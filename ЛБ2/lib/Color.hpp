#ifndef Color_HPP
#define Color_HPP

#include "../GL/freeglut.h"

namespace kondraLib
{

    class Color final
    {
    private:
        struct Rgba 
        {
            GLfloat red;
            GLfloat green;
            GLfloat blue;
            GLfloat alpha;

            Rgba(const GLfloat &, const GLfloat &, const GLfloat &, const GLfloat & = 1.f);
        } _color;
        
    public:
        Color(const GLfloat &, const GLfloat &, const GLfloat &, const GLfloat & = 1.f);
        Color(const GLfloat &, const GLfloat & = 1.f);
        Color(const Rgba &);
        ~Color() = default;
        Rgba getColor() const;
        void setColor(const GLfloat &, const GLfloat &, const GLfloat &, const GLfloat & = 1.f);
        void setColor(const Rgba &);

        static const Color BLACK;
        static const Color WHITE;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
    };

    Color::Rgba::Rgba(const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a) :
        red(r), green(g), blue(b), alpha(a) {}

    Color::Color(const GLfloat &red, const GLfloat &green, const GLfloat &blue, const GLfloat &alpha) : 
        _color(red, green, blue, alpha) {}

    Color::Color(const GLfloat &color, const GLfloat &alpha) : 
        _color(color, color, color, alpha) {}

    Color::Color(const Color::Rgba &color) : _color(color) {}

    Color::Rgba Color::getColor() const
    {
        return _color;
    }

    void Color::setColor(const GLfloat &red, const GLfloat &green, const GLfloat &blue, const GLfloat &alpha)
    {
        _color.red = red;
        _color.green = green;
        _color.blue = blue;
        _color.alpha = alpha;
    }

    void Color::setColor(const Color::Rgba &color)
    {
        _color.red = color.red;
        _color.green = color.green;
        _color.blue = color.blue;
        _color.alpha = color.alpha;
    }

    const Color Color::BLACK = Color(0.f);
    const Color Color::WHITE = Color(1.f);
    const Color Color::RED = Color(1.f, 0.f, 0.f);
    const Color Color::GREEN = Color(0.f, 1.f, 0.f);
    const Color Color::BLUE = Color(0.f, 0.f, 1.f);

}

#endif