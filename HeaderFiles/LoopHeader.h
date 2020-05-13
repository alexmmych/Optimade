//This is the header file which defines the "Loop" class which holds the message loop of the window.

#pragma once

class Loop
{
//Parameters for the message loop.
	BOOL boolean; 
	MSG msg = { 0 };
	POINT p;			

protected:  // Only the Window class should be able to acess the window loop.

	void MessageLoop(); //The message loop.
};
