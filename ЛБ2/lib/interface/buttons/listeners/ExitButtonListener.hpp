#ifndef ExitButtonListener_HPP
#define ExitButtonListener_HPP

#include "Listener.hpp"
#include <stdexcept>

namespace kondraLib
{

    class Interface;

    class ExitButtonListener final : public Listener, public std::runtime_error
    {
    private:
        Interface *_interface;

    public:
        ExitButtonListener(Interface *);
        ~ExitButtonListener() = default;
        void onClick() override;
    };

    ExitButtonListener::ExitButtonListener(Interface *itnrfc) : _interface(itnrfc), std::runtime_error("") {}

}

#endif