#ifndef Drawable_HPP
#define Drawable_HPP

namespace kondraLib
{

    class Drawable // interface
    {
    public:
        virtual ~Drawable() = default;
        virtual void draw() const = 0;
    };

}

#endif