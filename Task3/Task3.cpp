// Task3.cpp : Определяет точку входа для приложения.
//

#pragma warning(disable:4996)

#include "framework.h"
#include "Task3.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна


int timerId;
int width, height;
RECT windowRect;
bool needRead = true;
bool doMove = true;
bool doMove_ = true;
RectangleShape border(Point(10, 10), Point(30, 30));

VectorOfShapes shapes;
CircleShape* redactShape;

HWND hButtonStart, hButtonStop;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    SettingsProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TASK3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TASK3));

    MSG msg;

    // Цикл основного сообщения:
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
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TASK3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TASK3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   hButtonStart = CreateWindow(L"BUTTON", L"START", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, hWnd, (HMENU)BUTTON_START, hInstance, NULL);

   hButtonStop = CreateWindow(L"BUTTON", L"STOP", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, hWnd, (HMENU)BUTTON_STOP, hInstance, NULL);

   //button

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case BUTTON_START:
                doMove = true;
                break;
            case BUTTON_STOP:
                doMove = false;
                break;
            case IDM_SAVE:
                shapes.Save();
                break;
            case IDM_LOAD:
                shapes.Load();
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_SIZE:
        GetClientRect(hWnd, &windowRect);
        width = windowRect.right - windowRect.left;
        height = windowRect.bottom - windowRect.top;
        border.SetWH(Point(width - 150, height - 20));
        InvalidateRect(hWnd, NULL, FALSE);
        MoveWindow(hButtonStart, width - 120, 100, 100, 20, TRUE);
        MoveWindow(hButtonStop, width - 120, 150, 100, 20, TRUE);
        break;
    case WM_CREATE:
        timerId = SetTimer(hWnd, MOVING_TIMER_ID, 10, NULL);
        //GetWindowRect(hWnd, &windowRect);
        GetClientRect(hWnd, &windowRect);
        width = windowRect.right - windowRect.left;
        height = windowRect.bottom - windowRect.top;
        redactShape = nullptr;

        if(needRead)
        {
            if (!shapes.Load())
            {
                PostQuitMessage(0);
                break;
            }
            needRead = false;
        }
        break;
    case WM_LBUTTONDBLCLK:
        redactShape = shapes.dblClick(LOWORD(lParam), HIWORD(lParam));
        if (redactShape)
        {
            doMove_ = doMove;
            doMove = false;
            DialogBox(hInst, MAKEINTRESOURCE(IDD_SETTINGS), hWnd, SettingsProc);
            redactShape->WithBorderRedact(border.GetX(), border.GetY(), border.GetWidth(), border.GetHeight());
            doMove = doMove_;
        }
        break;
    case WM_LBUTTONDOWN:
        shapes.lButtonDown(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_LBUTTONUP:
        shapes.lButtonUp();
        break;
    case WM_MOUSEMOVE:
        shapes.mouseMove(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_TIMER:
        if (wParam == timerId)
        {
            if(doMove)
                shapes.Update(border.GetX(), border.GetY(), border.GetWidth(), border.GetHeight());
        }
        InvalidateRect(hWnd, NULL, 1);
        break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        //Рисование
        border.Draw(hdc);
        shapes.Draw(hdc);

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

// Обработчик сообщений для окна настроек фигур.
INT_PTR CALLBACK SettingsProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetDlgItemInt(hDlg, IDC_EDIT_X, redactShape->GetX(), 0);
        SetDlgItemInt(hDlg, IDC_EDIT_Y, redactShape->GetY(), 0);
        SetDlgItemInt(hDlg, IDC_EDIT_R, redactShape->GetRadius(), 0);
        SetDlgItemInt(hDlg, IDC_EDIT_W, redactShape->GetWeight(), 0);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDOK:
            {
                int x = GetDlgItemInt(hDlg, IDC_EDIT_X, 0, 0);
                int y = GetDlgItemInt(hDlg, IDC_EDIT_Y, 0, 0);
                int r = GetDlgItemInt(hDlg, IDC_EDIT_R, 0, 0);
                int w = GetDlgItemInt(hDlg, IDC_EDIT_W, 0, 0);

                shapes.SettingsShape(redactShape, x, y, r, w);
            }
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        default:
            break;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Обработчик сообщений для окна "О программе".
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
