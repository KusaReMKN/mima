#include <windows.h>
#include <strsafe.h>

#define EXPORT __declspec(dllexport)

// INI からデータをゲット
EXPORT DWORD __cdecl GetAppData(LPCTSTR AppName, LPCTSTR KeyName, LPTSTR Buffer, DWORD BufferSize)
{
	DWORD RetValue = 0; // 関数の返り値
	LPTSTR AppData;			// 環境変数 %APPDATA% の内容格納用
	LPTSTR IniPath;			// ini の Path 格納用
	DWORD ReadSize;			// 読み込まれたサイズ
	HANDLE Heap = GetProcessHeap();

	// Heap をゲットする
	if (Heap == NULL)
	{
		RetValue = -1;
		goto HeapError;
	}

	// %APPDATA% をゲットする
	if ((AppData = HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH)) == NULL)
	{
		RetValue = -2;
		goto AppDataMemoryError;
	}
	if (GetEnvironmentVariable(TEXT("APPDATA"), AppData, MAX_PATH) == 0)
	{
		RetValue = -3;
		goto AppDataVariableError;
	}

	// INI のファイル名を確定する
	if ((IniPath = HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH)) == NULL)
	{
		RetValue = -4;
		goto IniPathMemoryError;
	}
	if (StringCbPrintf(IniPath, MAX_PATH, TEXT("%s\\%s.ini"), AppData, AppName) != S_OK)
	{
		RetValue = -5;
		goto IniPathPrintfError;
	}

	// INI の値をゲットする
	ReadSize = GetPrivateProfileString(AppName, KeyName, TEXT(""), Buffer, BufferSize, IniPath);
	if (ReadSize == BufferSize - 1)
	{
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

// INI にデータをセット
EXPORT DWORD __cdecl SetAppData(LPCTSTR AppName, LPCTSTR KeyName, LPCTSTR Value)
{
	DWORD RetValue = 0; // 関数の返り値
	LPTSTR AppData;			// 環境変数 %APPDATA% の内容格納用
	LPTSTR IniPath;			// ini の Path 格納用
	DWORD WriteRet;			// 書き込みの値
	HANDLE Heap = GetProcessHeap();

	// Heap をゲットする
	if (Heap == NULL)
	{
		RetValue = -1;
		goto HeapError;
	}

	// %APPDATA% をゲットする
	if ((AppData = HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH)) == NULL)
	{
		RetValue = -2;
		goto AppDataMemoryError;
	}
	if (GetEnvironmentVariable(TEXT("APPDATA"), AppData, MAX_PATH) == 0)
	{
		RetValue = -3;
		goto AppDataVariableError;
	}

	// INI のファイル名を確定する
	if ((IniPath = HeapAlloc(Heap, HEAP_ZERO_MEMORY, MAX_PATH)) == NULL)
	{
		RetValue = -4;
		goto IniPathMemoryError;
	}
	if (StringCbPrintf(IniPath, MAX_PATH, TEXT("%s\\%s.ini"), AppData, AppName) != S_OK)
	{
		RetValue = -5;
		goto IniPathPrintfError;
	}

	// INI の値をセットする
	WriteRet = WritePrivateProfileString(AppName, KeyName, Value, IniPath);
	if (WriteRet == 0)
	{
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
