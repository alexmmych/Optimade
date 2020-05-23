@echo off
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=2& goto :ABORT)
mt.exe -nologo -manifest "C:/Optimade/cef/tests/cefsimple/cefsimple.exe.manifest" "C:/Optimade/cef/tests/cefsimple/compatibility.manifest" -outputresource:"C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/cefsimple.exe";#1 || (set FAIL_LINE=3& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=4& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Debug/chrome_elf.dll C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/chrome_elf.dll || (set FAIL_LINE=5& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=6& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Debug/d3dcompiler_47.dll C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/d3dcompiler_47.dll || (set FAIL_LINE=7& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=8& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Debug/libcef.dll C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/libcef.dll || (set FAIL_LINE=9& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=10& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Debug/libEGL.dll C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/libEGL.dll || (set FAIL_LINE=11& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=12& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Debug/libGLESv2.dll C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/libGLESv2.dll || (set FAIL_LINE=13& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=14& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Debug/snapshot_blob.bin C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/snapshot_blob.bin || (set FAIL_LINE=15& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=16& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Debug/v8_context_snapshot.bin C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/v8_context_snapshot.bin || (set FAIL_LINE=17& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=18& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_directory C:/Optimade/cef/Debug/swiftshader C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/swiftshader || (set FAIL_LINE=19& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=20& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Resources/cef.pak C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/cef.pak || (set FAIL_LINE=21& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=22& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Resources/cef_100_percent.pak C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/cef_100_percent.pak || (set FAIL_LINE=23& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=24& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Resources/cef_200_percent.pak C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/cef_200_percent.pak || (set FAIL_LINE=25& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=26& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Resources/cef_extensions.pak C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/cef_extensions.pak || (set FAIL_LINE=27& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=28& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Resources/devtools_resources.pak C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/devtools_resources.pak || (set FAIL_LINE=29& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=30& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_if_different C:/Optimade/cef/Resources/icudtl.dat C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/icudtl.dat || (set FAIL_LINE=31& goto :ABORT)
cd /D C:\Optimade\cef\out\build\x64-Debug\tests\cefsimple || (set FAIL_LINE=32& goto :ABORT)
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E copy_directory C:/Optimade/cef/Resources/locales C:/Optimade/cef/out/build/x64-Debug/tests/cefsimple/Debug/locales || (set FAIL_LINE=33& goto :ABORT)
goto :EOF

:ABORT
set ERROR_CODE=%ERRORLEVEL%
echo Batch file failed at line %FAIL_LINE% with errorcode %ERRORLEVEL%
exit /b %ERROR_CODE%