#include "lib/interface/buttons/Button.hpp"
#include <iostream>

const GLuint winWidth = 400;
const GLuint winHeight = 400;

class TestListener : public kondraLib::Listener
{
private:
    kondraLib::Button *_button;
    bool _isBlue = false;
public:
    TestListener(kondraLib::Button *button) : _button(button) {}
    ~TestListener() = default;
    void onClick() override
    {
        _button->setColor(_isBlue ? kondraLib::Color::RED : kondraLib::Color::BLUE);
        _isBlue = !_isBlue;
        std::cout << "Button was clicked!" << std::endl;
    }
};

kondraLib::Button testButton = kondraLib::Button(100, 100, 200, 50);

void display() 
{
    glClear(GL_COLOR_BUFFER_BIT);

    testButton.draw();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        if (testButton.isMouseOver(x, glutGet(GLUT_WINDOW_HEIGHT) - y)) 
        {
            testButton.click();
        }
    }
}

int main(int argc, char** argv)
{
    testButton.setColor(kondraLib::Color::RED);
    testButton.setLabelColor(kondraLib::Color::WHITE);
    testButton.setLabel("Click me!");
    testButton.setListener(std::make_unique<TestListener>(&testButton));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Button Example");

    glClearColor(0.0, 0.0, 0.0, 0.0);

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