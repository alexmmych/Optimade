//

#include "../HeaderFiles/ConsoleHeader.h"
#include "../HeaderFiles/pch.h"

#include <stdio.h>
#include <fcntl.h>
#include <io.h>


static const WORD MAX_CONSOLE_LINES = 500;

void CreateConsole() {
    // allocate a console for this app
    AllocConsole();

    FILE* dummyFile;

    freopen_s(&dummyFile,"CONOUT$", "w",stdout);
    freopen_s(&dummyFile, "CONOUT$", "w", stderr);
    freopen_s(&dummyFile, "CONIN$", "r", stdin);

    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    std::cout << "Status: Console created succesfully\n";
}
