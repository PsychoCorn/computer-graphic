#ifndef Rectangle_HPP
#define Rectangle_HPP

#include "../Drawable.hpp"
#include "../Color.hpp"

namespace kondraLib
{

    class Rectangle : Drawable
    {
    protected:
        GLfloat _x;
        GLfloat _y;
        GLfloat _height;
        GLfloat _width;
        Color _color;

    public:
        Rectangle(const GLfloat &, const GLfloat &, const GLfloat &, const GLfloat &, const Color & = Color::BLACK);
        ~Rectangle() = default;
        void draw() override;
    };

    Rectangle::Rectangle(const GLfloat &x, const GLfloat &y, const GLfloat &width,
                        const GLfloat &height, const Color &color) : _x(x), _y(y), _height(height), 
                                                                    _width(width), _color(color) {}

    void Rectangle::draw()
    {
        glColor4f(_color.getColor().red, _color.getColor().green, _color.getColor().blue, _color.getColor().alpha);
        glBegin(GL_QUADS);
        glVertex2f(_x, _y);
        glVertex2f(_x + _width, _y);
        glVertex2f(_x + _width, _y + _height);
        glVertex2f(_x, _y + _height);
        glEnd();
    }

}

#endif