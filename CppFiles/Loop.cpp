//This is the file which uses the class definitons in "pch.h" to declare "Main" functions.


//For more info on each process visit "pch.h".

 
#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/Loop.h"

void MessageLoop()
{
    BOOL boolean;
    MSG msg = { 0 };

        // Process any messages in the queue.
        while(GetMessageW(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    
}