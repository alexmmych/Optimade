#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/Hook.h"
#include "../HeaderFiles/Window.h"



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
	if (nCode == 0) {

		switch (wParam) {
		case WM_MOUSEMOVE: {

		}

		}
	}

	return CallNextHookEx(Hook::GetInstance()->GetMouseHook(), nCode, wParam, lParam);
}

