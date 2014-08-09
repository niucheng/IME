#include <windows.h>

static char g_szClassName[] = "IMEClass";
static HINSTANCE g_hInst = NULL;

#define IDC_MAIN_TEXT   1001


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_CREATE:
            CreateWindow("EDIT", "",
                         WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL
                         | ES_MULTILINE | ES_WANTRETURN,
                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                         hwnd, (HMENU)IDC_MAIN_TEXT, g_hInst, NULL);
            break;
        case WM_SIZE:
            if(wParam != SIZE_MINIMIZED)
                MoveWindow(GetDlgItem(hwnd, IDC_MAIN_TEXT), 0, 0, LOWORD(lParam),
                           HIWORD(lParam), TRUE);
            break;
        case WM_SETFOCUS:
            SetFocus(GetDlgItem(hwnd, IDC_MAIN_TEXT));
            break;
        case WM_COMMAND:
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX WndClass;
    HWND hwnd;
    MSG Msg;

    g_hInst = hInstance;

    WndClass.cbSize        = sizeof(WNDCLASSEX);
    WndClass.style         = 0;
    WndClass.lpfnWndProc   = WndProc;
    WndClass.cbClsExtra    = 0;
    WndClass.cbWndExtra    = 0;
    WndClass.hInstance     = g_hInst;
    WndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    WndClass.lpszMenuName  = "";
    WndClass.lpszClassName = g_szClassName;
    WndClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&WndClass))
    {
        MessageBox(0, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                          g_szClassName,
                          "File Editor Example Program",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT, 320, 240,
                          NULL, NULL, g_hInst, NULL);

    if (hwnd == NULL)
    {
        MessageBox(0, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
