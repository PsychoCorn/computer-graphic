#ifndef Listener_HPP
#define Listener_HPP

namespace kondraLib

{

    class Listener // interface for button listener
    {
    public:
        virtual void onClick() = 0; // action on click
        virtual ~Listener() = default;
    };

}

#endif