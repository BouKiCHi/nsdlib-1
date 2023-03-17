# コマンドプロンプトでのコンパイル方法

* https://www.msys2.org/
からmsys2をダウンロード、c:\msys64\usr\binにmake.exeがあるようにする。

* https://github.com/cc65/cc65
からWindows Snapshotをダウンロード、適当なディレクトリに展開する。

* 環境変数などで`CC65_BIN`をcc65スナップショットのbinディレクトリに変更。
例:`C:\cc65-snapshot-win32\bin`

* srcディレクトリに移動後、`_setenv.bat`を実行
* src/nsdディレクトリに移動後、次のコマンドを実行

`make -f MAKEFILE clean install`

* src/romディレクトリに移動後、次のコマンドを実行
`make -f MAKEFILE clean install`
