#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#pragma once

#include "../DataGame/DataGame.hpp"
// #include <vector>

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void run(float deltaTime);

	void draw(sf::RenderWindow &window) const;

	sf::Vector2f getMarioPosition();

	Map *map;
	Mario *mario;
	Uhd *uhd;

	float winTimer = 0;


private:
	Collider *collider;

	std::vector<Block> blocks;
	std::vector<Shroom> shrooms;
	std::vector<Goomba> goombas;
	std::vector<ParaGoomba> paraGoombas;
	std::vector<Rex> rexs;
	std::vector<Coin> coins;

	SfmlImage *flag;
	SfmlImage *deadZone;

	void initActor();

	void update(float deltaTime);

	void performActorsMovement(float deltaTime);

	void gravityStep(float deltaTime);

	// Collsion
	void collisionStep();
	void checkActorOnGround();
	void checkMarioJump();
	void headOnBlock();
	void marioRebondOnEnnemies();
	void marioGetHurt();
	void collisionNotTrigger();
	void marioCollisionOnCoin();
	void marioHeadOnBlock();
	void cancelMarioCollision(sf::Sprite &box);
	void instantKillMario();

	// Shroom
	void shroomMarioPowerUp();
	void changeShroomDirection();

	// Win
	bool isWon = false;
	bool playWinMusicOnce = true;
	SfmlAudio *winMusic;

	SfmlAudio *mainTheme;

	void winEngine(float deltaTime);
	void winCondition();
	void makeMarioMoveRight(float deltaTime);
	void playMusicWin();
};
#endif