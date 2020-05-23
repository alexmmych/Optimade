SET "sourcedir=C:\Optimade\CppFiles\"
SET "includedir=C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\"
SET "includedir1=C:\cef\include\"

cd %sourcedir%

SETLOCAL EnableDelayedExpansion

SET CppList=
SET LibList=
SET IncludeList=
SET IncludeList1=

SET "space= "
SET "quote=""

SET "CommandLinker=-L"
SET "CommandLink=-l"
SET "CommandInclude=/I"

FOR /f "delims=" %%v IN ('dir /a-d /b "%sourcedir%*.cpp"') DO (
SET CppList=!CppList!%space%%%v
)


FOR /f "tokens=*" %%b IN ('dir /ad /b "%includedir%*"') DO (

SET IncludeList=!IncludeList!%space%%CommandInclude%%quote%!includedir!%%b%quote%
ECHO !IncludeList!

)

FOR /f "tokens=*" %%b IN ('dir /ad /b "%includedir1%*"') DO (

SET IncludeList1=!IncludeList1!%space%%CommandInclude%%quote%!includedir1!%%b%quote%
ECHO !IncludeList1!

)

cl%CppList% /I"C:\cef\include" /I"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.26.28801\include" %IncludeList%  %IncludeList1% /out:Optimade\Optimade.exe
PAUSE
