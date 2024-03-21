#ifndef ContinueButtonListener_HPP
#define ContinueButtonListener_HPP

#include "Listener.hpp"

namespace kondraLib
{

    class Interface;

    class ContinueButtonListener final : public Listener
    {
    private:
        Interface *_interface;

    public:
        ContinueButtonListener(Interface *);
        ~ContinueButtonListener() = default;
        void onClick() override;
    };

    ContinueButtonListener::ContinueButtonListener(Interface *itnrfc) : _interface(itnrfc) {}

}

#endif