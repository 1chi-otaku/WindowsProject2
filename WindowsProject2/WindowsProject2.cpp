// WindowsProject2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProject2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);   //Registers the window class
BOOL                InitInstance(HINSTANCE, int);           //Init. the windows class
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);    //Process of window.
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);      //Popup "About"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);             //Loads a string resource from the executable file
    LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

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
    WNDCLASSEXW wcex;                                                                   //Creating object of structure WNDCLASSEXW
                                                                                            
    wcex.cbSize = sizeof(WNDCLASSEX);                                                   //cbSize specifies the size of the structure

    wcex.style          = CS_HREDRAW | CS_VREDRAW;                                      //Sets style of the win.
    wcex.lpfnWndProc    = WndProc;                                                      //Takes the pointer to the window procedure, in our case it's WndProc fun.
    wcex.cbClsExtra     = 0;                                                            //Sets size of extra bytes that will be allocated for class and for each window instance accordingly.
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;                                                    //A module descriptor. We specify the module descriptor as a function argument so that the system knew in which module to look for these resources.
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));    //A handle to the class icon. If NULL systems sets an icon by default.
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);                               //A handle to the class cursor. If NULL systems sets a cursor by default.
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                                     //Painting the bakcground colour.
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);                        //Sets the resource name of the class menu, as the name appears in the resource file. 
    wcex.lpszClassName  = szWindowClass;                                                           
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));         //Sets the small icon that appear in the right left corner, if NULL sets a default icon.

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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);        //Sets to the descriptor the window.

   if (!hWnd)                   //If fails, returns FALSE.
   {
       return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);                                                        //Shows window
   UpdateWindow(hWnd);                                                                //Updates the window if necessary

   return TRUE;                                                                       // If worked successfull, return TRUE
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)     //Process function.
{
    switch (message)                                                                //Checks the message input
    {
    case WM_COMMAND:                                                                //If the user selects a command item from a menu such as "About" or "Help".
        {
            int wmId = LOWORD(wParam);                                              //Var. to identify the option user choose 
            // Parse the menu selections:
            switch (wmId)           
            {
            case IDM_ABOUT:                                                         //If it's about option
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);       //Calls dialog box for "About"
                break;
            case IDM_EXIT:                                                          //If it's EXIT
                DestroyWindow(hWnd);                                                //Close the window
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;  
    case WM_PAINT:                                                                   //Message is sent when the system or another application makes a request to paint a portion of an application's window.
        {
            PAINTSTRUCT ps;                                                          //Creating object of PAINTSTRUCT structure
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:                                                                //Message is sent when the user closes the window by any way                    
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)       //About box
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)                                                                //Checks the message.
    {
    case WM_INITDIALOG:                                                             //Message for initializing controls and performing any other initialization tasks that affect the appearance of the dialog box.
        return (INT_PTR)TRUE;

    case WM_COMMAND:                                                                //Sent when the user selects a command item from a menu
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)                   //Checks if the about is closed by any way
        {
            EndDialog(hDlg, LOWORD(wParam));                                //Closes "About" information
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;                                                          //Return FALSE on failure
}
