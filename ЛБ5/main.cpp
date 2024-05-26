#include <cmath>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "camera.h"

int numOfCells = 8;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void windowResize(int, int);
void moveCamera();
void drawTriangle(float);
void drawFloor(float, float);
void drawAxes(int, int);
void drawChessBoard(float, float, int = 8);
void drawChessBoard(WPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wcex = { 
        .cbSize = sizeof(WNDCLASSEX), .style = CS_OWNDC, 
        .lpfnWndProc = WindowProc, .cbClsExtra = 0, .cbWndExtra = 0,
        .hInstance = hInstance, .hIcon = LoadIcon(NULL, IDI_APPLICATION),
        .hCursor = LoadCursor(NULL, IDC_ARROW), .hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH),
        .lpszMenuName = NULL, .lpszClassName = "ComputerGraphic", 
        .hIconSm = LoadIcon(NULL, IDI_APPLICATION)
     };
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    if (!RegisterClassEx(&wcex)) return 0;
    hwnd = CreateWindowEx(
        0, "ComputerGraphic", "Lab 5",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
        CW_USEDEFAULT, 800, 600, NULL, NULL,
        hInstance, NULL
    );
    ShowWindow(hwnd, nCmdShow);
    ShowCursor(FALSE);
    RECT windowRect;
    GetClientRect(hwnd, &windowRect);
    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;
    windowResize(windowRect.right, windowRect.bottom);
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;
    hDC = GetDC(hwnd);
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, iFormat, &pfd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);
    while (!bQuit) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) bQuit = TRUE;
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            glClearColor(204.f / 255.f, 254.f / 255.f, 255.f / 255.f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(45.0f, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            Camera_Apply();
            glPushMatrix();
            drawFloor(200, 200);
            glPopMatrix();
            glPushMatrix();
            drawTriangle(theta);
            glPopMatrix();
            glPushMatrix();
            drawChessBoard(5.0f, 0.0f, numOfCells);
            glPopMatrix();
            glPushMatrix();
            drawAxes(windowWidth, windowHeight);
            glPopMatrix();
            GLenum error = glGetError();
            if (error != GL_NO_ERROR) std::cerr << "Error: " << error << std::endl;
            SwapBuffers(hDC);
            theta += 1.0f;
            Sleep(1);
        }
    }
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
    DestroyWindow(hwnd);
    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY: return 0;

    case WM_KEYDOWN:
        drawChessBoard(wParam);
        break;

    case WM_MOUSEMOVE:
        moveCamera();
        break;

    case WM_SIZE:
        windowResize(LOWORD(lParam), HIWORD(lParam));
        break;

    default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void moveCamera() {
    Camera_MoveDirectional(
        GetKeyState('W') < 0 ? 1 : GetKeyState('S') < 0 ? -1
                                                        : 0,
        GetKeyState('D') < 0 ? 1 : GetKeyState('A') < 0 ? -1
                                                        : 0,
        0.1);
    Camera_AutoMoveByMouse(400, 400, 0.1);
}

void windowResize(int x, int y) {
    float aspectRatio = (float)x / (float)y;
    gluPerspective(45.0f, aspectRatio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void drawTriangle(float theta) {
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.87f, -0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.87f, -0.5f, 0.0f);
    glEnd();
}

void drawAxes(int windowWidth, int windowHeight) {
    float axisLength = 0.1f * std::min(windowWidth, windowHeight);
    float paddingX = windowWidth / 2.f;
    float paddingY = windowHeight / 2.f;
    float camXRot = camera.Xrot;
    float camZRot = camera.Zrot;
    float xAxisEndX = paddingX + axisLength * cos(camZRot * M_PI / 180.0f);
    float xAxisEndY = paddingY + axisLength * sin(camZRot * M_PI / 180.0f);
    float yAxisEndX = paddingX - axisLength * sin(camZRot * M_PI / 180.0f);
    float yAxisEndY = paddingY + axisLength * cos(camZRot * M_PI / 180.0f);
    float zAxisEndX = paddingX + axisLength * cos(camXRot * M_PI / 180.0f);
    float zAxisEndY = paddingY + axisLength * sin(camXRot * M_PI / 180.0f);
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(paddingX, paddingY);
    glVertex2f(xAxisEndX, xAxisEndY);
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(paddingX, paddingY);
    glVertex2f(yAxisEndX, yAxisEndY);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(paddingX, paddingY);
    glVertex2f(zAxisEndX, zAxisEndY);
    glEnd();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawChessBoard(float startX, float startY, int n) {
    float tileSize = 1.0f;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i + j) % 2 == 0) glColor3f(0.8f, 0.8f, 0.8f);
            else glColor3f(0.2f, 0.2f, 0.2f);
            float x = startX + j * tileSize;
            float y = startY + i * tileSize;
            glBegin(GL_QUADS);
            glVertex3f(x, 0.0f, y);
            glVertex3f(x + tileSize, 0.0f, y);
            glVertex3f(x + tileSize, 0.0f, y + tileSize);
            glVertex3f(x, 0.0f, y + tileSize);
            glEnd();
        }
    }
}

void drawFloor(float width, float length) {
    glColor3d(204 / 255.f, 102 / 255.f, 2 / 255.f);
    float minX = -width / 2.0f; 
    float minY = -length / 2.0f;
    float maxX = width / 2.0f;  
    float maxY = length / 2.0f;
    glBegin(GL_QUADS);
    glVertex3f(minX, minY, 0.0f);
    glVertex3f(maxX, minY, 0.0f);
    glVertex3f(maxX, maxY, 0.0f);
    glVertex3f(minX, maxY, 0.0f);
    glEnd();
}

void drawChessBoard(WPARAM wParam) {
    switch (wParam) {
    case VK_ESCAPE:
        PostQuitMessage(0);
        break;

    case VK_F1:
        numOfCells = 1;
        break;
    
    case VK_F2:
        numOfCells = 2;
        break;

    case VK_F3:
        numOfCells = 3;
        break;

    case VK_F4:
        numOfCells = 4;
        break;

    case VK_F5:
        numOfCells = 5;
        break;
    
    case VK_F6:
        numOfCells = 6;
        break;

    case VK_F7:
        numOfCells = 7;
        break;

    case VK_F8:
        numOfCells = 8;
        break;
    }
}