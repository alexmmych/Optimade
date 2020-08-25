//This is the "Hooks" class, containing all of the hooks



class Hook {
private:
	Hook();
	~Hook();

	HHOOK MouseHook;

	static Hook* HookInstance;

	void SetHook();
	void UnSetHook();

public:

	static Hook* GetInstance() {
		if (!HookInstance) {
			HookInstance = new Hook();
		}
		return HookInstance;
	}



	HHOOK GetMouseHook() { return MouseHook; };

};

LRESULT CALLBACK MouseHookProc(int, WPARAM, LPARAM);