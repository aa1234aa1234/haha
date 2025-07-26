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

    void efficientFixedCountdown(const std::chrono::nanoseconds& countdownDuration, const std::chrono::nanoseconds& tickInterval) {
        // Local variables used to control fixed updating of countdown timer
        std::chrono::time_point<std::chrono::high_resolution_clock> bootTime = std::chrono::high_resolution_clock::now();
        std::chrono::nanoseconds fixedTime = std::chrono::nanoseconds(0);
        std::chrono::nanoseconds deltaTime = std::chrono::nanoseconds(0);

        // While there is more time left to coundown, countdown
        while (countdownDuration > fixedTime) {
            // If it is time to countdown according to tickrate, countdown
            if (fixedTime + deltaTime < std::chrono::high_resolution_clock::now() - bootTime) {
                // Convert nanoseconds to hours, minutes, seconds, and milliseconds
                std::chrono::nanoseconds timeLeft = countdownDuration - fixedTime;
                std::chrono::hours hours = std::chrono::duration_cast<std::chrono::hours>(timeLeft);
                std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(timeLeft % std::chrono::hours(1));
                std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(timeLeft % std::chrono::minutes(1));
                std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timeLeft % std::chrono::seconds(1));

                // Print leftover time
                //std::cout << hours.count() << " hours, " << minutes.count() << " minutes, " << seconds.count() << " seconds, " << milliseconds.count() << " milliseconds\n";

                // Conserve resources and iterations
                std::this_thread::sleep_until(std::chrono::high_resolution_clock::now() + tickInterval);

                // Update fixed time
                fixedTime += tickInterval;
            }
        }
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
            efficientFixedCountdown(std::chrono::milliseconds((int)((1.0/FRAME_LIMIT-time)*1000.0)), std::chrono::milliseconds(1));
            //std::this_thread::sleep_for(std::chrono::duration<double, std::chrono::milliseconds>((1.0/FRAME_LIMIT-time)*1000.0));
        }
        return fps;
    }

    float getFPS() { return fps; }
};

#define FRAMELIMITER_H

#endif //FRAMELIMITER_H
