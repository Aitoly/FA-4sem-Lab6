
// Task1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Task1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hButtonStart, hButtonStop;
int timerId;
TimeClass timeClass;
bool isGo;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_TASK1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TASK1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASK1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TASK1);
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
      CW_USEDEFAULT, 0, 320, 200, nullptr, nullptr, hInstance, nullptr);

   timeClass.hWEditDate = CreateWindowEx( WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
       EDIT_DATE_X, 30, 25, 25, hWnd, (HMENU)EDIT_DATE, hInstance, nullptr);

   timeClass.hWEditMounth = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
       EDIT_MOUNTH_X, 30, 25, 25, hWnd, (HMENU)EDIT_MOUNTH, hInstance, nullptr);

   timeClass.hWEditYear = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
       EDIT_YEAR_X, 30, 50, 25, hWnd, (HMENU)EDIT_YEAR, hInstance, nullptr);

   timeClass.hWEditHours = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
       EDIT_HOURS_X, 30, 25, 25, hWnd, (HMENU)EDIT_HOURS, hInstance, nullptr);

   timeClass.hWEditMin = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
       EDIT_MIN_X, 30, 25, 25, hWnd, (HMENU)EDIT_MIN, hInstance, nullptr);

   timeClass.hWEditSec = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
       EDIT_SEC_X, 30, 25, 25, hWnd, (HMENU)EDIT_SEC, hInstance, nullptr);

   timeClass.hWEditMSec = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
       EDIT_MSEC_X, 30, 40, 25, hWnd, (HMENU)EDIT_MSEC, hInstance, nullptr);

   timeClass.hEditTimerSec = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
       EDIT_SEC_X, 60, 25, 25, hWnd, (HMENU)EDIT_TIMERSEC, hInstance, nullptr);

   timeClass.hEditTimerMSec = CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_NUMBER,
       EDIT_MSEC_X, 60, 40, 25, hWnd, (HMENU)EDIT_TIMERMSEC, hInstance, nullptr);

   hButtonStart = CreateWindow(L"BUTTON", L"START", WS_CHILD | WS_VISIBLE, 40, 100, 100, 20, hWnd, (HMENU)BUTTON_START, hInstance, NULL);

   hButtonStart = CreateWindow(L"BUTTON", L"STOP", WS_CHILD | WS_VISIBLE, 180, 100, 100, 20, hWnd, (HMENU)BUTTON_STOP, hInstance, NULL);


   timeClass.GetNowTime();
   timeClass.SetTimeForWindow();

   if (!hWnd)
   {
      return FALSE;
   }

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
            case IDM_SETNOWTIME:
                timeClass.GetNowTime();
                timeClass.SetTimeForWindow();
                break;
            case BUTTON_START:
                if (timeClass.GetTimeFromWindow() && !isGo)
                {
                    timerId = SetTimer(hWnd, MOVING_TIMER_ID, timeClass.edit_msec, NULL);
                    isGo = true;
                }
                break;
            case BUTTON_STOP:
                if (isGo)
                {
                    KillTimer(hWnd, MOVING_TIMER_ID);
                    isGo = false;
                }
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_CREATE:
        timerId = 0;
        isGo = false;
        break;
    case WM_TIMER:
        if (wParam == timerId)
        {
            timeClass.PlusTime();
            timeClass.SetTimeForWindow();
        }
        InvalidateRect(hWnd, NULL, 1);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            TextOut(hdc, EDIT_DATE_X, 10, L"Date(dd.mm.yyyy  hh:mm:sec:msec):", sizeof(L"Date(dd.mm.yyyy  hh:mm:sec:msec):") / 2);
            TextOut(hdc, EDIT_DATE_X + 26, 40, L".", sizeof(L".")/2);
            TextOut(hdc, EDIT_MOUNTH_X + 26, 40, L".", sizeof(L".") / 2);

            TextOut(hdc, EDIT_HOURS_X + 26, 35, L":", sizeof(L":") / 2);
            TextOut(hdc, EDIT_MIN_X + 26, 35, L":", sizeof(L":") / 2);
            TextOut(hdc, EDIT_SEC_X + 26, 35, L":", sizeof(L":") / 2);

            TextOut(hdc, EDIT_SEC_X + 26, 35, L":", sizeof(L":") / 2);

            TextOut(hdc, EDIT_DATE_X, 65, L"Timer`s interval(sec:msec):", sizeof(L"Timer`s interval(sec:msec):") / 2);
            EndPaint(hWnd, &ps);
        }
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
