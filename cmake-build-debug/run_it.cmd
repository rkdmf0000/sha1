@echo off

echo Thank you for use this encryption code :)  : 
hash_enc1.exe Thank you for use this encryption code :)
echo.

echo hello : 
hash_enc1.exe suck
echo.

echo world123 : 
hash_enc1.exe buck
echo.

echo suck you : 
hash_enc1.exe suck you
echo.

echo 1234 : 
hash_enc1.exe 1234
echo.

echo ������: 
hash_enc1.exe ������
echo.

echo �������: 
hash_enc1.exe �������
echo.

echo e5�긻c9���0��b��5��a4 : 
hash_enc1.exe e5�긻c9���0��b��5��a4
echo.


echo.
echo.
echo.
echo. ����������������������������������������������������
echo.   SHA ENCRYPT TESTER TOOL
echo. ����������������������������������������������������
echo.

:testform
echo. [ Target text : %str% ]
set /p str=Please put any text : 
hash_enc1.exe %str%
echo. [ Converted! ]
echo.
echo.
goto :testform

pause