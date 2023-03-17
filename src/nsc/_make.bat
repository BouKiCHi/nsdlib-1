SET PATH_BACK=%PATH%
rem call "C:\Program Files (x86)\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
rem devenv nsc.sln /build Release
cd release
copy *.exe ..\..\..\bin\
cd..
SET PATH=%PATH_BACK%
