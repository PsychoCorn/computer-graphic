#include "lib/interface/Interface.hpp"
#include <iostream>

kondraLib::Interface interface;

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    interface.draw();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        interface.checkButtons(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow(winTitle);

    glClearColor(0.f, 0.f, 0.f, 0.f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, winWidth, 0, winHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}