This document is encoded in utf-8(LF)

#######################################
##     最強の INI 書き換えセット     ##
##                (c) 2019 KusaReMKN ##
#######################################

はっせーとお電話してたら DLL が勝手に発生してた。
ini ファイルは %APPDATA% 直下に発生する。


HSP から呼び出す場合、mima.dll を動作させる HSP と同一ディレクトリに置いて、
#uselib "mima.dll"
#func SetAppData "_SetAppData" str, str, str
#func GetAppData "_GetAppData" str, str, var, int
を記載してください。


■ 関数群

// INI からデータをゲット
DWORD __cdecl GetAppData(
	LPCTSTR AppName,	// アプリの名前	(str)
	LPCTSTR KeyName,	// 値の名前	(str)
	LPTSTR Buffer,		// 値(文字列) の受け取りバッファ (var?)
	DWORD BufferSize	// バッファのサイズ (int)
);


// INI にデータをセット
DWORD __cdecl SetAppData(
	LPCTSTR AppName,	// アプリの名前 (str)
	LPCTSTR KeyName,	// 値の名前 (str)
	LPCTSTR Value		// 値(文字列) (str)
);



■ 返り値

返り値はエラーコード。
0 が正常。
1 は予期されるエラー。
	GET: バッファのサイズが足りない
	SET: 失敗してるかもしれない(?)
負値は異常エラー。
	-1: HeapError
	-2: AppDataMemoryAllocationError
	-3: AppDataEnvironmentVariableError
	-4: IniPathMemoryAllocationError
	-5: IniPathPrintfError
