#ifndef Rectangle_HPP
#define Rectangle_HPP

#include "../Drawable.hpp"
#include "../Color.hpp"
#include <array>

namespace kondraLib
{

    class Rectangle :public Drawable
    {
    protected:
        GLfloat _x;
        GLfloat _y;
        GLfloat _height;
        GLfloat _width;
        Color _color;
        std::array<std::pair<GLfloat, GLfloat>, 4> _vertices;

    public:
        Rectangle(const GLfloat &, const GLfloat &, const GLfloat &, const GLfloat &, const Color & = Color::BLACK);
        ~Rectangle() = default;
        void draw() const override;
    };

    Rectangle::Rectangle(const GLfloat &x, const GLfloat &y, const GLfloat &width,
                        const GLfloat &height, const Color &color) : _x(x), _y(y), _height(height), 
                                                                    _width(width), _color(color) 
    {
        _vertices[0] = {_x, _y};
        _vertices[1] = {_x + _width, _y};
        _vertices[2] = {_x + _width, _y + _height};
        _vertices[3] = {_x, _y + _height};
    }

    void Rectangle::draw() const
    {
        glColor4f(_color.getColor().red, _color.getColor().green, _color.getColor().blue, _color.getColor().alpha);
        glBegin(GL_QUADS);
        for (auto&& [x, y] : _vertices)
        {
            glVertex2f(x, y);
        }
        glEnd();
    }

}

#endif