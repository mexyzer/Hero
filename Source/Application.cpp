#include "Application.h"

#include <iostream>

#include "Display.h"
#include "Util/Random.h"

#include "States/Playing_State.h"
#include "States/Splash_Screen.h"

#include "Game/Equipment/Equipment_Data.h"

namespace
{
    void calculateFPS()
    {
        static sf::Clock timer;
        static sf::Clock printTimer;
        static auto numFrames = 0;

        numFrames++;

        if (printTimer.getElapsedTime().asSeconds() >= 1.0f)
        {
            auto fps = (float)numFrames / timer.getElapsedTime().asSeconds();
            printTimer.restart();
            std::cout << fps << std::endl;

            numFrames = 0;
            timer.restart();
        }
    }
}

Application::Application()
{
    Display ::init      ("Hero - V0.1");
    Random  ::init      ();

    m_music.setLoop(true);
    m_music.openFromFile("Res/Music/cs8b.ogg");
    m_music.setVolume(10);
    m_music.play();

    //pushState(std::make_unique<State::Splash_Screen>(*this));
    pushState(std::make_unique<State::Playing>(*this));
}

void Application::runMainLoop()
{
    sf::Clock c;
    while (Display::isOpen())
    {
        auto dt = c.restart().asSeconds();

        Display::clear({50, 50, 100});

        m_states.top()->input   ();
        m_states.top()->update  (dt);
        m_states.top()->draw    ();

        Display::update         ();
        calculateFPS            ();

        Display::pollEvents(*m_states.top());
    }
}

void Application::pushState(std::unique_ptr<State::State_Base> state)
{
    m_states.push(std::move(state));
}

void Application::popState()
{
    m_states.pop();
}
