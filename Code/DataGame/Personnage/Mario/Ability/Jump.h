#ifndef JUMP_H
#define JUMP_H

#pragma once

class Jump
{
public:
    Jump();
    ~Jump();

    float jumpSpeedInitial = 1;
    float jumpSpeed = 0;
    float jumpForce = 0.01;

    void initJumpSpeed();
    void setJumpSpeed(float jumpSpeed);
    void upJumpSpeed(float upJumpSpeed);
    void updateJumpSpeed();

private:
};

#endif