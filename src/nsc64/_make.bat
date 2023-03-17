SET PATH_BACK=%PATH%
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
@REM call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
MSBuild nsc64.sln -t:Build -p:Configuration=Release;Platform="x64"

if not exist ..\..\bin mkdir ..\..\bin
copy x64\Release\*.exe ..\..\bin\
SET PATH=%PATH_BACK%
