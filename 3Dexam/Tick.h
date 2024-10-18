#pragma once

class Tick {
public:
    virtual ~Tick() {}

    // Pure virtual function - this forces derived classes to implement UpdateTick
    virtual void UpdateTick(float deltaTime) = 0;
};