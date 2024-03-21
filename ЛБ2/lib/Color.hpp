#ifndef Color_HPP
#define Color_HPP

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <Windows.h>
#include <gl/gl.h>
#include "../stb-master/stb_image.h"
#include "../stb-master/stb_easy_font.h"
#include "../stb-master/stb_textedit.h"
#include "../stb-master/stb_truetype.h"
#include "../stb-master/stb_rect_pack.h"


namespace kondraLib
{

    class Color final
    {
    private:
        struct Rgba 
        {
            GLdouble red;
            GLdouble green;
            GLdouble blue;
            GLdouble alpha;

            Rgba(const GLdouble &, const GLdouble &, const GLdouble &, const GLdouble & = 1.f);
        } _color;
        
    public:
        Color(const GLdouble &, const GLdouble &, const GLdouble &, const GLdouble & = 1.f);
        Color(const GLdouble &, const GLdouble & = 1.f);
        Color(const Rgba &);
        ~Color() = default;
        Rgba getColor() const;
        void setColor(const GLdouble &, const GLdouble &, const GLdouble &, const GLdouble & = 1.f);
        void setColor(const Rgba &);

        static const Color BLACK;
        static const Color WHITE;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
    };

    Color::Rgba::Rgba(const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &a) :
        red(r), green(g), blue(b), alpha(a) {}

    Color::Color(const GLdouble &red, const GLdouble &green, const GLdouble &blue, const GLdouble &alpha) : 
        _color(red, green, blue, alpha) {}

    Color::Color(const GLdouble &color, const GLdouble &alpha) : 
        _color(color, color, color, alpha) {}

    Color::Color(const Color::Rgba &color) : _color(color) {}

    Color::Rgba Color::getColor() const
    {
        return _color;
    }

    void Color::setColor(const GLdouble &red, const GLdouble &green, const GLdouble &blue, const GLdouble &alpha)
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