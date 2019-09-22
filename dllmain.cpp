// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"

#include "mima2.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

DWORD __cdecl MimaVersion(void)
{
	return MIMAVERSION;
}

DWORD __cdecl GetAppDataA(LPCSTR AppName, LPCSTR KeyName, LPSTR Buffer, DWORD BufferSize)
{
	DWORD RetValue = 0; // 関数の返り値
	LPSTR AppData;			// 環境変数 %APPDATA% の内容格納用
	LPSTR IniPath;			// ini の Path 格納用
	DWORD ReadSize;			// 読み込まれたサイズ
	HANDLE Heap;

	// Heap をゲットする
	if ((Heap = GetProcessHeap()) == NULL) {
		RetValue = -1;
		goto HeapError;
	}

	// %APPDATA% をゲットする
	if ((AppData = (LPSTR)HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH * sizeof CHAR)) == NULL) {
		RetValue = -2;
		goto AppDataMemoryError;
	}
	if (GetEnvironmentVariableA("APPDATA", AppData, MAX_PATH) == 0) {
		RetValue = -3;
		goto AppDataVariableError;
	}

	// INI のファイル名を確定する
	if ((IniPath = (LPSTR)HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH * sizeof CHAR)) == NULL) {
		RetValue = -4;
		goto IniPathMemoryError;
	}
	if (StringCchPrintfA(IniPath, MAX_PATH, "%s\\%s.ini", AppData, AppName) != S_OK) {
		RetValue = -5;
		goto IniPathPrintfError;
	}

	// INI の値をゲットする
	ReadSize = GetPrivateProfileStringA(AppName, KeyName, "", Buffer, BufferSize, IniPath);
	if (ReadSize == BufferSize - 1) {
		RetValue = 1;
	}

IniPathPrintfError:
	HeapFree(Heap, 0, IniPath);
IniPathMemoryError:
AppDataVariableError:
	HeapFree(Heap, 0, AppData);
AppDataMemoryError:
HeapError:
	return RetValue;
}
DWORD __cdecl GetAppDataW(LPCWSTR AppName, LPCWSTR KeyName, LPWSTR Buffer, DWORD BufferSize)
{
	DWORD RetValue = 0; // 関数の返り値
	LPWSTR AppData;			// 環境変数 %APPDATA% の内容格納用
	LPWSTR IniPath;			// ini の Path 格納用
	DWORD ReadSize;			// 読み込まれたサイズ
	HANDLE Heap;

	// Heap をゲットする
	if ((Heap = GetProcessHeap()) == NULL) {
		RetValue = -1;
		goto HeapError;
	}

	// %APPDATA% をゲットする
	if ((AppData = (LPWSTR)HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH * sizeof WCHAR)) == NULL) {
		RetValue = -2;
		goto AppDataMemoryError;
	}
	if (GetEnvironmentVariableW(L"APPDATA", AppData, MAX_PATH) == 0) {
		RetValue = -3;
		goto AppDataVariableError;
	}

	// INI のファイル名を確定する
	if ((IniPath = (LPWSTR)HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH * sizeof WCHAR)) == NULL) {
		RetValue = -4;
		goto IniPathMemoryError;
	}
	if (StringCchPrintfW(IniPath, MAX_PATH, L"%s\\%s.ini", AppData, AppName) != S_OK) {
		RetValue = -5;
		goto IniPathPrintfError;
	}

	// INI の値をゲットする
	ReadSize = GetPrivateProfileStringW(AppName, KeyName, L"", Buffer, BufferSize, IniPath);
	if (ReadSize == BufferSize - 1) {
		RetValue = 1;
	}

IniPathPrintfError:
	HeapFree(Heap, 0, IniPath);
IniPathMemoryError:
AppDataVariableError:
	HeapFree(Heap, 0, AppData);
AppDataMemoryError:
HeapError:
	return RetValue;
}

DWORD __cdecl SetAppDataA(LPCSTR AppName, LPCSTR KeyName, LPCSTR Value)
{
	DWORD RetValue = 0; // 関数の返り値
	LPSTR AppData;			// 環境変数 %APPDATA% の内容格納用
	LPSTR IniPath;			// ini の Path 格納用
	DWORD WriteRet;			// 書き込みの値
	HANDLE Heap;

	// Heap をゲットする
	if ((Heap = GetProcessHeap()) == NULL) {
		RetValue = -1;
		goto HeapError;
	}

	// %APPDATA% をゲットする
	if ((AppData = (LPSTR)HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH * sizeof CHAR)) == NULL) {
		RetValue = -2;
		goto AppDataMemoryError;
	}
	if (GetEnvironmentVariableA("APPDATA", AppData, MAX_PATH) == 0) {
		RetValue = -3;
		goto AppDataVariableError;
	}

	// INI のファイル名を確定する
	if ((IniPath = (LPSTR)HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH * sizeof WCHAR)) == NULL) {
		RetValue = -4;
		goto IniPathMemoryError;
	}
	if (StringCchPrintfA(IniPath, MAX_PATH, "%s\\%s.ini", AppData, AppName) != S_OK) {
		RetValue = -5;
		goto IniPathPrintfError;
	}

	// INI の値をセットする
	WriteRet = WritePrivateProfileStringA(AppName, KeyName, Value, IniPath);
	if (WriteRet == 0) {
		RetValue = 1;
	}

IniPathPrintfError:
	HeapFree(Heap, 0, IniPath);
IniPathMemoryError:
AppDataVariableError:
	HeapFree(Heap, 0, AppData);
AppDataMemoryError:
HeapError:
	return RetValue;
}
DWORD __cdecl SetAppDataW(LPCWSTR AppName, LPCWSTR KeyName, LPCWSTR Value)
{
	DWORD RetValue = 0; // 関数の返り値
	LPWSTR AppData;			// 環境変数 %APPDATA% の内容格納用
	LPWSTR IniPath;			// ini の Path 格納用
	DWORD WriteRet;			// 書き込みの値
	HANDLE Heap;

	// Heap をゲットする
	if ((Heap = GetProcessHeap()) == NULL) {
		RetValue = -1;
		goto HeapError;
	}

	// %APPDATA% をゲットする
	if ((AppData = (LPWSTR)HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH * sizeof WCHAR)) == NULL) {
		RetValue = -2;
		goto AppDataMemoryError;
	}
	if (GetEnvironmentVariableW(L"APPDATA", AppData, MAX_PATH) == 0) {
		RetValue = -3;
		goto AppDataVariableError;
	}

	// INI のファイル名を確定する
	if ((IniPath = (LPWSTR)HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH * sizeof WCHAR)) == NULL) {
		RetValue = -4;
		goto IniPathMemoryError;
	}
	if (StringCchPrintfW(IniPath, MAX_PATH, L"%s\\%s.ini", AppData, AppName) != S_OK) {
		RetValue = -5;
		goto IniPathPrintfError;
	}

	// INI の値をセットする
	WriteRet = WritePrivateProfileStringW(AppName, KeyName, Value, IniPath);
	if (WriteRet == 0) {
		RetValue = 1;
	}

IniPathPrintfError:
	HeapFree(Heap, 0, IniPath);
IniPathMemoryError:
AppDataVariableError:
	HeapFree(Heap, 0, AppData);
AppDataMemoryError:
HeapError:
	return RetValue;
}
