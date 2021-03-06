// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
#pragma once

#pragma warning(disable: 4062)

#ifdef _WIN32
    #include <windows.h>

    #ifndef _WIN32_WINNT_WIN10
    #define _WIN32_WINNT_WIN10 0x0A00
    #endif

    #ifndef XDK_API
    #define XDK_API (WINAPI_FAMILY == WINAPI_FAMILY_TV_APP || WINAPI_FAMILY == WINAPI_FAMILY_TV_TITLE) 
    #endif

    #ifndef UWP_API
    #define UWP_API (WINAPI_FAMILY == WINAPI_FAMILY_APP && _WIN32_WINNT >= _WIN32_WINNT_WIN10)
    #endif
#endif //#ifdef _WIN32

#ifndef _WIN32
    #ifdef _In_
    #undef _In_
    #endif
    #define _In_

    #ifdef _Ret_maybenull_
    #undef _Ret_maybenull_
    #endif
    #define _Ret_maybenull_

    #ifdef _Post_writable_byte_size_
    #undef _Post_writable_byte_size_
    #endif
    #define _Post_writable_byte_size_(X)
#endif

#if defined _WIN32
  #ifdef HC_API_NONE
    #define HC_API
    #if _MSC_VER >= 1900
        #define HC_API_DEPRECATED __declspec(deprecated)
    #else
        #define HC_API_DEPRECATED
    #endif
  #else
    #ifdef HC_API_EXPORT
      #define HC_API __declspec(dllexport)
      #define HC_API_DEPRECATED __declspec(dllexport, deprecated)
    #else
      #define HC_API __declspec(dllimport)
      #define HC_API_DEPRECATED __declspec(dllimport, deprecated)
    #endif
  #endif
#else
  #if defined _NOHC_API || __GNUC__ < 4
     #define HC_API
     #define HC_API_DEPRECATED __attribute__ ((deprecated))
  #else
    #define HC_API __attribute__ ((visibility ("default")))
    #define HC_API_DEPRECATED __attribute__ ((visibility ("default"), deprecated))
  #endif
#endif

#ifdef _WIN32
typedef wchar_t CHAR_T;
typedef LPCWSTR PCSTR_T;
#else
typedef char CHAR_T;
typedef const char* PCSTR_T;
#endif

#ifndef _T
    #ifdef _WIN32
        #define _T(x) L ## x
    #else
        #define _T(x) x
    #endif
#endif

#define HC_CALLING_CONV __cdecl
//#define HC_CALLING_CONV __stdcall

typedef uint32_t HC_MEMORY_TYPE;
typedef struct HC_CALL* HC_CALL_HANDLE;
typedef struct HC_TASK* HC_TASK_HANDLE;
typedef const struct HC_USER* USER_HANDLE;
