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
        enum class BasePoints
        {
            Center,
            NorthWest,
            NorthEast,
            SouthWest, // default
            SouthEast,
        };

        Rectangle(const GLfloat &, const GLfloat &, const GLfloat &, const GLfloat &, const Color & = Color::BLACK);
        ~Rectangle() = default;
        void draw() const override;
        void baseTo(const BasePoints &);
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

    void Rectangle::baseTo(const Rectangle::BasePoints &basePosition)
    {
        GLfloat offsetX, offsetY;

        switch (basePosition)
        {
        case BasePoints::Center:
            offsetX = -_width / 2.0f;
            offsetY = -_height / 2.0f;
            break;

        case BasePoints::NorthWest:
            offsetX = 0.0f;
            offsetY = -_height;
            break;

        case BasePoints::NorthEast:
            offsetX = -_width;
            offsetY = -_height;
            break;

        case BasePoints::SouthWest:
            offsetX = 0.0f;
            offsetY = 0.0f;
            break;

        case BasePoints::SouthEast:
            offsetX = -_width;
            offsetY = 0.0f;
            break;
        }

        auto x = _x + offsetX;
        auto y = _y + offsetY;

        // Update the vertices
        _vertices[0] = {x, y};
        _vertices[1] = {x + _width, y};
        _vertices[2] = {x + _width, y + _height};
        _vertices[3] = {x, y + _height};
    }

}

#endif