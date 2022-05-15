#include "Mario.hpp"
#include "../../../System/Input.h"

Mario::Mario()
{
     // Init mario sprite
     marioSprite = new SfmlImage("ressources/Mario/SNES - Super Mario World - Mario.png", 1004, 3618, 200, 1050);
     marioSprite->getSprite().setTextureRect(sf::IntRect(24, 51, 16, 22));
     marioSprite->getSprite().setScale(2, 2);
     marioSprite->SetCentralOrigin();

     footHitbox = new SfmlImage("ressources/Images/hitbox.png", 100, 100, 0, 0);
     footHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 16, 8));
     footHitbox->SetCentralOrigin();

     headHitbox = new SfmlImage("ressources/Images/hitbox.png", 100, 100, 0, 0);
     headHitbox->SetCentralOrigin();

     rightHitbox = new SfmlImage("ressources/Images/hitbox.png", 100, 100, 0, 0);
     rightHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 3, 5));
     rightHitbox->SetCentralOrigin();

     leftHitbox = new SfmlImage("ressources/Images/hitbox.png", 100, 100, 0, 0);
     leftHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 3, 5));
     leftHitbox->SetCentralOrigin();

     // Sound
     jumpSound = new SfmlAudio("ressources/Sound/Snes Mario World/jump.wav");
     powerupSound = new SfmlAudio("ressources/Sound/Snes Mario World/powerup.wav");
     pipeSound = new SfmlAudio("ressources/Sound/Snes Mario World/pipe.wav");
     kickSound = new SfmlAudio("ressources/Sound/Snes Mario World/kick.wav");
     deadSound = new SfmlAudio("ressources/Sound/Video Game Deaths Super Mario World (SNES) (Death AnimationGame Over).wav");

     // For Wraparound
     onceTimeLeft = true;
     onceTimeRight = true;

     setSmallMario();
}

Mario::~Mario()
{
     delete jumpSound;
     delete powerupSound;
     delete kickSound;
     delete pipeSound;
     delete deadSound;
     delete marioSprite;
     delete headHitbox;
     delete footHitbox;
     delete leftHitbox;
     delete rightHitbox;
}

void Mario::draw(sf::RenderWindow &window) const
{
     marioSprite->draw(window);
}

void Mario::update(float deltaTime)
{
     wraparound();

     invulnerable(deltaTime);

     switchState(deltaTime);
}

void Mario::performMovement(float deltaTime)
{
     float xMov = 0;
     float yMov = 0;

     gravity(deltaTime);

     if (state != DUNK)
     {
          xMov = Input::getAxisRaw("Horizontal") * speedMove * deltaTime;
     }

     yMov = (-jump.jumpSpeed + gravitySpeed) * deltaTime;

     marioSprite->getSprite().move(xMov, yMov);

     velocity.x = xMov;
     velocity.y = yMov;

     setPositionHitbox();
}

void Mario::deathing(float deltaTime)
{
     currendDeathingTime += deltaTime;
     if (currendDeathingTime >= maxDeathingTime)
     {
          getSprite().move(0, -jump.jumpSpeed);
          jump.jumpSpeed -= 0.2;
     }
}

void Mario::gravity(float deltaTime)
{
     if (canJump)
          gravitySpeed = 0;
     else
          gravitySpeed += gravityForce;
}

void Mario::makeDead()
{
     transformation = SmallMario;
     powerDown();
}

// Transformation
void Mario::transformationMario(int transfo)
{
     isTransforming = true;

     if (SmallMario == transfo)
          newTransformation = SmallMario;

     switch (transfo)
     {
     case SmallMario:
          newTransformation = SmallMario;
          break;
     case SuperMario:
          newTransformation = SuperMario;
          break;
     case FireMario:
          newTransformation = FireMario;
          break;
     }
}

void Mario::setCanJump(bool jump)
{
     canJump = jump;
}

// Get Mario sprite
sf::Sprite &Mario::getSprite()
{
     return marioSprite->getSprite();
}

sf::Vector2f &Mario::getVelocity()
{
     return velocity;
}

// Private function

void Mario::setSmallMario()
{
     previousTransformation = transformation;
     transformation = SmallMario;
}

void Mario::setSuperMario()
{
     previousTransformation = transformation;
     transformation = SuperMario;
}

void Mario::invulnerable(float deltaTime)
{
     if (currentInvulnerableTime > 0)
          currentInvulnerableTime += deltaTime;

     if (currentInvulnerableTime >= maxInvulnerableTime)
     {
          currentInvulnerableTime = 0;
          getSprite().setColor(sf::Color(255, 255, 255, 255));
     }

     if (currentInvulnerableTime % 4 == 0)
          getSprite().setColor(sf::Color(255, 255, 255, 255));
     else
          getSprite().setColor(sf::Color(255, 255, 255, 0));
}

void Mario::transforming(float deltaTime)
{
     if (isTransforming)
     {
          transformationTimer += deltaTime;

          if ((int)(transformationTimer) % 30 == 0)
          {
               if (transformation == SmallMario)
                    marioSprite->getSprite().move(0, 15);
               else if (transformation == SuperMario)
                    marioSprite->getSprite().move(0, -3);

               marioSprite->getSprite().setTextureRect(sf::IntRect(24, 51, 16, 22));
          }
          else
          {
               if (transformation == SmallMario)
                    marioSprite->getSprite().move(0, -15);
               else if (transformation == SuperMario)
                    marioSprite->getSprite().move(0, 3);

               marioSprite->getSprite().setTextureRect(sf::IntRect(24, 586, 16, 30));
          }

          if (transformationTimer > 500)
          {
               isTransforming = false;
               transformationTimer = 0;
               transformation = newTransformation;
               if (transformation == SmallMario)
                    marioSprite->getSprite().move(0, 20);
          }
     }
}

void Mario::powerUp()
{
     if (transformation == SmallMario)
     {
          transformationMario(SuperMario);
          powerupSound->sound.play();
     }
}

void Mario::powerDown()
{
     if (transformation == SmallMario)
     {
          jump.jumpSpeed = 10;
          isAlive = false;
          deadSound->sound.play();
          marioSprite->getSprite().setTextureRect(sf::IntRect(544, 266, 16, 25));
     }
     else if (transformation == SuperMario)
     {
          pipeSound->sound.play();
          transformationMario(SmallMario);
          currentInvulnerableTime = 1;
     }
}

// State Function

void Mario::switchState(float deltaTime)
{
     switch (state)
     {
     case IDLE:
          setIdle();
          setStateMoving();
          setStateDunk();
          setStateJump();
          if (jump.jumpSpeed > 0)
          {
               jump.updateJumpSpeed();
          }
          break;

     case MOVE:
          animationWalk(deltaTime);
          setStateJump();
          setStateDunk();
          if (Input::getAxisRaw("Horizontal") == 0)
          {
               state = IDLE;
          }
          break;

     case JUMP:
          jumping(deltaTime);
          break;

     case FALLING:
          if (canJump)
               setStateIdle();
          break;

     case DUNK:
          setDuck();
          break;
     }
}

// Fcutnions set State

void Mario::setStateIdle()
{
     previousState = state;
     state = IDLE;
}

void Mario::setStateMoving()
{
     if (Input::getAxisRaw("Horizontal") != 0)
     {
          previousState = state;
          state = MOVE;
     }
}

void Mario::setStateJump()
{
     if (Input::getInputAction("Jump") && isSpace && canJump)
     {
          previousState = state;
          state = JUMP;
          jumpSound->sound.play();
          canJump = false;
          isSpace = false;
          jump.initJumpSpeed();
     }
     else if (!Input::getInputAction("Jump"))
          isSpace = true;
}

void Mario::setStateDunk()
{
     if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
     {
          previousState = state;
          state = DUNK;
     }
}

void Mario::setIdle()
{
     if (transformation == SmallMario)
          marioSprite->getSprite().setTextureRect(sf::IntRect(24, 51, 16, 22));
     else if (transformation == SuperMario)
          marioSprite->getSprite().setTextureRect(sf::IntRect(24, 586, 16, 30));
}

void Mario::setDuck()
{
     if (Input::getAxisRaw("Vertical") > 0)
     {
          if (transformation == SmallMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(128, 51, 16, 22));
          else if (transformation == SuperMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(128, 586, 16, 30));
     }
     else
     {
          setStateIdle();
     }
}

void Mario::setMarioVictoryStyle()
{
     if (transformation == SmallMario)
          marioSprite->getSprite().setTextureRect(sf::IntRect(700, 114, 18, 22));
     else if (transformation == SuperMario)
          marioSprite->getSprite().setTextureRect(sf::IntRect(699, 657, 18, 30));
}

void Mario::animationWalk(float deltaTime)
{
     if (transformation == SmallMario)
          animationSmallWalk(deltaTime);
     else if (transformation == SuperMario)
          animationSuperWalk(deltaTime);
}

void Mario::animationSmallWalk(float deltaTime)
{
     animationMoveTimer += deltaTime;

     if (animationMoveTimer > 200)
          animationMoveTimer = 0;
     else if (animationMoveTimer > 100)
          marioSprite->getSprite().setTextureRect(sf::IntRect(181, 51, 16, 22));
     else if (animationMoveTimer > 0)
          marioSprite->getSprite().setTextureRect(sf::IntRect(24, 51, 16, 22));
}

void Mario::animationSuperWalk(float deltaTime)
{
     animationMoveTimer += deltaTime;

     if (animationMoveTimer > 300)
          animationMoveTimer = 0;
     else if (animationMoveTimer > 200)
          marioSprite->getSprite().setTextureRect(sf::IntRect(179, 586, 18, 30));
     else if (animationMoveTimer > 100)
          marioSprite->getSprite().setTextureRect(sf::IntRect(232, 586, 17, 30));
     else if (animationMoveTimer > 0)
          marioSprite->getSprite().setTextureRect(sf::IntRect(24, 586, 16, 30));
}

void Mario::wraparound()
{
     if (Input::getAxisRaw("Horizontal") < 0 && onceTimeLeft)
     {
          onceTimeLeft = false;
          onceTimeRight = true;
          marioSprite->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 10 - (marioSprite->getSprite().getTextureRect().width * fabs(marioSprite->getSprite().getScale().x)) * 1 / 2, marioSprite->getSprite().getPosition().y);
          marioSprite->getSprite().setScale(abs(getSprite().getScale().x), abs(getSprite().getScale().y));
     }
     else if (Input::getAxisRaw("Horizontal") > 0 && onceTimeRight)
     {
          onceTimeLeft = true;
          onceTimeRight = false;
          marioSprite->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 10 + (marioSprite->getSprite().getTextureRect().width * fabs(marioSprite->getSprite().getScale().x)) * 1 / 2, marioSprite->getSprite().getPosition().y);
          marioSprite->getSprite().setScale(-abs(getSprite().getScale().x), abs(getSprite().getScale().y));
     }
}

void Mario::jumping(float deltaTime)
{
     // Set sprite anime
     if (Input::getAxisRaw("Vertical") > 0)
     {
          // Sprite Dunk
          if (transformation == SmallMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(128, 51, 16, 22));
          else if (transformation == SuperMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(128, 586, 16, 30));
     }
     else
     {
          // Sprite Jump
          if (transformation == SmallMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(75, 112, 17, 42));
          else if (transformation == SuperMario)
               marioSprite->getSprite().setTextureRect(sf::IntRect(75, 654, 18, 32));
     }

     jump.updateJumpSpeed();

     // Jump End
     if (jump.jumpSpeed <= 0 || canJump)
     {
          jump.setJumpSpeed(0);
          previousState = state;
          if (canJump)
          {
               setIdle();
               setStateIdle();
          }
          else
               state = FALLING;
     }
}

void Mario::setPositionHitbox()
{
     rightHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + marioSprite->getSprite().getTextureRect().width * fabs(marioSprite->getSprite().getScale().x) / 2, marioSprite->getSprite().getPosition().y - 10);
     leftHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - marioSprite->getSprite().getTextureRect().width * fabs(marioSprite->getSprite().getScale().x) / 2, marioSprite->getSprite().getPosition().y - 10);

     if (transformation == SuperMario)
     {
          rightHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 3, 20));
          leftHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 3, 20));
     }
     else if (transformation == SmallMario)
     {
          rightHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 3, 8));
          leftHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 3, 8));
     }

     if (state == IDLE)
     {
          if (transformation == SuperMario)
          {
               footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 3, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 + 5);

               headHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 18, 3));
               headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 30);
          }
          else if (transformation == SmallMario)
          {
               footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 - 3 * fabs(marioSprite->getSprite().getScale().y) + 1);

               headHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 18, 3));
               headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 30);
          }
     }
     else if (state == MOVE)
     {
          if (transformation == SuperMario)
          {
               footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 0, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 + 5);

               headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 30);
          }
          else if (transformation == SmallMario)
          {
               if (marioSprite->getSprite().getScale().x > 0)
                    footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 0, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 - 3 * fabs(marioSprite->getSprite().getScale().y));
               else
                    footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 3, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 - 3 * fabs(marioSprite->getSprite().getScale().y));

               headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 30);
          }
     }
     else if (state == DUNK)
     {
          if (transformation == SuperMario)
          {
               footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 8, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 + 5);

               headHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 18, 3));
               headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 30);
          }
          else if (transformation == SmallMario)
          {
               if (marioSprite->getSprite().getScale().x > 0)
                    footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 0, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 - 3 * fabs(marioSprite->getSprite().getScale().y) + 1);
               else
                    footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 3, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 - 3 * fabs(marioSprite->getSprite().getScale().y) + 1);

               headHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 18, 3));
               headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 30);
          }
     }
     else if (state == JUMP || state == FALLING)
     {
          if (transformation == SuperMario)
          {
               if (marioSprite->getSprite().getScale().x > 0)
                    footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 10, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 + 5);
               else
                    footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 5, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 + 5);

               headHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 18, 3));
               headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 30);

               if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 50);
          }
          else if (transformation == SmallMario)
          {
               if (marioSprite->getSprite().getScale().x > 0)
               {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                         footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 5, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 - 3 * fabs(marioSprite->getSprite().getScale().y) + 1);
                    else
                         footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 0, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 - 20);
               }
               else
               {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                         footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 3, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 - 3 * fabs(marioSprite->getSprite().getScale().y) + 1);
                    else
                         footHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x - 0, marioSprite->getSprite().getPosition().y + marioSprite->getSprite().getTextureRect().height * fabs(marioSprite->getSprite().getScale().y) / 2 - 20);
               }

               headHitbox->getSprite().setTextureRect(sf::IntRect(0, 0, 18, 3));
               headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 30);

               if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    headHitbox->getSprite().setPosition(marioSprite->getSprite().getPosition().x + 40, marioSprite->getSprite().getPosition().y + 40);
          }
     }
}