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
        std::vector<std::shared_ptr<Button>> _buttons;

        void addPauseButton();
        void addPauseMenu();
        void clearButtons();

    public:
        Interface();
        ~Interface() = default;
        void draw() const override;
        void changeState(const State &);
        void checkButtons(const GLdouble &, const GLdouble &);
        
    };

    Interface::Interface() : _state(Interface::State::Gameplay) 
    {
        addPauseButton();
    }

    void Interface::draw() const
    {
        for (auto button : _buttons)
        {
            button->draw();
        }
    }

    void Interface::addPauseButton()
    {
        auto pauseButton = std::make_shared<Button>(0.f, winHeight, 75.f, 32.f); 
        pauseButton->baseTo(Rectangle::BasePoints::NorthWest);
        pauseButton->setColor(0.5f);
        pauseButton->setLabelColor(255, 255, 255);
        pauseButton->setLabel("Pause");
        pauseButton->setListener(std::make_unique<PauseButtonListener>(this));
        _buttons.push_back(pauseButton);
    }

    void Interface::addPauseMenu()
    {
        GLdouble buttonsWidth = 250.f, buttonsHeight = 75.f;
        // continue button
        auto continueButton = std::make_shared<Button>(winWidth / 2.f, winHeight / 2.f + 10, 
                                                       buttonsWidth, buttonsHeight); 
        continueButton->baseTo(Rectangle::BasePoints::SouthCenter);
        continueButton->setColor(0.5f);
        continueButton->setLabelColor(255, 255, 255);
        continueButton->setLabel("Continue");
        continueButton->setListener(std::make_unique<ContinueButtonListener>(this));
        _buttons.push_back(continueButton);

        // exit button
        auto exitButton = std::make_shared<Button>(winWidth / 2.f, winHeight / 2.f - 10, 
                                                       buttonsWidth, buttonsHeight); 
        exitButton->baseTo(Rectangle::BasePoints::NorthCenter);
        exitButton->setColor(0.5f);
        exitButton->setLabelColor(255, 255, 255);
        exitButton->setLabel("Exit");
        exitButton->setListener(std::make_unique<ExitButtonListener>(this));
        _buttons.push_back(exitButton);
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

    void Interface::checkButtons(const GLdouble &mouseX, const GLdouble &mouseY)
    {
        for (auto button : _buttons)
        {
            if (button->isMouseOver(mouseX, mouseY))
            {
                button->click();
                break;
            }
        }
    }

    void Interface::clearButtons()
    {
        for (auto button : _buttons)
        {
            button.reset();
        }
        _buttons.clear();
        _buttons.clear();
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
        throw *this;
    }


}

#endif