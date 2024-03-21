#ifndef Button_HPP
#define Button_HPP

#include "listeners/Listener.hpp"
#include "../../primitives/Rectangle.hpp"
#include <memory>
#include <string>
#include <cstring>

namespace kondraLib
{

    class Button final : public Rectangle
    {
    private:
        std::unique_ptr<Listener> _listener = nullptr;

        struct Label
        {
            std::string text = "";
            int x;
            int y;
            int width;
            int height;
            size_t length;
            RECT rect;
            struct Color
            {
                int r;
                int g;
                int b;
            } color;
        } _label;
        

    public:
        Button(const GLdouble &, const GLdouble &, const GLdouble &, const GLdouble &);
        ~Button() = default;
        void click();
        bool isMouseOver(const GLdouble &, const GLdouble &) const;
        void setListener(std::unique_ptr<Listener>);
        void setLabel(const std::string &);
        void setColor(const Color &);
        void setColor(const GLdouble &, const GLdouble &, const GLdouble &, const GLdouble & = 1.f);
        void setLabelColor(const int &, const int &, const int &);
        void draw() const override;
        void baseTo(const BasePoints &);
    };

    Button::Button(const GLdouble &x, const GLdouble &y, const GLdouble &width, const GLdouble &height) : 
        Rectangle(x, y, width, height) {}

    void Button::click()
    {
        _listener->onClick();
    }

    bool Button::isMouseOver(const GLdouble &mouseX, const GLdouble &mouseY) const
    {
        return mouseX >= _vertices[0].first && mouseX <= _vertices[2].first && 
               mouseY >= _vertices[0].second && mouseY <= _vertices[2].second;
    }

    void Button::setListener(std::unique_ptr<Listener> listener)
    {
        _listener = std::move(listener);
    }

    void Button::setLabel(const std::string &text)
    {
        _label.text = text;
        _label.length = text.length();
        _label.width = _label.length * 8;
        _label.height = 13.f;
        _label.x = _vertices[0].first + (_width - _label.width) / 2;
        _label.y = _vertices[0].second + (_height - _label.height) / 2; // 3 - magic number, result of the selection
        _label.rect.left = _label.x;
        _label.rect.top = _label.y;
        _label.rect.right = _label.x + _label.width;
        _label.rect.bottom = _label.y + _label.height;
    }

    void Button::setColor(const Color &color)
    {
        _color = color;
    }

    void Button::setColor(const GLdouble &r, const GLdouble &g, const GLdouble &b, const GLdouble &a)
    {
        _color.setColor(r, g, b, a);
    }

    void Button::setLabelColor(const int &r, const int &g, const int &b)
    {
        _label.color.r = r;
        _label.color.g = g;
        _label.color.b = b;
    }

    void Button::draw() const
    {
        Rectangle::draw(); // Отрисовка самой кнопки

        HDC hdc = GetDC(hwnd);
        RECT rect = _label.rect;

        SetTextColor(hdc, RGB(_label.color.r, _label.color.g, _label.color.b));

        DrawText(hdc, _label.text.c_str(), _label.length, &rect, DT_LEFT | DT_TOP | DT_SINGLELINE);

        ReleaseDC(hwnd, hdc);
    }

    void Button::baseTo(const Rectangle::BasePoints &basePosition)
    {
        Rectangle::baseTo(basePosition);
        _label.x = _vertices[0].first + (_width - _label.width) / 2;
        _label.y = _vertices[0].second + (_height + _label.height) / 3;
    }

}

#endif