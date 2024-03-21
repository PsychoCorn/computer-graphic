#ifndef PauseButtonListener_HPP
#define PauseButtonListener_HPP

#include "Listener.hpp"

namespace kondraLib
{

    class Interface;

    class PauseButtonListener final : public Listener
    {
    private:
        Interface *_interface;

    public:
        PauseButtonListener(Interface *);
        ~PauseButtonListener() = default;
        void onClick() override;
    };

    PauseButtonListener::PauseButtonListener(Interface *itnrfc) : _interface(itnrfc) {}

}

#endif