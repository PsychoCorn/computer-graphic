#ifndef Button_HPP
#define Button_HPP

#include "listeners/Listener.hpp"
#include "../../primitives/Rectangle.hpp"
#include <memory>
#include <string>

namespace kondraLib
{

    class Button final : public Rectangle
    {
    private:
        std::string _label = "";
        GLfloat _labelWidth;
        GLfloat _labelHeight;
        GLfloat _labelX;
        GLfloat _labelY;
        Color _labelColor = Color::BLACK;
        std::unique_ptr<Listener> _listener = nullptr;

    public:
        Button(const GLfloat &, const GLfloat &, const GLfloat &, const GLfloat &);
        ~Button() = default;
        void click();
        bool isMouseOver(const GLfloat &, const GLfloat &) const;
        void setListener(std::unique_ptr<Listener>);
        void setLabel(const std::string &);
        void setColor(const Color &);
        void setColor(const GLfloat &, const GLfloat &, const GLfloat &, const GLfloat & = 1.f);
        void setLabelColor(const Color &);
        void setLabelColor(const GLfloat &, const GLfloat &, const GLfloat &, const GLfloat & = 1.f);
        void draw() const override;
    };

    Button::Button(const GLfloat &x, const GLfloat &y, const GLfloat &width, const GLfloat &height) : 
        Rectangle(x, y, width, height) {}

    void Button::click()
    {
        _listener->onClick();
    }

    bool Button::isMouseOver(const GLfloat &mouseX, const GLfloat &mouseY) const
    {
        return mouseX >= _vertices[0].first && mouseX <= _vertices[2].first && 
               mouseY >= _vertices[0].second && mouseY <= _vertices[2].second;
    }

    void Button::setListener(std::unique_ptr<Listener> listener)
    {
        _listener = std::move(listener);
    }

    void Button::setLabel(const std::string &label)
    {
        _label = label;
        _labelWidth = _label.length() * 8;
        _labelHeight = 13.f;
        _labelX = _vertices[0].first + (_width - _labelWidth) / 2;
        _labelY = _vertices[0].second + (_height + _labelHeight) / 3; // 3 - magic number, result of the selection
    }

    void Button::setColor(const Color &color)
    {
        _color = color;
    }

    void Button::setColor(const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a)
    {
        _color.setColor(r, g, b, a);
    }

    void Button::setLabelColor(const Color &color)
    {
        _labelColor = color;
    }

    void Button::setLabelColor(const GLfloat &r, const GLfloat &g, const GLfloat &b, const GLfloat &a)
    {
        _labelColor.setColor(r, g, b, a);
    }

    void Button::draw() const
    {
        Rectangle::draw();
        glColor4f(_labelColor.getColor().red, _labelColor.getColor().green, _labelColor.getColor().blue, _labelColor.getColor().alpha);
        glRasterPos2f(_labelX, _labelY);
        for (char c : _label)
        {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c); // Render each character of the label
        }
    }

}

#endif