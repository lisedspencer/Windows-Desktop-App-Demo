/*
* Name: Kacy Spencer
* Course: COP 3003 Programming II, CRN 80601
* Date: 8/30/21
* Filename: HellowWindowsApp.cpp
* Description: Follows Windows desktop app walkthrough found @ 
* https://docs.microsoft.com/en-us/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp?view=msvc-160
*/

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

//GLOBAL VARIABLES
//main window class name
static TCHAR szWindowClass[] = _T("DesktopApp");
//title bar text string
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");
HINSTANCE hInst;

//Function Prototypes
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//begin main
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	//WINDCLASSEX Structure
	//Contains details on window, title, color, etc & pointer to window procedure (WndProc)
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	//Register wcex
	if (!RegisterClassEx(&wcex)) {
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Windows Desktop Guided Tour"), NULL);
		return 1;
	}

	//Store instance handle in global variable
	hInst = hInstance;

	//Create window
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,			//opt extended window style
		szWindowClass,					//name of app
		szTitle,						//text in title bar
		WS_OVERLAPPEDWINDOW,			//type of window to create
		CW_USEDEFAULT, CW_USEDEFAULT,	//initial position (x,y)
		500, 100,						//initial size (width, length)
		NULL,							//parent of window
		NULL,							//handle to menu (not used here)
		hInstance,						//handle to instance of module associated w window (first param from WinMain)
		NULL							//pointer to value passed by CREATESTRUCT (not used here)
	);
	//check window created sucessfully
	if (!hWnd) {
		MessageBox(NULL, _T("Call to CreateWindowEx failed!"), _T("Windows Desktop Guided Tour"), NULL);
		return 1;
	}

	//Display window
	//args:	(value returned by CreateWindow, fourth param of WinMain)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//Window now visible, but is not handling messages (WndProc not used yet)

	//Message loop: listens for events from Windows & sends to WndProc for handling
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);	//translates virtual-key msgs to ASCII character msgs
		DispatchMessage(&msg);	//sends pointed to structure to WndProc
	}

	return (int)msg.wParam;
}

	

//Window Procedure Function, handles messages to window
LRESULT CALLBACK WndProc(
	_In_ HWND hWnd,
	_In_ UINT message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, Dolly!");

	switch (message) {
	//WM_PAINT - msg from windows saying the application window must be re-drawn
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//APPLICATION LAYOUT
		//Build application display, buttons, text, etc.
		TextOut(hdc, 5, 5, greeting, _tcslen(greeting));

		//END APP LAYOUT
		EndPaint(hWnd, &ps);
		break;
	//WM_DESTROY - "Exit" button was clicked
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	} //end switch

	return 0;
}
