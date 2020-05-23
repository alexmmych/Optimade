/*********************************************************************************************************************/
/*                                                                                                                   */
/*   This is the file which contains the windows.h version of main and uses the most important class called Window   */
/*   in order to fastly create a window in just a single line.                                                       */
/*                                                                                                                   */
/*********************************************************************************************************************/
#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/WindowHeader.h"
#include "../HeaderFiles/ConsoleHeader.h"


               /***********************************************************/
               /*                                                         */
               /*   In order to read the comments correctly have in mind  */
               /*   that the code to the right of a variable or function  */
               /*   means it only applies to it. In other words there is  */
               /*   no newline in code which is written with the "//" me- */
               /*   thod.                                                 */
               /*                                                         */
               /***********************************************************/

#define _DEBUG  //If defined, creates the D3D12 debug layer and console.

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
    CreateConsole();

    CefApp display;

    CefMainArgs args(hInstance);

    CefSettings settings;

    settings.no_sandbox = true;
    settings.multi_threaded_message_loop = true; //Windows only

    CefInitialize(args, settings, NULL, NULL);

	Window window;

    CefShutdown();

	return 0;
}
