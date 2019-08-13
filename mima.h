#pragma once
#ifndef __MIMA_MKNP_INCLUDED__
#define __MIMA_MKNP_INCLUDED__

#include <windows.h>

extern DWORD GetAppData(LPCTSTR AppName, LPCTSTR KeyName, LPTSTR Buffer, DWORD BufferSize);
extern DWORD SetAppData(LPCTSTR AppName, LPCTSTR KeyName, LPCTSTR Value);

#endif
