// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "pch.h"
#include "httpcall.h"
#include "Mock/http_mock.h"

HC_API void HC_CALLING_CONV
HCHttpCallCreate(
    _Out_ HC_CALL_HANDLE* callHandle
    )
{
    VerifyGlobalInit();

    HC_CALL* call = new HC_CALL();
    call->retryAllowed = true;

    call->id = get_http_singleton()->m_lastHttpCallId;
    get_http_singleton()->m_lastHttpCallId++;

    LOGS_INFO << "HCHttpCallCreate [ID " << call->id << "]";

    *callHandle = call;
}

HC_API void HC_CALLING_CONV
HCHttpCallCleanup(
    _In_ HC_CALL_HANDLE call
    )
{
    LOGS_INFO << "HCHttpCallCleanup [ID " << call->id << "]";
    VerifyGlobalInit();
    delete call;
}

void HttpCallPerformExecute(
    _In_opt_ void* executionRoutineContext,
    _In_ HC_TASK_HANDLE taskHandle
    )
{
    HC_CALL_HANDLE call = (HC_CALL_HANDLE)executionRoutineContext;
    LOGS_INFO << "HttpCallPerformExecute [ID " << call->id << "]";

    bool matchedMocks = false;
    if (get_http_singleton()->m_mocksEnabled)
    {
        matchedMocks = Mock_Internal_HCHttpCallPerform(call);
        if (matchedMocks)
        {
            HCTaskSetCompleted(taskHandle);
        }
    }
   
    if (!matchedMocks) // if there wasn't a matched mock, then real call
    {
        HC_HTTP_CALL_PERFORM_FUNC performFunc = get_http_singleton()->m_performFunc;
        if (performFunc != nullptr)
        {
            try
            {
                performFunc(call, taskHandle);
            }
            catch (...)
            {
                LOG_ERROR("HCHttpCallPerform failed");
            }
        }
    }
}

void HttpCallPerformWriteResults(
    _In_opt_ void* writeResultsRoutineContext,
    _In_ HC_TASK_HANDLE taskHandle
    )
{
    HC_CALL_HANDLE call = (HC_CALL_HANDLE)writeResultsRoutineContext;
    LOGS_INFO << "HttpCallPerformWriteResults [ID " << call->id << "]";
    HCHttpCallPerformCompletionRoutine completeFn = (HCHttpCallPerformCompletionRoutine)taskHandle->completionRoutine;
    if (completeFn != nullptr)
    {
        completeFn(taskHandle->completionRoutineContext, call);
    }
}

HC_API HC_TASK_HANDLE HC_CALLING_CONV
HCHttpCallPerform(
    _In_ uint64_t taskGroupId,
    _In_ HC_CALL_HANDLE call,
    _In_opt_ void* completionRoutineContext,
    _In_opt_ HCHttpCallPerformCompletionRoutine completionRoutine
    )
{
    VerifyGlobalInit();
    LOGS_INFO << "HCHttpCallPerform [ID " << call->id << "]";

    return HCTaskCreate(
        taskGroupId,
        HttpCallPerformExecute, (void*)call,
        HttpCallPerformWriteResults, (void*)call,
        completionRoutine, completionRoutineContext,
        true
        );
}


