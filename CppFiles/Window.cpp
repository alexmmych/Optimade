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

class tempClass : public CefBase {
private:
	IMPLEMENT_REFCOUNTING(tempClass);
};

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
    CreateConsole();

		CefEnableHighDPISupport();

		CefMainArgs args(hInstance);

		void* sandbox_info = nullptr;

		// Create a
	  CefRefPtr<tempClass> app(new tempClass);

		int exit_code = CefExecuteProcess(args, app, sandbox_info);
		if (exit_code >= 0)
			return exit_code;

		CefSettings settings;

		settings.no_sandbox = true;
		settings.multi_threaded_message_loop = true; //Windows only

    CefInitialize(args, settings, app.get(), sandbox_info);

		Window window;

    CefShutdown();

	return 0;
}
