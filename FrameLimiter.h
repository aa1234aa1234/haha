//
// Created by D412 on 2025-07-09.
//

#ifndef FRAMELIMITER_H
#include <chrono>
class FrameLimiter
{
    float FRAME_LIMIT;

public:
    FrameLimiter(float framelimit) : FRAME_LIMIT(framelimit) {}
    ~FrameLimiter() {}

    void start()
    {

    }

    void end()
    {

    }
};

#define FRAMELIMITER_H

#endif //FRAMELIMITER_H
