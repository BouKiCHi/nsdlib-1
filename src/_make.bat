
rem --- nsd.lib ---
cd nsd
nmake
copy *.lib ..\..\lib\
cd..

rem --- nsc.exe ---
cd nsc
cd..

rem --- nsdl.chm ---
cd help
copy *.chm ..\..\doc\
cd..

rem ������ for Debug ������
cd _Debug
nmake
cd..

cd _nsf
nmake
cd..

