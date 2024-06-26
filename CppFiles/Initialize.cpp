/*********************************************************************************************************************/
/*                                                                                                                   */
/*   This is the file which contains the windows.h version of main and uses the most important class called Window   */
/*   in order to fastly create a window in just a single line.                                                       */
/*                                                                                                                   */
/*********************************************************************************************************************/

#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/Console.h"
#include "../HeaderFiles/CefWindowView.h"
#include "../HeaderFiles/Hook.h"

#define CONSOLE_ENABLE


int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    CefMainArgs main_args(hInstance);

    CefRefPtr<WindowView> app(new WindowView);

    void* sandbox_info = nullptr;

    int exit_code = CefExecuteProcess(main_args, app.get(), sandbox_info);
    if (exit_code >= 0) {
        // The sub-process terminated, exit now.
        return exit_code;
    }

    CefSettings settings;

    settings.no_sandbox = true;
    settings.multi_threaded_message_loop = true;

#ifdef CONSOLE_ENABLE
    CreateConsole();
#endif

    Window::GetInstance();

    CefEnableHighDPISupport();

    CefInitialize(main_args, settings, app.get(),sandbox_info);

    MessageLoop();

    CefShutdown();

	return 0;
}
