@echo off

echo Thank you for use this encryption code :)  : 
hash_enc1.exe Thank you for use this encryption code :)
echo.

echo SEED 123 / hello : 
hash_enc1.exe -s 123 -v suck
echo.

echo SEED 456 / hello : 
hash_enc1.exe -s 456 -v suck
echo.

echo world123 : 
hash_enc1.exe -v buck
echo.

echo suck you : 
hash_enc1.exe -v suck you
echo.

echo 1234 : 
hash_enc1.exe -v 1234
echo.

echo 陛釭棻: 
hash_enc1.exe -v 陛釭棻
echo.

echo 旛蜪蒡郲: 
hash_enc1.exe -v 旛蜪蒡郲
echo.

echo e5剟蜓c9瀎煎0瘏b褐5裺a4 : 
hash_enc1.exe -v e5剟蜓c9瀎煎0瘏b褐5裺a4
echo.

echo.
echo.
echo.
echo. 忙式式式式式式式式式式式式式式式式式式式式式式式式忖
echo.   SHA ENCRYPT TESTER TOOL
echo. 戌式式式式式式式式式式式式式式式式式式式式式式式式戎
echo.

:testform
echo. [ SEED : HELLO_WORD123 ] [ TEXT : %str% ]
set /p str=Please put any text : 
hash_enc1.exe -s HELLO_WORD123 -v %str%
echo.
echo.
goto :testform

pause