#ifndef INPUT_H
#define INPUT_H

#pragma once

#include "iostream"

class Input
{
public:
    Input();
    ~Input();

    static float getAxisRaw(std::string axe);
    static bool getInputAction(std::string action);

private:
};

#endif