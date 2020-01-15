// RobSurgical_GUI.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "framework.h"
#include "RobSurgical_GUI.h"

#include <stdio.h>
#include <cwchar>
#include <cstdio>

#define MAX_LOADSTRING 100

using namespace std;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//EF mod
//A code to create a default empty Edit Control
HWND CreateTextBox(CONST INT iX, CONST INT iY, CONST UINT uWidth, CONST UINT uHeight, HWND hWnd, CONST UINT uId, HINSTANCE hInstance)
{
	HWND hWndRet = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), NULL, WS_CHILD, iX, iY, (signed)uWidth, (signed)uHeight, hWnd, (HMENU)uId, hInstance, NULL);
	SetBkColor(GetDC(hWndRet), RGB(0, 255, 255));
	return hWndRet;
}

//Forward declaration
bool createAppLayout(HWND *hWnd);
//-----------------------------

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ROBSURGICALGUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROBSURGICALGUI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROBSURGICALGUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ROBSURGICALGUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   createAppLayout(&hWnd);//EF mod

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...

            EndPaint(hWnd, &ps);
        }
        break;

	case WM_CTLCOLORSTATIC:
		{
		COLORREF crBk = RGB(255, 0, 0); // use RED for Background.
		SetBkColor(GetDC(hWnd), crBk); // Set to red
		}
		break;
	case WM_CTLCOLOREDIT:
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

bool createAppLayout(HWND *hWnd) {
	int x = ix_start;//first col
	int y = iy_start;//first row

	//------------------Buttons control section (5th col)----------------------------
	y += 4 * iy_inc;//Jump to 5th col

	//Create a button: SEND
	HWND hwndButton_Send = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"SEND",	// Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,		// Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	x += 3*ix_inc;//Jump to 4th row

	 //Create a button: STOP
	HWND hwndButton_Stop = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"STOP",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	//----------------STATIC control section (first col)----------------------
	x = ix_start;//first col
	y = iy_start;//first row

	HWND hwndText_ControlWordSend = CreateWindow(
		L"STATIC",  // Predefined class; Unicode assumed 
		L"Controlword",      // Text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.
	SetBkColor(GetDC(hwndText_ControlWordSend), RGB(255, 255, 255));//White background
	SetTextColor(GetDC(hwndText_ControlWordSend), RGB(0, 0, 0));//Black Text

	y += iy_inc;//Jump one row

	HWND hwndText_TargetPositionSend = CreateWindow(
		L"STATIC",  // Predefined class; Unicode assumed 
		L"Target Position",      // Text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_TargetVelocitySend = CreateWindow(
		L"STATIC",  // Predefined class; Unicode assumed 
		L"Target Velocity",      // Text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_OperationModeSend = CreateWindow(
		L"STATIC",  // Predefined class; Unicode assumed 
		L"Operation Mode",      // Text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.		 
	//---------------------------------------------------------


	//---------------EDIT controls section (second col)-----------
	x = ix_start + ix_inc;//second col
	y = iy_start;//first row

	HWND hwndText_ControlWordValueSend = CreateWindow(
		L"EDIT",  // Predefined class; Unicode assumed 
		editControlDefaultDecimal,      // default text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,   // Text width
		defaultHeight,	// Text height
		*hWnd,			// Parent window
		NULL,			// No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);			// Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_TargetPositionValueSend = CreateWindow(
		L"EDIT",  // Predefined class; Unicode assumed 
		editControlDefaultDecimal,      // default text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,   // Text width
		defaultHeight,	// Text height
		*hWnd,			// Parent window
		NULL,			// No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);			// Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_TargetVelocityValueSend = CreateWindow(
		L"EDIT",  // Predefined class; Unicode assumed 
		editControlDefaultDecimal,      // default text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,   // Text width
		defaultHeight,	// Text height
		*hWnd,			// Parent window
		NULL,			// No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);			// Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_OperationModeValueSend = CreateWindow(
		L"EDIT",  // Predefined class; Unicode assumed 
		editControlDefaultDecimal,      // default text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,   // Text width
		defaultHeight,	// Text height
		*hWnd,			// Parent window
		NULL,			// No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);			// Pointer not needed.
	
	//----------------STATIC control section (third col)----------------------
	x = ix_start + 2*ix_inc;//first col
	y = iy_start;//first row

	HWND hwndText_StatusWordRcv = CreateWindow(
		L"STATIC",  // Predefined class; Unicode assumed 
		L"StatusWord",      // Text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_PositionActualRcv = CreateWindow(
		L"STATIC",  // Predefined class; Unicode assumed 
		L"Position actual",      // Text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_VelocityActualRcv = CreateWindow(
		L"STATIC",  // Predefined class; Unicode assumed 
		L"Velocity actual",      // Text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_OperationModeRcv = CreateWindow(
		L"STATIC",  // Predefined class; Unicode assumed 
		L"Operation Mode display",      // Text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,// Width
		defaultHeight,// Height
		*hWnd,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);      // Pointer not needed.		 
	//---------------------------------------------------------
	
	//---------------EDIT controls section (fourth col)-----------
	x = ix_start + 3*ix_inc;//fourth col
	y = iy_start;//first row

	HWND hwndText_StatusWordValueRcv = CreateWindow(
		L"EDIT",  // Predefined class; Unicode assumed 
		editControlDefaultDecimal,      // default text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,   // Text width
		defaultHeight,	// Text height
		*hWnd,			// Parent window
		NULL,			// No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);			// Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_PositionActualValueRcv = CreateWindow(
		L"EDIT",  // Predefined class; Unicode assumed 
		editControlDefaultDecimal,      // default text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,   // Text width
		defaultHeight,	// Text height
		*hWnd,			// Parent window
		NULL,			// No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);			// Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_VelocityActualValueRcv = CreateWindow(
		L"EDIT",  // Predefined class; Unicode assumed 
		editControlDefaultDecimal,      // default text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,   // Text width
		defaultHeight,	// Text height
		*hWnd,			// Parent window
		NULL,			// No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);			// Pointer not needed.

	y += iy_inc;//Jump one row

	HWND hwndText_OperationModeValueRcv = CreateWindow(
		L"EDIT",  // Predefined class; Unicode assumed 
		editControlDefaultDecimal,      // default text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_TEXT,  // Styles 
		x,			// x position 
		y,			// y position 
		defaultWidth,   // Text width
		defaultHeight,	// Text height
		*hWnd,			// Parent window
		NULL,			// No menu.
		(HINSTANCE)GetWindowLong(*hWnd, GWL_HINSTANCE),
		NULL);			// Pointer not needed.

	//MessageBox sample
	/*LPCWSTR a = L"TestWindow";
	LPCWSTR b = L"TestTitleWindow";
	MessageBox(hWnd, a, b, MB_OK | MB_ICONQUESTION);*/
	

	//TODO: return logics
	return true;
}
