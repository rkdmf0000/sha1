@echo off


:testform
set /p str=Please put any text : 
hash_enc1.exe %str%

echo.
goto :testform

pause