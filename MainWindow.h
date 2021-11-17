#pragma once
#define MAX_LOADSTRING 100
class MainWindow
{
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
	static ATOM MyRegisterClass(HINSTANCE hInstance);
	MainWindow();
	~MainWindow();
public:
	static BOOL InitInstance(HINSTANCE, int);
};

