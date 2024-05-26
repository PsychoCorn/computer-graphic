#include <cmath>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "camera.h"
#include <vector>

// VARIANT 8

int numOfCells = 8;
GLfloat cubeSizeFactor = 1.f;
int numOfOnjectsInCircle = 10;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void windowResize(int, int);
void moveCamera();
void drawTriangle(float);
void drawFloor(float, float);
void drawFloorLikeChessBoard(float, float);
void drawAxes(int, int);
void drawChessBoard(float, float, int = 8);
void drawChessBoard(WPARAM);
void drawCube();
void drawBulb(GLfloat *, GLfloat , GLfloat);
void drawPrism(float);
void drawObjectsInCircle(float, int);
void drawProjector();

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

    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    GLfloat materialAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat materialDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat materialShininess[] = { 100.0f };
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, materialShininess);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
            drawFloorLikeChessBoard(200, 200);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(2.f, 2.f, 2.f);
            glScalef(-1.f, 1.f, 1.f); // Mirror horizontally
            drawObjectsInCircle(5.f, numOfOnjectsInCircle);
            glPopMatrix();
            /* glPushMatrix();
            glTranslatef(2.f, 2.f, 2.f);
            drawCube();
            glPopMatrix(); */
            glPushMatrix();
            drawAxes(windowWidth, windowHeight);
            glPopMatrix();
            glPushMatrix();
            drawProjector();
            glPopMatrix();

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

    case '0':
        numOfOnjectsInCircle = 10;
        break;
    case '1':
        numOfOnjectsInCircle = 1;
        break;
    case '2':
        numOfOnjectsInCircle = 2;
        break;
    case '3':
        numOfOnjectsInCircle = 3;
        break;
    case '4':
        numOfOnjectsInCircle = 4;
        break;
    case '5':
        numOfOnjectsInCircle = 5;
        break;
    case '6':
        numOfOnjectsInCircle = 6;
        break;
    case '7':
        numOfOnjectsInCircle = 7;
        break;
    case '8':
        numOfOnjectsInCircle = 8;
        break;
    case '9':
        numOfOnjectsInCircle = 9;
        break;
    }
}

void drawCube() {
    const GLfloat vertices[] = {
        -1.f * cubeSizeFactor, -1.f * cubeSizeFactor, 1.f * cubeSizeFactor, 
        1.f * cubeSizeFactor, -1.f * cubeSizeFactor, 1.f * cubeSizeFactor, 
        1.f * cubeSizeFactor, 1.f * cubeSizeFactor, 1.f * cubeSizeFactor, 
        -1.f * cubeSizeFactor, 1.f * cubeSizeFactor, 1.f * cubeSizeFactor, 
        -1.f * cubeSizeFactor, -1.f * cubeSizeFactor, -1.f * cubeSizeFactor, 
        1.f * cubeSizeFactor, -1.f * cubeSizeFactor, -1.f * cubeSizeFactor, 
        1.f * cubeSizeFactor, 1.f * cubeSizeFactor, -1.f * cubeSizeFactor, 
        -1.f * cubeSizeFactor, 1.f * cubeSizeFactor, -1.f * cubeSizeFactor, 
    };

    const GLuint indices[] = {
        0, 1, 2, 2, 3, 0, 1, 5, 6,
        6, 2, 1, 7, 6, 5, 5, 4, 7, 
        4, 0, 3, 3, 7, 4, 3, 2, 6,
        6, 7, 3, 4, 5, 1, 1, 0, 4 
    };
    const GLfloat normals[] = {
        0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f
    };
    glColor3f(.8f, .8f, .8f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, &normals);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_CULL_FACE);
}

void drawBulb(GLfloat *bulbColor, GLfloat bulbWidth, GLfloat bulbHeight) {
    GLfloat defaultColor[] = {1.0f, 1.0f, 0.0f};
    if (!bulbColor) bulbColor = defaultColor;
    GLfloat bulbPosition[] = {0.0f, 0.0f, 0.0f};
    GLfloat intensity = 2.f;
    GLfloat bulbColorWithIntensity[3];
    for (int i = 0; i < 3; ++i) {
        bulbColorWithIntensity[i] = bulbColor[i] * intensity;
    }
    GLfloat lightPosition[] = {bulbPosition[0], bulbPosition[1], bulbPosition[2], 1.0f};
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, bulbColorWithIntensity);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    GLfloat lightDirection[] = {0.0f, 0.0f, -1.0f};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDirection);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 128.0f);
    GLfloat lightCutoff = 15.0f;
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, lightCutoff);
    glColor3fv(bulbColorWithIntensity);
    glPushMatrix();
    glTranslatef(bulbPosition[0], bulbPosition[1], bulbPosition[2]);
    glBegin(GL_QUADS);
    glVertex3f(-bulbWidth / 2, -bulbHeight / 2, 0.0f);
    glVertex3f(bulbWidth / 2, -bulbHeight / 2, 0.0f);
    glVertex3f(bulbWidth / 2, bulbHeight / 2, 0.0f);
    glVertex3f(-bulbWidth / 2, bulbHeight / 2, 0.0f);
    glEnd();
    glPopMatrix();
}

void drawFloorLikeChessBoard(float width, float length) {
    float tileSize = 2;
    float minX = -width / 2.0f;
    float minY = -length / 2.0f;
    float maxX = width / 2.0f;
    float maxY = length / 2.0f;
    float normal_vert[] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1};
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, &normal_vert);
    glBegin(GL_QUADS);
    glColor3d(204 / 255.f, 204 / 255.f, 204 / 255.f);
    bool isBlack = true;
    for (float x = minX; x < maxX; x += tileSize) {
        isBlack = !isBlack;
        for (float y = minY; y < maxY; y += tileSize) {
            if (isBlack) glColor3f(0.2f, 0.2f, 0.2f);
            else glColor3f(0.8f, 0.8f, 0.8f);
            glVertex3f(x, y, 0.f);
            glVertex3f(x + tileSize, y, 0.f);
            glVertex3f(x + tileSize, y + tileSize, 0.f);
            glVertex3f(x, y + tileSize, 0.f);
            isBlack = !isBlack;
        }
    }
    glEnd();
    glDisable(GL_NORMAL_ARRAY);
}

void drawPrism(float alpha) {
    const int numVerticesPerSection = 11;
    const int numSections = 2;
    const GLfloat radius = 1.5f;
    const GLfloat height = 2.0f;
    std::vector<GLfloat> vertices(numVerticesPerSection * numSections * 3);
    std::vector<GLuint> indices;
    std::vector<GLfloat> normals(numVerticesPerSection * numSections * 3);
    for (int i = 0; i < numSections; i++) {
        GLfloat z = i * height / (numSections - 1);
        GLfloat currentRadius = (i == 1) ? radius * 0.5 : radius;
        for (int j = 0; j < numVerticesPerSection; j++) {
            GLfloat angle = j * 2 * M_PI / numVerticesPerSection;
            GLfloat x = currentRadius * cos(angle);
            GLfloat y = currentRadius * sin(angle);
            vertices[(i * numVerticesPerSection + j) * 3] = x;
            vertices[(i * numVerticesPerSection + j) * 3 + 1] = y;
            vertices[(i * numVerticesPerSection + j) * 3 + 2] = z;
        }
    }
    for (int i = 0; i < numSections - 1; i++) {
        for (int j = 0; j < numVerticesPerSection; j++) {
            GLuint idx1 = i * numVerticesPerSection + j;
            GLuint idx2 = (j < numVerticesPerSection - 1) ? idx1 + 1 : i * numVerticesPerSection;
            GLuint idx3 = (i + 1) * numVerticesPerSection + j;
            GLuint idx4 = (j < numVerticesPerSection - 1) ? idx3 + 1 : (i + 1) * numVerticesPerSection;
            indices.push_back(idx1);
            indices.push_back(idx2);
            indices.push_back(idx3);
            indices.push_back(idx2);
            indices.push_back(idx4);
            indices.push_back(idx3);
        }
    }
    int topCenterIndex = vertices.size() / 3;
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(height);
    for (int j = 0; j < numVerticesPerSection; j++) {
        indices.push_back(topCenterIndex);
        indices.push_back((numSections - 1) * numVerticesPerSection + j);
        indices.push_back((numSections - 1) * numVerticesPerSection + ((j + 1) % numVerticesPerSection));
    }
    int bottomCenterIndex = vertices.size() / 3;
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(0);
    for (int j = 0; j < numVerticesPerSection; j++) {
        indices.push_back(bottomCenterIndex);
        indices.push_back(j);
        indices.push_back((j + 1) % numVerticesPerSection);
    }
    for (int i = 0; i < numSections; i++) {
        for (int j = 0; j < numVerticesPerSection; j++) {
            GLfloat x = vertices[(i * numVerticesPerSection + j) * 3 + 0];
            GLfloat y = vertices[(i * numVerticesPerSection + j) * 3 + 1];
            GLfloat nx = x;
            GLfloat ny = y;
            GLfloat nz = 0.0f;
            normals[(i * numVerticesPerSection + j) * 3 + 0] = nx;
            normals[(i * numVerticesPerSection + j) * 3 + 1] = ny;
            normals[(i * numVerticesPerSection + j) * 3 + 2] = nz;
        }
    }
    normals.push_back(0);
    normals.push_back(0);
    normals.push_back(1);
    normals.push_back(0);
    normals.push_back(0);
    normals.push_back(-1);
    glColor4f(100 / 255.0f, 149 / 255.0f, 237 / 255.0f, alpha);
    glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < indices.size(); i += 3) {
        glVertex3f(
            vertices[indices[i] * 3], 
            vertices[indices[i] * 3 + 1], 
            vertices[indices[i] * 3 + 2]
        );
        glVertex3f(
            vertices[indices[i + 1] * 3], 
            vertices[indices[i + 1] * 3 + 1], 
            vertices[indices[i + 1] * 3 + 2]
        );
        glVertex3f(
            vertices[indices[i + 2] * 3], 
            vertices[indices[i + 2] * 3 + 1], 
            vertices[indices[i + 2] * 3 + 2]
        );
    }
    glEnd();
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glColor4f(0.0f, 1.0f, 0.0f, alpha);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (size_t i = 0; i < indices.size(); i += 3) {
        glVertex3f(
            vertices[indices[i] * 3], 
            vertices[indices[i] * 3 + 1], 
            vertices[indices[i] * 3 + 2]
        );
        glVertex3f(
            vertices[indices[i + 1] * 3], 
            vertices[indices[i + 1] * 3 + 1], 
            vertices[indices[i + 1] * 3 + 2]
        );
        glVertex3f(
            vertices[indices[i + 1] * 3], 
            vertices[indices[i + 1] * 3 + 1], 
            vertices[indices[i + 1] * 3 + 2]
        );
        glVertex3f(
            vertices[indices[i + 2] * 3], 
            vertices[indices[i + 2] * 3 + 1], 
            vertices[indices[i + 2] * 3 + 2]
        );
        glVertex3f(
            vertices[indices[i + 2] * 3], 
            vertices[indices[i + 2] * 3 + 1], 
            vertices[indices[i + 2] * 3 + 2]
        );
        glVertex3f(
            vertices[indices[i] * 3], 
            vertices[indices[i] * 3 + 1], 
            vertices[indices[i] * 3 + 2]
        );
    }
    glEnd();
    glDisable(GL_POLYGON_OFFSET_LINE);
}

void drawObjectsInCircle(float radius, int numObjects) {
    for (int i = 0; i < numObjects; ++i) {
        float alpha = (i + 1) * 1.f / numObjects;
        float angle = alpha * 2.f * M_PI;
        float prismX = radius * cos(angle);
        float prismY = radius * sin(angle);
        glPushMatrix();
        glTranslatef(prismX, prismY, 0.f);
        float prismRotationAngle = atan2(-prismY, -prismX) * 180.f / M_PI;
        glRotatef(prismRotationAngle, 0.f, 0.f, 1.f);
        drawPrism(alpha);
        glPopMatrix();
    }
}

void drawProjector() {
    GLfloat lightAmbient[] = {.5f, .5f, .5f, 1.f};
    GLfloat lightDiffuse[] = {.5f, .5f, .5f, 1.f};
    GLfloat lightSpecular[] = {.5f, .5f, .5f, 1.f};
    GLfloat lightPosition[] = {13.f, 10.f, 15.f, 1.f};
    GLfloat lightDirection[] = {0.f, 0.f, -1.f};
    GLfloat lightCutoff = 90.f;
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0f);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lightCutoff);
    glEnable(GL_LIGHT0);
}