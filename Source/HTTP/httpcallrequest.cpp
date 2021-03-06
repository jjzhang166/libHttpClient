// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "pch.h"
#include "httpcall.h"


HC_API void HC_CALLING_CONV
HCHttpCallRequestSetUrl(
    _In_ HC_CALL_HANDLE call,
    _In_ PCSTR_T method,
    _In_ PCSTR_T url
    )
{
    VerifyGlobalInit();
    call->method = method;
    call->url = url;

    LOGS_INFO << "HCHttpCallRequestSetUrl [ID " << call->id << "]: method=" << method << " url=" << url; 
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestGetUrl(
    _In_ HC_CALL_HANDLE call,
    _Outptr_ PCSTR_T* method,
    _Outptr_ PCSTR_T* url
    )
{
    VerifyGlobalInit();
    *method = call->method.c_str();
    *url = call->url.c_str();
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestSetRequestBodyString(
    _In_ HC_CALL_HANDLE call,
    _In_ PCSTR_T requestBodyString
    )
{
    VerifyGlobalInit();
    call->requestBodyString = requestBodyString;
    LOGS_INFO << "HCHttpCallRequestSetRequestBodyString [ID " << call->id << "]: requestBodyString=" << requestBodyString;
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestGetRequestBodyString(
    _In_ HC_CALL_HANDLE call,
    _Out_ PCSTR_T* requestBodyString
    )
{
    VerifyGlobalInit();
    *requestBodyString = call->requestBodyString.c_str();
}


HC_API void HC_CALLING_CONV
HCHttpCallRequestSetHeader(
    _In_ HC_CALL_HANDLE call,
    _In_ PCSTR_T headerName,
    _In_ PCSTR_T headerValue
    )
{
    VerifyGlobalInit();
    call->requestHeaders[headerName] = headerValue;
    LOGS_INFO << "HCHttpCallRequestSetHeader [ID " << call->id << "]: " << headerName << "=" << headerValue;
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestGetHeader(
    _In_ HC_CALL_HANDLE call,
    _In_ PCSTR_T headerName,
    _Out_ PCSTR_T* headerValue
    )
{
    VerifyGlobalInit();
    auto it = call->requestHeaders.find(headerName);
    if (it != call->requestHeaders.end())
    {
        *headerValue = it->second.c_str();
    }
    else
    {
        *headerValue = nullptr;
    }
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestGetNumHeaders(
    _In_ HC_CALL_HANDLE call,
    _Out_ uint32_t* numHeaders
    )
{
    VerifyGlobalInit();
    *numHeaders = static_cast<uint32_t>(call->requestHeaders.size());
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestGetHeaderAtIndex(
    _In_ HC_CALL_HANDLE call,
    _In_ uint32_t headerIndex,
    _Out_ PCSTR_T* headerName,
    _Out_ PCSTR_T* headerValue
    )
{
    VerifyGlobalInit();

    uint32_t index = 0;
    for (auto it = call->requestHeaders.cbegin(); it != call->requestHeaders.cend(); ++it)
    {
        if (index == headerIndex)
        {
            *headerName = it->first.c_str();
            *headerValue = it->second.c_str();
            return;
        }

        index++;
    }

    *headerName = nullptr;
    *headerValue = nullptr;
    return;
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestSetRetryAllowed(
    _In_ HC_CALL_HANDLE call,
    _In_ bool retryAllowed
    )
{
    VerifyGlobalInit();
    call->retryAllowed = retryAllowed;
    LOGS_INFO << "HCHttpCallRequestSetRetryAllowed [ID " << call->id << "]: retryAllowed=" << retryAllowed;
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestGetRetryAllowed(
    _In_ HC_CALL_HANDLE call,
    _Out_ bool* retryAllowed
    )
{
    VerifyGlobalInit();
    *retryAllowed = call->retryAllowed;
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestSetTimeout(
    _In_ HC_CALL_HANDLE call,
    _In_ uint32_t timeoutInSeconds
    )
{
    VerifyGlobalInit();
    call->timeoutInSeconds = timeoutInSeconds;
    LOGS_INFO << "HCHttpCallRequestSetTimeout [ID " << call->id << "]: timeoutInSeconds=" << timeoutInSeconds;
}

HC_API void HC_CALLING_CONV
HCHttpCallRequestGetTimeout(
    _In_ HC_CALL_HANDLE call,
    _Out_ uint32_t* timeoutInSeconds
    )
{
    VerifyGlobalInit();
    *timeoutInSeconds = call->timeoutInSeconds;
}


