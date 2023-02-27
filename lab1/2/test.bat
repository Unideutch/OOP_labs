@echo off

set PROGRAM="%~1"
set OUTPUT = "%TEMP%\output.txt"
rem simple tests
%PROGRAM% 16 10 -7FFFFFFF 
fc output.txt maxIntBelow.txt || goto err
%PROGRAM% 16 10 7FFFFFFF
fc output.txt maxInt.txt || goto err

rem from biggest notation to smallest
%PROGRAM% 36 2 ZZZZ 
fc output.txt bigToSmall.txt || goto err
rem reverse
%PROGRAM% 2 36 110011010000011111111
fc output.txt smallToBig.txt || goto err

rem too large values
%PROGRAM% 16 10 FFFFFFFF
fc output.txt inflation.txt || goto err


rem err params
%PROGRAM% 0 40 ABCD
fc output.txt wrongInput.txt || goto err
%PROGRAM% 10 2 ABCD
fc output.txt wrongInput.txt || goto err
%PROGRAM% G 10 FFFFFFFF
fc output.txt wrongInput.txt || goto err
%PROGRAM% "" "" ""
fc output.txt wrongInput.txt || goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1