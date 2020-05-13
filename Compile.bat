
SET "sourcedir=C:\Optimade\CppFiles\"

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

FOR /f "delims=" %%v IN ('dir /a-d /b "%sourcedir%*.cpp"') DO (
SET CppList=!CppList!%space%%%v
)

g++%CppList% -std=c++17 -mwindows -o C:\Optimade\Optimade.exe
PAUSE
