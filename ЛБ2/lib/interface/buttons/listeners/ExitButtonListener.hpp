#ifndef ExitButtonListener_HPP
#define ExitButtonListener_HPP

#include "Listener.hpp"

namespace kondraLib
{

    class Interface;

    class ExitButtonListener final : public Listener
    {
    private:
        Interface *_interface;

    public:
        ExitButtonListener(Interface *);
        ~ExitButtonListener() = default;
        void onClick() override;
    };

    ExitButtonListener::ExitButtonListener(Interface *interface) : _interface(interface) {}

}

#endif