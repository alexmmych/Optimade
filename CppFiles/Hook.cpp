#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/Hook.h"
#include "../HeaderFiles/Window.h"

Hook* Hook::HookInstance = nullptr;

Hook::Hook() {
	SetHook();
}

Hook::~Hook(){
	HookInstance = nullptr;
	UnSetHook();
}

void Hook::SetHook() {
	MouseHook = SetWindowsHookExW(WH_MOUSE_LL, MouseHookProc, NULL, 0);
}

void Hook::UnSetHook() {
	UnhookWindowsHookEx(MouseHook);
}


LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;

	if (nCode == 0) {

		switch (wParam) {
		case WM_MOUSEMOVE: {
			std::cout << "Mouse position is: x = " << pMouseStruct->pt.x << " | y = " << pMouseStruct->pt.y << std::endl;
			break;
		}
		case WM_LBUTTONDOWN: {
			std::cout << "CLICKED!" << std::endl;
			SendMessageW(Window::GetInstance()->GetWindowHandle(), WM_NCHITTEST, NULL, MAKELPARAM(pMouseStruct->pt.x , pMouseStruct->pt.y));
			break;
		}
		}
	}

	return CallNextHookEx(Hook::GetInstance()->GetMouseHook(), nCode, wParam, lParam);
}

