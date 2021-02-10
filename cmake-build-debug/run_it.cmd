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

echo 陛釭棻: 
hash_enc1.exe 陛釭棻
echo.

echo 旛蜪蒡郲: 
hash_enc1.exe 旛蜪蒡郲
echo.

echo e5剟蜓c9瀎煎0瘏b褐5裺a4 : 
hash_enc1.exe e5剟蜓c9瀎煎0瘏b褐5裺a4
echo.


echo.
echo.
echo.
echo. 忙式式式式式式式式式式式式式式式式式式式式式式式式忖
echo.   SHA ENCRYPT TESTER TOOL
echo. 戌式式式式式式式式式式式式式式式式式式式式式式式式戎
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