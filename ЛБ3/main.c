#include "lib/game.h"

game_t game;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    game_draw(&game);

    SwapBuffers(GetDC(GetActiveWindow()));
}

void mouse(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int x = LOWORD(lParam);
    int y = HIWORD(lParam);
    switch (uMsg)
    {
    case WM_LBUTTONDOWN:
        interface_check_buttons(&game.interf, x, WIN_HEIGHT - y);
        break;
    
    default:
        break;
    }
}

void key_down(WPARAM wParam)
{
    switch (wParam)
    {
    case VK_RIGHT:
        character_walk_right(&game.charac);
        break;

    case VK_LEFT:
        character_walk_left(&game.charac);
        break;
    
    default:
        break;
    }
}

void key_up(WPARAM wParam)
{
    switch (wParam)
    {
    case VK_RIGHT:
        character_stop(&game.charac);
        break;

    case VK_LEFT:
        character_stop(&game.charac);
        break;
    
    default:
        break;
    }
}

void close()
{
    for (int i = 0; i < 3; ++i)
    {
        free(game.charac.animations[i].frame_coords);
    }
    PostQuitMessage(0);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        close();
        break;

    case WM_PAINT:
        display();
        Sleep(sleep_time);
        break;

    case WM_LBUTTONDOWN:
        mouse(message, wParam, lParam);
        break;

    case WM_KEYDOWN:
        key_down(wParam);
        break;
    
    case WM_KEYUP:
        key_up(wParam);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // _setmaxstdio(10 << 20);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "OpenGLWindow";
    RegisterClass(&wc);

    hwnd = CreateWindowEx(0, "OpenGLWindow", WIN_TITLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, WIN_WIDTH, WIN_HEIGHT + 39, 
        NULL, NULL, GetModuleHandle(NULL), NULL);
        // 39 is a magic number) this is the size of the title bar that I got with GetClientRect function
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

    glClearColor(0.1f, 0.3f, 0.15f, 1.f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WIN_WIDTH, 0, WIN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    ShowWindow(hwnd, SW_SHOWDEFAULT);

    MSG msg = {};
    game = game_new();
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        SwapBuffers(hdc);
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    
    ReleaseDC(hwnd, hdc);
    
    return 0;
}