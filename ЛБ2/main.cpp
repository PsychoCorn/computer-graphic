#include "lib/interface/Interface.hpp"
#include <iostream>

kondraLib::Interface intrfc;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    intrfc.draw();

    SwapBuffers(GetDC(GetActiveWindow()));
}

void mouse(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    if (uMsg == WM_LBUTTONDOWN)
    {
        try
        {
            intrfc.checkButtons(x, winHeight - y);
        }
        catch(const kondraLib::ExitButtonListener&)
        {
            PostQuitMessage(0);
        }
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_PAINT:
        display();
        break;

    case WM_LBUTTONDOWN:
        mouse(message, wParam, lParam);
        break;


    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "OpenGLWindow";
    RegisterClass(&wc);

    hwnd = CreateWindowEx(0, "OpenGLWindow", winTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, winWidth, winHeight,
        NULL, NULL, GetModuleHandle(NULL), NULL);

    HDC hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR) };
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int format = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, format, &pfd);

    HGLRC hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);

    glClearColor(0.f, 0.f, 0.f, 0.f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, winWidth, 0, winHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        SwapBuffers(hdc);
        Sleep(fps); // frame lock 60 fps;
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    
    ReleaseDC(hwnd, hdc);
    
    return 0;
}
