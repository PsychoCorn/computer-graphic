#ifndef Interface_HPP
#define Interfsce_HPP

#include "../Drawable.hpp"
#include "../WinowSettings.hpp"
#include "buttons/Button.hpp"
#include "buttons/listeners/PauseButtonListener.hpp"
#include "buttons/listeners/ContinueButtonListener.hpp"
#include "buttons/listeners/ExitButtonListener.hpp"
#include <vector>

namespace kondraLib
{

    class Interface : public Drawable
    {
    public:
        enum class State
        {
            Gameplay,
            Pause,
            CloseConfirmation,
        };

    private:
        State _state;
        std::vector<std::shared_ptr<Drawable>> _widgets;
        std::vector<size_t> _indecesOfButtons;

        void addPauseButton();
        void addPauseMenu();
        void clearButtons();

    public:
        Interface();
        ~Interface() = default;
        void draw() const override;
        void changeState(const State &);
        void checkButtons(const GLfloat &, const GLfloat &);
        
    };

    Interface::Interface() : _state(Interface::State::Gameplay) 
    {
        addPauseButton();
    }

    void Interface::draw() const
    {
        for (auto widget : _widgets)
        {
            widget->draw();
        }
    }

    void Interface::addPauseButton()
    {
        auto pauseButton = std::make_shared<Button>(0.f, winHeight, 75.f, 32.f); 
        pauseButton->baseTo(Rectangle::BasePoints::NorthWest);
        pauseButton->setColor(0.5f);
        pauseButton->setLabelColor(1.f);
        pauseButton->setLabel("Pause");
        pauseButton->setListener(std::make_unique<PauseButtonListener>(this));
        _widgets.push_back(pauseButton);
        _indecesOfButtons.push_back(_widgets.size() - 1);
    }

    void Interface::addPauseMenu()
    {
        GLfloat buttonsWidth = 250.f, buttonsHeight = 75.f;
        // continue button
        auto continueButton = std::make_shared<Button>(winWidth / 2.f, winHeight / 2.f + 10, 
                                                       buttonsWidth, buttonsHeight); 
        continueButton->baseTo(Rectangle::BasePoints::SouthCenter);
        continueButton->setColor(0.5f);
        continueButton->setLabelColor(1.f);
        continueButton->setLabel("Continue");
        continueButton->setListener(std::make_unique<ContinueButtonListener>(this));
        _widgets.push_back(continueButton);
        _indecesOfButtons.push_back(_widgets.size() - 1);

        // exit button
        auto exitButton = std::make_shared<Button>(winWidth / 2.f, winHeight / 2.f - 10, 
                                                       buttonsWidth, buttonsHeight); 
        exitButton->baseTo(Rectangle::BasePoints::NorthCenter);
        exitButton->setColor(0.5f);
        exitButton->setLabelColor(1.f);
        exitButton->setLabel("Exit");
        exitButton->setListener(std::make_unique<ExitButtonListener>(this));
        _widgets.push_back(exitButton);
        _indecesOfButtons.push_back(_widgets.size() - 1);
    }

    void Interface::changeState(const Interface::State &state)
    {
        _state = state;
        clearButtons();
        switch (state)
        {
        case Interface::State::Gameplay:
            addPauseButton();
            break;

        case Interface::State::Pause:
            addPauseMenu();
            break;
        
        default:
            break;
        }
    }

    void Interface::checkButtons(const GLfloat &mouseX, const GLfloat &mouseY)
    {
        for (auto indexOfButton : _indecesOfButtons)
        {
            auto button = std::static_pointer_cast<Button>(_widgets[indexOfButton]);
            if (button->isMouseOver(mouseX, mouseY))
            {
                button->click();
                break;
            }
        }
    }

    void Interface::clearButtons()
    {
        for (auto indexOfButton : _indecesOfButtons)
        {
            _widgets[indexOfButton].reset();
        }
        _widgets.clear();
        _indecesOfButtons.clear();
    }

    void PauseButtonListener::onClick()
    {
        _interface->changeState(Interface::State::Pause);
    }

    void ContinueButtonListener::onClick()
    {
        _interface->changeState(Interface::State::Gameplay);
    }

    void ExitButtonListener::onClick()
    {
        glutDestroyWindow(glutGetWindow());
        exit(0);
    }

}

#endif