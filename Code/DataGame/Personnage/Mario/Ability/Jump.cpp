#include "Jump.h"

Jump::Jump()
{
}

Jump::~Jump()
{
}

// Public Functions

void Jump::initJumpSpeed()
{
    this->jumpSpeed = jumpSpeedInitial;
}

void Jump::setJumpSpeed(float jumpSpeed)
{
    this->jumpSpeed = jumpSpeed;
}

void Jump::upJumpSpeed(float upJumpSpeed)
{
    this->jumpSpeed += upJumpSpeed;
}

void Jump::updateJumpSpeed()
{
    jumpSpeed -= jumpForce;

    if (jumpSpeed < 0)
    {
        jumpSpeed = 0;
    }
}