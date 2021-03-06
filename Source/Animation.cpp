#include "Animation.h"

#include <iostream>

void Animation::addFrames(int numFrames, const sf::IntRect& frameSize, float time)
{
    for (int i = 0 ; i <= numFrames ; i++)
    {
        addFrame({frameSize.left * i, frameSize.top, frameSize.width, frameSize.height}, time);
    }
}

void Animation::addFrame(const sf::IntRect& frame, float timeToNextFrame)
{
    if (timeToNextFrame > m_longestFrameTime)
        m_longestFrameTime = timeToNextFrame;

    m_frames.emplace_back(frame, timeToNextFrame);
}

const sf::IntRect Animation::getFrame()
{
    if (m_timer.getElapsedTime().asSeconds() >= m_frames[m_currentFrame].timeToNextFrame)
    {
        m_currentFrame++;
        if (m_currentFrame == m_frames.size() )
            reset();
        m_timer.restart().asSeconds();
    }

    return  m_frames[m_currentFrame].frame;
}

const sf::IntRect Animation::getFrame(int index)
{
    return m_frames[index].frame;
}


bool Animation::isOnFinalFrame() const
{
    return m_currentFrame == m_frames.size() - 1;
}


void Animation::reset()
{
    m_currentFrame = 0;
    m_timer.restart().asSeconds();
}
