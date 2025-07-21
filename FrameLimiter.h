//
// Created by D412 on 2025-07-09.
//

#ifndef FRAMELIMITER_H
#include <chrono>
#include <thread>

class FrameLimiter
{
    float FRAME_LIMIT, startframe, fps;

public:
    FrameLimiter(float framelimit) : FRAME_LIMIT(framelimit) {}
    ~FrameLimiter() {}

    void begin()
    {
        startframe = glfwGetTime();
    }

    void getAverageFps()
    {
        double currenttime = glfwGetTime();

        static double lastFpsUpdateTime = glfwGetTime();
        static int frameCount = 0;
        static float frametimes[10];
        static double frametime;
        frametime = currenttime - lastFpsUpdateTime;
        frametimes[frameCount % 10] = frametime;
        lastFpsUpdateTime = currenttime;
        int cnt;
        frameCount++;
        cnt = frameCount < 10 ? frameCount : 10;
        float averageframe = 0;
        for (int i = 0; i < cnt; i++)
        {
            averageframe += frametimes[i];
        }
        averageframe /= static_cast<float>(cnt);
        fps = averageframe > 0 ? 1.0/averageframe : FRAME_LIMIT;
    }

    int end()
    {
        getAverageFps();
        float time = glfwGetTime() - startframe;
        //std::cout << time << ' ' << 1.0/FRAME_LIMIT << std::endl;
        if (time < 1.0/FRAME_LIMIT)
        {
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>((1.0/FRAME_LIMIT-time)*1000.0));
        }
        return fps;
    }

    float getFPS() { return fps; }
};

#define FRAMELIMITER_H

#endif //FRAMELIMITER_H
