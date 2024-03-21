#ifndef Rectangle_HPP
#define Rectangle_HPP

#include "../Drawable.hpp"
#include "../Color.hpp"
#include <array>

namespace kondraLib
{

    class Rectangle : public Drawable
    {
    protected:
        GLdouble _x;
        GLdouble _y;
        GLdouble _height;
        GLdouble _width;
        Color _color;
        std::array<std::pair<GLdouble, GLdouble>, 4> _vertices;
        void calculateVertices(const GLdouble &, const GLdouble &);

    public:
        enum class BasePoints
        {
            Center,
            NorthCenter,
            SouthCenter,
            WestCenter,
            EastCenter,
            NorthWest,
            NorthEast,
            SouthWest, // default
            SouthEast,
        };

        Rectangle(const GLdouble &, const GLdouble &, const GLdouble &, const GLdouble &, const Color & = Color::BLACK);
        ~Rectangle() = default;
        void draw() const override;
        void baseTo(const BasePoints &);
    };

    Rectangle::Rectangle(const GLdouble &x, const GLdouble &y, const GLdouble &width,
                        const GLdouble &height, const Color &color) : _x(x), _y(y), _height(height), 
                                                                    _width(width), _color(color) 
    {
        calculateVertices(x, y);
    }

    void Rectangle::draw() const
    {
        glColor4d(_color.getColor().red, _color.getColor().green, _color.getColor().blue, _color.getColor().alpha);
        glBegin(GL_QUADS);
        for (auto&& [x, y] : _vertices)
        {
            glVertex2d(x, y);
        }
        glEnd();
    }

    void Rectangle::baseTo(const Rectangle::BasePoints &basePosition)
    {
        GLdouble offsetX, offsetY;

        switch (basePosition)
        {
        case BasePoints::Center:
            offsetX = -_width / 2.f;
            offsetY = -_height / 2.f;
            break;

        case BasePoints::NorthWest:
            offsetX = 0.f;
            offsetY = -_height;
            break;

        case BasePoints::NorthEast:
            offsetX = -_width;
            offsetY = -_height;
            break;

        case BasePoints::SouthWest:
            offsetX = 0.f;
            offsetY = 0.f;
            break;

        case BasePoints::SouthEast:
            offsetX = -_width;
            offsetY = 0.f;
            break;

        case BasePoints::NorthCenter:
            offsetX = -_width / 2.f;
            offsetY = -_height;
            break;

        case BasePoints::SouthCenter:
            offsetX = -_width / 2.f;
            offsetY = 0.f;
            break;

        case BasePoints::WestCenter:
            offsetX = 0.f;
            offsetY = -_height / 2.f;
            break;

        case BasePoints::EastCenter:
            offsetX = -_width;
            offsetY = -_height / 2.f;
            break;
        }

        auto x = _x + offsetX;
        auto y = _y + offsetY;

        // Update the vertices
        calculateVertices(x, y);
    }

    void Rectangle::calculateVertices(const GLdouble &x, const GLdouble &y)
    {
        _vertices[0] = {x, y};
        _vertices[1] = {x + _width, y};
        _vertices[2] = {x + _width, y + _height};
        _vertices[3] = {x, y + _height};
    }

}

#endif