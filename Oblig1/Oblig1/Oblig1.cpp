// Oblig1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Oblig1.h"

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
    LoadStringW(hInstance, IDC_OBLIG1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OBLIG1));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBLIG1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OBLIG1);
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
    static BOOL isMouseButtonDown;
    static POINT positionGreen{ 25,25 };
    static POINT positionYellow{ 25,25 };
    static POINT positionRed{ 25,25 };
    static POINT position{ 200,200 };
    static POINT position2{ 500,0 };
    static int teller{ 1 };

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
        
    case WM_LBUTTONDOWN:
    {
        isMouseButtonDown = true;

    }
      
    case WM_LBUTTONUP:{
           isMouseButtonDown = false;
    }

    case WM_CREATE: SetTimer(hWnd,0,200,0);
        break;
    case WM_TIMER:
               RECT rect;
            GetClientRect(hWnd, &rect);
    

        while (teller == 1) {
            position.x += 10;
        }
        while(teller == 3) {
            position2.y += 10;
        }

        while(teller == 2) {
            position.x += 10;
            position2.y += 10;

        }
        if (isMouseButtonDown == true) {
            teller++;
            Sleep(100);
        }
        if(isMouseButtonDown == false) {
            teller++;
            Sleep(100);
        }

        if (teller == 4) {
            teller = 1;
        }

        InvalidateRect(hWnd, 0, true);
        break;

        
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            HBRUSH hbrushBackground = CreateSolidBrush(RGB(90, 90, 90));
            HGDIOBJ hOriginal = SelectObject(hdc, hbrushBackground);
            Rectangle(hdc,10, 15, 85, 150);

            HBRUSH hbrushBackground2 = CreateSolidBrush(RGB(90, 90, 90));
            SelectObject(hdc, hbrushBackground2);
            Rectangle(hdc, 80, 15, 150, 150);
           

           
           
            if (teller <= 1) {

                HBRUSH hbrushTrafficklight = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, hbrushTrafficklight);
                Ellipse(hdc, 30, 25, 60, 60);


                HBRUSH hbrushTrafficklight2 = CreateSolidBrush(RGB(0, 255, 0));
                SelectObject(hdc, hbrushTrafficklight2);

                Ellipse(hdc, 130, 25, 100, 60);


                DeleteObject(hbrushTrafficklight);
                DeleteObject(hbrushTrafficklight2);

            }
            if (teller == 2) {

                HBRUSH hbrushTrafficklight = CreateSolidBrush(RGB(255, 255, 0));
                SelectObject(hdc, hbrushTrafficklight);
                Ellipse(hdc, 30, 40, 60, 70);


                HBRUSH hbrushTrafficklight2 = CreateSolidBrush(RGB(255, 255, 0));
                SelectObject(hdc, hbrushTrafficklight2);

                Ellipse(hdc, 130, 40, 100, 70);

                DeleteObject(hbrushTrafficklight);
                DeleteObject(hbrushTrafficklight2);

            }
            if (teller == 3) {

                HBRUSH hbrushTrafficklight = CreateSolidBrush(RGB(0, 255, 0));
                SelectObject(hdc, hbrushTrafficklight);
                Ellipse(hdc, 30, 60, 60, 80);


                HBRUSH hbrushTrafficklight2 = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, hbrushTrafficklight2);

                Ellipse(hdc, 130, 60, 100, 80);

                DeleteObject(hbrushTrafficklight);
                DeleteObject(hbrushTrafficklight2);

            }


           

          

            HBRUSH hbrushroad1 = CreateSolidBrush(RGB(90, 90, 90));
            SelectObject(hdc, hbrushroad1);
            Rectangle(hdc, 600, 0, 550, 450);

            HBRUSH hbrushroad2 = CreateSolidBrush(RGB(90, 90, 90));
            SelectObject(hdc, hbrushroad2);
            Rectangle(hdc, 200, 195, 950, 140);

           


            if (isMouseButtonDown == false) {
                HBRUSH hbrushBil = CreateSolidBrush(RGB(0, 0, 0));
                HGDIOBJ hOriginalBil = SelectObject(hdc, hbrushBil);

                Rectangle(hdc, position.x, 190, position.x - 10, 160);

                DeleteObject(hbrushBil);


                HBRUSH hbrushBil2 = CreateSolidBrush(RGB(0, 0, 0));
                HGDIOBJ hBil2 = SelectObject(hdc, hbrushBil2);

                Rectangle(hdc, 550, position2.y -10, 600, position2.y);

                DeleteObject(hbrushBil2);
                Sleep(100);
            }
        

            


            SelectObject(hdc,hOriginal);
            DeleteObject(hbrushBackground);
            DeleteObject(hbrushBackground2);
          


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
