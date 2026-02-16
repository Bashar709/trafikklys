// trafikklys.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "trafikklys.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
    LoadStringW(hInstance, IDC_TRAFIKKLYS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRAFIKKLYS));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRAFIKKLYS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TRAFIKKLYS);
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
        // begynne me vei
        // so trafikklyset

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rc;
        GetClientRect(hWnd, &rc);

        int width = rc.right - rc.left;
        int height = rc.bottom - rc.top;

        int cx = width / 2;   // midten av vinduet
        int cy = height / 2;

        int roadHalf = 50;    // halv bredde på veien

        // Veifarge
        HBRUSH hRoad = CreateSolidBrush(RGB(200, 200, 200));

        // Horisontal vei
        RECT hRoadRect = { 0, cy - roadHalf, width, cy + roadHalf };
        FillRect(hdc, &hRoadRect, hRoad);

        // Vertikal vei
        RECT vRoadRect = { cx - roadHalf, 0, cx + roadHalf, height };
        FillRect(hdc, &vRoadRect, hRoad);
        DeleteObject(hRoad);

       // Størrelse på trafikklys
        int tlWidth = 30;
        int tlHeight = 80;

        // Pensler
        HBRUSH hRed = CreateSolidBrush(RGB(220, 50, 50));
        HBRUSH hYellow = CreateSolidBrush(RGB(230, 200, 50));
        HBRUSH hGreen = CreateSolidBrush(RGB(60, 200, 80));

        // Vvenstre lys
        int leftTLX = cx - roadHalf - tlWidth - 60;
        int leftTLY = cy - tlHeight / 2;

        SelectObject(hdc, hRed);
        Ellipse(hdc, leftTLX + 5, leftTLY + 5, leftTLX + tlWidth - 5, leftTLY + 25);

        SelectObject(hdc, hYellow);
        Ellipse(hdc, leftTLX + 5, leftTLY + 30, leftTLX + tlWidth - 5, leftTLY + 50);

        SelectObject(hdc, hGreen);
        Ellipse(hdc, leftTLX + 5, leftTLY + 55, leftTLX + tlWidth - 5, leftTLY + 75);


        // hori linja
        int topTLX = cx - 60;
        int topTLY = cy - roadHalf - 100;

        SelectObject(hdc, hRed);
        Ellipse(hdc, topTLX + 5, topTLY + 5, topTLX + 25, topTLY + 25);

        SelectObject(hdc, hYellow);
        Ellipse(hdc, topTLX + 30, topTLY + 5, topTLX + 50, topTLY + 25);

        SelectObject(hdc, hGreen);
        Ellipse(hdc, topTLX + 55, topTLY + 5, topTLX + 75, topTLY + 25);

        DeleteObject(hRed);
        DeleteObject(hYellow);
        DeleteObject(hGreen);
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
