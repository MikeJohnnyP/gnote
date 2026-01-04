#pragma once

#include "pch.h"

namespace Gnote
{
struct GNOTE_API TimeSteps
{
    TimeSteps(float time = 0) : m_Time(time)
    {
    }

    operator float()
    {
        return m_Time;
    }

    float GetTime()
    {
        return m_Time;
    }
    float GetTimeMiliSeconds()
    {
        return m_Time * 1000.0f;
    }

    float m_Time;
};
} // namespace Gnote
