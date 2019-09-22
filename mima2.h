#pragma once

#ifdef MIMA2_EXPORTS
#define MIMA_API __declspec(dllexport)
#else
#define MIMA_API __declspec(dllimport)
#endif

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

constexpr auto MIMAVERSION = (0x0110);

#ifdef __cplusplus
extern "C" {
#endif

#ifdef UNICODE
#define GetAppData GetAppDataW
#else
#define GetAppData GetAppDataA
#endif

MIMA_API	DWORD __cdecl MimaVersion(void);

MIMA_API	DWORD __cdecl GetAppDataA(LPCSTR AppName, LPCSTR KeyName, LPSTR Buffer, DWORD BufferSize);
MIMA_API	DWORD __cdecl GetAppDataW(LPCWSTR AppName, LPCWSTR KeyName, LPWSTR Buffer, DWORD BufferSize);

MIMA_API DWORD __cdecl SetAppDataA(LPCSTR AppName, LPCSTR KeyName, LPCSTR Value);
MIMA_API DWORD __cdecl SetAppDataW(LPCWSTR AppName, LPCWSTR KeyName, LPCWSTR Value);

#ifdef __cplusplus
}
#endif