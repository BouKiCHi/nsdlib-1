if exist buildlog.txt del buildlog.txt
if exist errlog.txt del errlog.txt
if exist comlog.txt del comlog.txt
make -f MAKEFILE -k >buildlog.txt 2>&1
if %errorlevel% equ 0	goto end

if not exist ..\..\bin mkdir ..\..\bin
copy *.bin ..\..\bin\

if exist errlog.txt start errlog.txt
:end
