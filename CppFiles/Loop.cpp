//This is the file which uses the class definitons in "pch.h" to declare "Main" functions.


//For more info on each process visit "pch.h".

 
#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/Loop.h"

void MessageLoop()
{
    BOOL boolean;
    MSG msg = { 0 };
    POINT p;

    while (msg.message != WM_QUIT)
    {
        // Process any messages in the queue.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}