#ifndef MARIO_H
#define MARIO_H
#pragma once

#include "../../Actor/Actor.h"
#include "../../Collision/Collision.h"
#include "./Ability/Jump.h"

enum State
{
	IDLE,
	JUMP,
	FALLING,
	DUNK,
	MOVE,
};

enum Transformation
{
	SmallMario,
	SuperMario,
	FireMario,
};

class Mario
{
public:
	Mario();
	~Mario();

	void update(float deltaTime);
	void performMovement(float deltaTime);
	void draw(sf::RenderWindow &window) const;

	sf::Sprite &getSprite();
	sf::Vector2f &getVelocity();
	sf::Sprite *getFootHitbox();

	void gravity(float deltaTime);
	void setCanJump(bool jump);
	void setIdle();
	void setStateIdle();
	void setStateMoving();
	void setStateJump();
	void setStateDunk();
	void setMarioVictoryStyle();
	void setJumpSpeed(float jumpSpeed);

	void setPositionHitbox();

	void powerDown();
	void powerUp();
	void makeDead();

	void deathing(float deltaTime);
	void invulnerable(float deltaTime);

	void transforming(float deltaTime);

	// Transformation
	void transformationMario(int transfo);

	void animationWalk(float deltaTime);


	float speedMove = 0.4;
	float gravitySpeed = 0;
	float gravityForce = 0.03;

	float maxDeathingTime = 1000;
	float currendDeathingTime = 0;

	float maxInvulnerableTime = 1000; // 1 seconde
	int currentInvulnerableTime = 0;

	bool isTransforming = false;
	bool canJump = false;
	bool isAlive = true;

	Jump jump;

	SfmlImage *footHitbox;
	SfmlImage *headHitbox;
	SfmlImage *leftHitbox;
	SfmlImage *rightHitbox;

	sf::Vector2f velocity;

	// Sound effect
	SfmlAudio *jumpSound;
	SfmlAudio *powerupSound;
	SfmlAudio *pipeSound;
	SfmlAudio *kickSound;
	SfmlAudio *deadSound;
	
	State state = IDLE;

private:
	State previousState = state;

	Transformation transformation = SmallMario;
	Transformation previousTransformation = transformation;
	Transformation newTransformation;

	bool onceTimeLeft;
	bool onceTimeRight;
	bool isSpace = true;
	bool isDucking = false;

	// Sprite
	SfmlImage *marioSprite;

	float dunkTime;
	float jumpTimer = 0;
	float animationMoveTimer;
	float transformationTimer;

	void checkState();
	void switchState(float deltaTime);


	void setSmallMario();
	void setSuperMario();

	void animationSmallWalk(float deltaTime);
	void animationSuperWalk(float deltaTime);

	void setDuck();
	void inputMove();

	void jumping(float deltaTime);
	void inputJump();

	void input();

	// Inverse mirror mario sprite
	void wraparound();

	bool keyW = true;
	bool keyX = true;
	bool keyC = true;
	bool keyV = true;
};
#endif