
SET "sourcedir=C:\GameProject\CppFiles\"
SET "librarydir=C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\"
SET "includedir=C:\Program Files (x86)\Windows Kits\10\Include\10.0.18362.0\"

cd %sourcedir%

SETLOCAL EnableDelayedExpansion

SET CppList=
SET LibList=
SET IncludeList=

SET "space= "
SET "quote=""

SET "CommandLinker=-L"
SET "CommandLink=-l"
SET "CommandInclude=-I"

SET "target=\x64"

FOR /f "delims=" %%v IN ('dir /a-d /b "%sourcedir%*.cpp"') DO (
SET CppList=!CppList!%space%%%v
)

FOR /f "tokens=*" %%a IN ('dir /ad /b "%librarydir%*"') DO (
SET LibList=!LibList!%space%%CommandLinker%%quote%!librarydir!%%a%target%%quote%
)

FOR /f "tokens=*" %%b IN ('dir /ad /b "%includedir%*"') DO (
IF NOT [%%b] == [ucrt] (
SET IncludeList=!IncludeList!%space%%CommandInclude%%quote%!includedir!%%b%quote%
ECHO !IncludeList!
)
)

g++%CppList% -std=c++17 -mwindows -o C:\GameProject\Game.exe
PAUSE
