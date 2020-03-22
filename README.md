# mima
INI 書き換えツール for mima

Version 1.10. © 2019 KusaReMKN. Available under [MKNPPL](https://mkn.kusaremkn.com/mknppl).

## これはなに
KusaReMKN による、怠け者のための INI 読み書きツールです。
たった一行記述するだけで INI をいじくれます。

## ファイルの発生場所
INI ファイルは、`%APPDATA` の直下に発生します。
INI ファイルのファイル名は、アプリの名前が利用されます。

## 内蔵関数
```cpp
// バージョン取得 (1.10 なら 0x0110)
DWORD __cdecl MimaVersion();

// INI から値を読み出す
DWORD __cdecl GetAppData(
  LPCTSTR AppName,   // アプリの名前
  LPCTSTR KeyName,   // キー名
  LPTSTR Buffer,     // 受け取りバッファ
  DWORD BufferSize   // バッファのサイズ (単位:文字)
);

DWORD __cdecl SetAppData(
  LPCTSTR AppName,   // アプリの名前
  LPCTSTR KeyName,   // キー名
  LPCTSTR Value      // 値
);
```

## 返値

|返値|エラー内容|
|:-:|:-|
|0|正常終了|
|1|Get: バッファが小さすぎる|
|1|Set: エラーってるかもしれない|
|-1|プロセスのヒープを得られなかった|
|-2|環境変数用のメモリを確保できなかった|
|-3|環境変数 `%APPDATA%` が得られなかった|
|-4|ファイルパス用のメモリを確保できなかった|
|-5|ファイルパスを確定する最中で事故った|

## HSP ユーザへ
HSP から呼び出すには、以下を記述してください:
```clike
#uselib "mima.dll"
#func GetAppData  "GetAppDataA" str, str, var, int
#func SetAppData  "SetAppDataA" str, str, str
```
