/*********************************************************************************************************************/
/*                                                                                                                   */
/*   This is the file which contains the windows.h version of main and uses the most important class called Window   */
/*   in order to fastly create a window in just a single line.                                                       */
/*                                                                                                                   */
/*********************************************************************************************************************/

#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/Console.h"
#include "../HeaderFiles/CefWindowView.h"



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


    Window::Instance();

    CefInitialize(main_args, settings, app.get(),sandbox_info);

    MessageLoop();

    CefShutdown();

	return 0;
}
