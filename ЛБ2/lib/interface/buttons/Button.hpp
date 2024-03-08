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
        return mouseX >= _x && mouseX <= _x + _width && mouseY >= _y && mouseY <= _y + _height;
    }

    void Button::setListener(std::unique_ptr<Listener> listener)
    {
        _listener = std::move(listener);
    }

    void Button::setLabel(const std::string &label)
    {
        _label = label;
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

        // Draw label text
        // Set color to white
        glColor4f(_labelColor.getColor().red, _labelColor.getColor().green, _labelColor.getColor().blue, 
                _labelColor.getColor().alpha); 
        glRasterPos2f(_x + (_width - _label.length() * 8) / 2, _y + _height / 2); // Calculate position for centering text
        for (char c : _label)
        {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c); // Render each character of the label
        }
    }

}

#endif