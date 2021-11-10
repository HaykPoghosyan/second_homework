// HelloWorld.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "HelloWorld.h"

#include <vector>

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
    LoadStringW(hInstance, IDC_HELLOWORLD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HELLOWORLD));

    SetTimer(NULL, 0, 1000, (TIMERPROC)&WndProc);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HELLOWORLD));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HELLOWORLD);
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

void paint(HWND hWnd) {
    PAINTSTRUCT ps;
    RECT rect;
    GetClientRect(hWnd, &rect);//Get the size of the customer are
    InvalidateRect(hWnd, &rect, false);
    HDC hdc = BeginPaint(hWnd, &ps);

    std::vector<HBITMAP> hOrgBitmap;
  /*  static COLORREF bkcolor = RGB(0, 255, 0);
    SetDCBrushColor(hdc, bkcolor);*/

    HBITMAP hOldBitmap[10];
    int height, width;

    height = rect.bottom - rect.top;
    width = rect.right - rect.left;

    HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(DC_BRUSH));
    SYSTEMTIME st, lt;
    GetLocalTime(&lt); //get Time

    int hour = lt.wHour;
    int min = lt.wMinute;
    int sec = lt.wSecond;

    //Load picture
    if (hour < 10) {
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1)));
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1 + hour)));
    }
    else {
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1 + hour / 10)));
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1 + hour % 10)));
    }

    hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 11)));

    if (min < 10) {
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1)));
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1 + min)));
    }
    else {
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1 + min / 10)));
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1 + min % 10)));
    }

    hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 11)));

    if (sec < 10) {
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1)));
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1 + sec)));
    }
    else {
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1 + sec / 10)));
        hOrgBitmap.push_back((HBITMAP)::LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP + 1 + sec % 10)));
    }
    //Create a compatible DC (memory DC) of the current context
    HDC hDrawDC = ::CreateCompatibleDC(hdc);

    //Create a compatible DC (memory DC) of the current context

    //Load bitmap to memory DC
    for (int i = 0; i < 8; i++) {
        HDC hDrawDC = ::CreateCompatibleDC(hdc);
        hOldBitmap[i] = (HBITMAP)::SelectObject(hDrawDC, hOrgBitmap[i]);

        ::BitBlt(hdc, width / 4 + (35 * (i + 1)), height / 2 - 24, 48, 48, hDrawDC, 0, 0, SRCCOPY);

        //Restore memory original data
        ::SelectObject(hDrawDC, hOldBitmap[i]);

        //Delete resources to prevent leakage
        ::DeleteObject(hOrgBitmap[i]);
    }
    ::DeleteDC(hDrawDC);
    EndPaint(hWnd, &ps);
    OutputDebugStringW(L"This will go to the output.\n");

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_TIMER:
        {
            paint(hWnd);
        }
        break;
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
            paint(hWnd);  
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
