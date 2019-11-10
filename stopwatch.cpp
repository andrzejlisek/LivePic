#include "stopwatch.h"

namespace EdenClass
{
    StopWatch::StopWatch()
    {
        Reset();
    }

    void StopWatch::Reset()
    {
        IsRunning = false;
        Time1 = StopWatchGetTimeNow;
        Time2 = Time1;
    }

    void StopWatch::Start()
    {
        IsRunning = 1;
        long T = Time2 - Time1;
        Time1 = StopWatchGetTimeNow;
        Time2 = Time1 + T;
        Time2 = Time1;
    }

    void StopWatch::Stop()
    {
        IsRunning = false;
        Time2 = StopWatchGetTimeNow;
    }

    long long StopWatch::GetTime()
    {
        if (IsRunning)
        {
            Time2 = StopWatchGetTimeNow;
        }
        return Time2 - Time1;
    }

    std::string StopWatch::GetTimeT()
    {
        long long T = GetTime();
        std::string XX;
        std::string X;

        X = std::to_string(T % 1000);
        while (X.length() < 3) { X = "0" + X; }
        XX = "." + X;
        T = T / 1000LL;

        X = std::to_string(T % 60);
        while (X.length() < 2) { X = "0" + X; }
        XX = ":" + X + XX;
        T = T / 60LL;

        X = std::to_string(T % 60);
        while (X.length() < 2) { X = "0" + X; }
        XX = ":" + X + XX;
        T = T / 60LL;

        X = std::to_string(T);
        while (X.length() < 2) { X = "0" + X; }
        XX = X + XX;

        return XX;
    }

    void StopWatch::Delay(long long Duration, bool ActiveWork)
    {
        if (ActiveWork)
        {
            long long T = StopWatchGetTimeNow;
            T += Duration;
            while (StopWatchGetTimeNow < T)
            {
            }
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(Duration));
        }
    }
}
