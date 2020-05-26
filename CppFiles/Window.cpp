/*********************************************************************************************************************/
/*                                                                                                                   */
/*   This is the file which contains the windows.h version of main and uses the most important class called Window   */
/*   in order to fastly create a window in just a single line.                                                       */
/*                                                                                                                   */
/*********************************************************************************************************************/
#include "C:/Optimade/HeaderFiles/pch.h"
#include "C:/Optimade/HeaderFiles/WindowHeader.h"
#include "C:/Optimade/HeaderFiles/ConsoleHeader.h"
#include "C:/Optimade/HeaderFiles/simple_app.h"

class TempClass : public CefApp {
public:
	// Various class methods here...

private:
	// Various class members here...

	IMPLEMENT_REFCOUNTING(TempClass);  // Provides atomic refcounting implementation.
};


               /***********************************************************/
               /*                                                         */
               /*   In order to read the comments correctly have in mind  */
               /*   that the code to the right of a variable or function  */
               /*   means it only applies to it. In other words there is  */
               /*   no newline in code which is written with the "//" me- */
               /*   thod.                                                 */
               /*                                                         */
               /***********************************************************/



int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CefEnableHighDPISupport();

	CefMainArgs args(hInstance);

	void* sandbox_info = nullptr;

	CefSettings settings;

	settings.no_sandbox = true;

	CefRefPtr<SimpleApp> app(new SimpleApp);

	int exit_code = CefExecuteProcess(args, app.get(), sandbox_info);
	if (exit_code >= 0)
		return exit_code;


    CefInitialize(args, settings, app.get(), sandbox_info);

	CefRunMessageLoop();

    CefShutdown();

	return 0;
}
