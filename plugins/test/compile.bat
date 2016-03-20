set PATH=C:\Qt\Qt5.5.0\5.5\mingw492_32\bin;C:\Qt\Qt5.5.0\Tools\mingw492_32\bin;C:\Windows\System32
qmake CONFIG-=release CONFIG+=debug %*
mingw32-make -j2