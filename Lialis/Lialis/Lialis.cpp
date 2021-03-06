// Lialis.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lialis.h"
#include "Theme.h"
#include "MainProc.h"
#include "BuildProc.h"
#include "SettingsProc.h"
#include "ListView.h"
#include "Remote.h"
#include "Spawn.h"

#define FileName L"LialisClient.exe"
#define SearchTerm L"127.0.0.1\0"
#define SearchSize 9

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);



	Spawn s;
	//DWORD offset = s.CheckMemoryW(FileName, SearchTerm, SearchSize);
	//if (offset) {

		//if (s.ChangeMemory(FileName, L"192.168.7.25\0", offset, 13) == 0) {

			// Initialize global strings
			LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
			LoadStringW(hInstance, IDC_LIALIS, szWindowClass, MAX_LOADSTRING);

			MyRegisterClass(hInstance);

			// Perform application initialization:
			if (!InitInstance(hInstance, nCmdShow))
			{
				return FALSE;
			}

			//HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LIALIS));

			MSG msg;

			// Main message loop:
			while (GetMessage(&msg, nullptr, 0, 0))
			{
				//if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
				//{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				//}

			}

			return (int)msg.wParam;
		//}
	//}
}

ATOM MyRegisterClass(HINSTANCE hInstance) //register all custom buttons and windows. 
{
    

	WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = sizeof(Theme::MData);
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LIALIS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(0x2C, 0x2C, 0x2C));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LIALIS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	Theme::RClass(wcex.style, RemoteProc, hInstance,
		wcex.hCursor, wcex.hIcon, wcex.hbrBackground, L"Remote Desktop", L"Remote", sizeof(Remote::RemoteSession));

	Theme::RClass(wcex.style, DrawProc, hInstance,
		wcex.hCursor, wcex.hIcon, wcex.hbrBackground, L"Remote Desktop", L"RemoteDraw", sizeof(Remote::RemoteSession));

	Theme::RClass(wcex.style, Theme::buttonProc, hInstance,
		wcex.hCursor, wcex.hIcon,
		wcex.hbrBackground, NULL, L"CBUTTON", sizeof(Theme::CData));

	Theme::RClass(wcex.style, BuildProc, hInstance, wcex.hCursor, wcex.hIcon,
		wcex.hbrBackground, L"Stub Creation", L"StubCreation", sizeof(Theme::Build));
	
	Theme::RClass(wcex.style, Theme::ListViewButtonProc, hInstance, wcex.hCursor, wcex.hIcon,
		wcex.hbrBackground, NULL, L"LVBUTTON", sizeof(Theme::ListViewButton));

	Theme::RClass(wcex.style, SettingsProc, hInstance, wcex.hCursor, wcex.hIcon,
		wcex.hbrBackground, L"Settings", L"Settings", sizeof(Theme::Settings));

	Theme::RClass(wcex.style, (WNDPROC)ListViewProc, hInstance, wcex.hCursor, wcex.hIcon,
		/*CreateSolidBrush(RGB(0x0F, 0x2C, 0x2C))*/wcex.hbrBackground, NULL, L"LV", sizeof(Theme::ListView));


	Theme::RClass(wcex.style | CS_DBLCLKS, Theme::editProc, hInstance, LoadCursor(nullptr, IDC_IBEAM) , wcex.hIcon,
		wcex.hbrBackground, NULL, L"CEDIT", sizeof(Theme::CData));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) //initialize the main window
{
	RECT rect;
	GetClientRect(GetDesktopWindow(), &rect);
	Theme::SCREEN_HEIGHT = rect.bottom;
	Theme::SCREEN_WIDTH = rect.right;

	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_POPUP, (rect.right - 800) / 2,
		(rect.bottom - 350) / 2, 800, 345, GetDesktopWindow(), nullptr, hInstance, nullptr);

	//CreateWindow(L"Remote", L"Remote Session", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, nullptr, (HINSTANCE)GetModuleHandle(NULL), nullptr);
   // HWND hWnd1 = CreateWindow(L"Remote", L"Remote", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, nullptr,(HINSTANCE)GetModuleHandle(NULL), nullptr);




		if (!hWnd)
		{
			return FALSE;
		}
		//  SetWindowLongPtr(hWnd, GWL_STYLE, WS_BORDER | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);
		//ShowWindow(hWnd1, nCmdShow);
		//UpdateWindow(hWnd1);

		return TRUE;
	
}




