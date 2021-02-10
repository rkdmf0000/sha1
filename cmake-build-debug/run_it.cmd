@echo off

echo hello : 
hash_enc1.exe hello
echo.

echo suck : 
hash_enc1.exe suck
echo.

echo buck : 
hash_enc1.exe buck
echo.

echo suck you : 
hash_enc1.exe suck you
echo.

echo 1234 : 
hash_enc1.exe 1234
echo.

echo xxxx: 
hash_enc1.exe xxxx
echo.

:testform
setlocal

set /p str=아무 문자열이나 입력하세요 :
hash_enc1.exe %str%
echo.
pause > nul
goto :testform

pause