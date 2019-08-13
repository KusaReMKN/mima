# 最強の INI 書き換えセット
(c) 2019 KusaReMKN

This document is encoded in utf-8(LF)

ini ファイルは %APPDATA% 直下に発生する。
ini のファイル名はアプリの名前が利用される。

HSP から呼び出す場合、mima.dll を動作させる HSP と同一ディレクトリに置いて、以下を記載。
```hsp
#uselib "mima.dll"
#func SetAppData "_SetAppData" str, str, str
#func GetAppData "_GetAppData" str, str, var, int
```

## 関数群
```c
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
```
## 返り値

返り値はエラーコード。
|返り値|エラー内容|
|:---:|:---|
|0|正常|
|1|Get: バッファが小さすぎる|
|1|Set: エラーってるかもしれない|
|-1|プロセスのヒープを得られなかった|
|-2|環境変数用のメモリを確保できなかった|
|-3|環境変数 `%APPDATA%` が得られなかった|
|-4|パス用のメモリを確保できなかった|
|-5|パスを確定する最中で事故った|
