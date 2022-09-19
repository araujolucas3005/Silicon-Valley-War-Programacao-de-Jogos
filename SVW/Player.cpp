/**********************************************************************************
// Player (Código Fonte)
//
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Player do jogo SVW
//
**********************************************************************************/

#include "SVW.h"
#include "Player.h"
#include "Pivot.h"
#include "Food.h"
#include "Projectile.h"
#include "GameManager.h"
#include "Wall.h"
#include "LevelAnim.h"
#include <random>
enum { MUSIC, EFFECT, FOODSOUND, DEATH, PROJECTILESOUND};

// ---------------------------------------------------------------------------------

Player::Player(MovementKeys movementKeys, PLAYERTYPE pt, int playerCount)
{
	this->movementKeys = movementKeys;

	playerSpriteID = playerCount;

	spriteL = new Sprite(GameManager::playerImages[playerCount] + "L.png");
	spriteR = new Sprite(GameManager::playerImages[playerCount] + "R.png");
	spriteU = new Sprite(GameManager::playerImages[playerCount] + "U.png");
	spriteD = new Sprite(GameManager::playerImages[playerCount] + "D.png");
	currSprite = spriteU;

	letterP = new Sprite("Resources/letterP.png");
	heart = new Image("Resources/heart.png");
	audio = new Audio();
	audio->Add(EFFECT, "Resources/PlayerCollisionSound.wav");
	audio->Add(FOODSOUND, "Resources/FoodSound.wav");
	audio->Add(PROJECTILESOUND, "Resources/ProjectileSound.wav");
	audio->Add(DEATH, "Resources/DeathSound.wav");


	if (pt == PLAYER1)
	{
		playerTypeSprite = new Sprite("Resources/number1.png");
	}
	else
	{
		playerTypeSprite = new Sprite("Resources/number2.png");
	}


	for (int i = 0; i < life; i++)
	{
		lifeChain.push_back(new Sprite(heart));
	}

	bulletHoriImg = new Image("Resources/BulletHori.png");
	bulletVerImg = new Image("Resources/BulletVer.png");
	specialPowerUp = new Image("Resources/specialPowerUp.png");
	specialPowerLeft = new Image("Resources/specialPowerLeft.png");
	specialPowerRight = new Image("Resources/specialPowerRight.png");
	specialPowerDown = new Image("Resources/specialPowerDown.png");

	// imagem do pacman é 48x48 (com borda transparente de 4 pixels)
	BBox(new Rect(-20, -20, 20, 20));
	type = PLAYER;
	playerType = pt;

	ctrlShot = true;

	timer = new Timer();
	specialPowerTimer = new Timer();
	timer->Start();
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete spriteL;
	delete spriteR;
	delete spriteU;
	delete spriteD;
	delete letterP;
	delete bulletHoriImg;
	delete bulletVerImg;
	delete playerTypeSprite;
	delete audio;

	for (int i = 0; i < life; i++)
	{
		delete lifeChain[i];
	}
}

// ---------------------------------------------------------------------------------

void Player::Stop()
{
	velX = 0;
	velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Up()
{
	velX = 0;
	velY = -200.0f;
}

// ---------------------------------------------------------------------------------

void Player::Down()
{
	velX = 0;
	velY = 200.0f;
}

// ---------------------------------------------------------------------------------

void Player::Left()
{
	velX = -200.0f;
	velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Right()
{
	velX = 200.0f;
	velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	if (obj->Type() == PLAYER)
	{
		Player* player = (Player*)obj;

		if (playerType == PLAYER1) {
			std::random_device dev;
			std::mt19937 rng(dev());

			std::uniform_int_distribution<std::mt19937::result_type> randomFt(0, 1);
			std::uniform_int_distribution<std::mt19937::result_type> randomPos(0, GameManager::PivotPositions.size() - 1);
			pair<float, float> pos1 = GameManager::PivotPositions[randomPos(rng)];
			pair<float, float> pos2 = GameManager::PivotPositions[randomPos(rng)];

			while (pos1.first != pos2.first && pos1.second != pos2.second) {
				audio->Play(EFFECT);
				pos1 = GameManager::PivotPositions[randomPos(rng)];
			}

			MoveTo(pos1.first, pos1.second);
			player->MoveTo(pos2.first, pos2.second);

			if (GameManager::puffTs) {
				LevelAnim* anim1 = new LevelAnim(GameManager::puffTs, 0.100f, false);
				LevelAnim* anim2 = new LevelAnim(GameManager::puffTs, 0.100f, false);

				anim1->MoveTo(x, y);
				anim2->MoveTo(player->X(), player->Y());

				GameManager::currLevel->scene->Add(anim1, STATIC);
				GameManager::currLevel->scene->Add(anim2, STATIC);
			}
		}
	

		Stop();

		//switch (currState)
		//{
		//case UP:
		//	MoveTo(x, player->Y() + 42);
		//	break;
		//case DOWN:
		//	MoveTo(x, player->Y() - 42);
		//	break;
		//case LEFT:
		//	MoveTo(player->X() + 42, y);
		//	break;
		//case RIGHT:
		//	MoveTo(player->X() - 42, y);
		//	break;
		//default:
		//	break;
		//}
		currState = nextState = STOPED;
	}
	if (obj->Type() == PROJECTILE)
	{
		Projectile* projectile = (Projectile*)obj;
		if (projectile->PlayerInfo() != this){
					
			if (projectile->PlayerInfo()->specialPower) {
				life -= 2;

				if (GameManager::blueExplosionTs) {
					LevelAnim* anim = new LevelAnim(GameManager::blueExplosionTs, 0.1f);

					anim->MoveTo(x, y);

					GameManager::currLevel->scene->Add(anim, STATIC);
				}
			}

			else {
				life--;

				if (GameManager::explosionTs) {
					LevelAnim* anim = new LevelAnim(GameManager::explosionTs, 0.1f);

					anim->MoveTo(x, y);

					GameManager::currLevel->scene->Add(anim, STATIC);
				}
			}
		}
	
		if (life <= 0)
		{
			audio->Play(DEATH);
			Sleep(1000);
			GameManager::winner = projectile->PlayerInfo()->playerType;
			GameManager::winnerSpriteID = playerSpriteID;
			GameManager::endGame = true;
		}
	}
	if (obj->Type() == FOOD)
	{
		Food* fd = (Food*)obj;

		if (fd->foodType == MONEY && life < 3)
			life++;
		else
		{
			specialPower = true;
			specialPowerTimer->Start();
		}
		audio->Play(FOODSOUND);
		GameManager::currLevel->scene->Delete(fd, STATIC);
		GameManager::foodNow--;
	}
	if (obj->Type() == PIVOT) {
		PivotCollision(obj);
	}

	if (obj->Type() == WALL) {
		Wall* wall = (Wall*)obj;

		Stop();

		switch (currState) {
		case UP: MoveTo(x, prevY + 1); break;
		case DOWN: MoveTo(x, prevY - 1); break;
		case LEFT: MoveTo(prevX + 1, prevY); break;
		case RIGHT: MoveTo(prevX - 1, prevY); break;
		}
	}
}

// ---------------------------------------------------------------------------------

void Player::PivotCollision(Object* obj)
{
	Pivot* p = (Pivot*)obj;

	switch (currState)
	{
	case STOPED:
		// -----------------------
		// CurrentState == STOPED
		// -----------------------

		switch (nextState)
		{
		case LEFT:
			if (p->left)
			{
				currState = LEFT;
				Left();
			}
			break;
		case RIGHT:
			if (p->right)
			{
				currState = RIGHT;
				Right();
			}

			break;
		case UP:
			if (p->up)
			{
				currState = UP;
				Up();
			}
			break;
		case DOWN:
			if (p->down)
			{
				currState = DOWN;
				Down();
			}
			break;
		}
		break;

	case LEFT:
		// -----------------------
		// CurrentState == LEFT
		// -----------------------

		if (x < p->X())
		{
			if (!p->left)
			{
				MoveTo(p->X(), Y());
				currState = STOPED;
				Stop();
			}
		}

		switch (nextState)
		{
		case LEFT:
			if (x < p->X())
			{
				if (!p->left)
				{
					MoveTo(p->X(), Y());
					currState = STOPED;
					Stop();
				}
			}
			break;
		case RIGHT:
			currState = RIGHT;
			Right();

			break;
		case UP:
			if (x < p->X())
			{
				if (p->up)
				{
					MoveTo(p->X(), Y());
					currState = UP;
					Up();
				}
			}
			break;
		case DOWN:
			if (x < p->X())
			{
				if (p->down)
				{
					MoveTo(p->X(), Y());
					currState = DOWN;
					Down();
				}
			}
			break;
		}
		break;

	case RIGHT:
		// -----------------------
		// CurrentState == RIGHT
		// -----------------------

		if (x > p->X())
		{
			if (!p->right)
			{
				MoveTo(p->X(), Y());
				currState = STOPED;
				Stop();
			}
		}

		switch (nextState)
		{
		case LEFT:
			currState = LEFT;
			Left();
			break;
		case RIGHT:
			if (x > p->X())
			{
				if (!p->right)
				{
					MoveTo(p->X(), Y());
					currState = STOPED;
					Stop();
				}
			}

			break;
		case UP:
			if (x > p->X())
			{
				if (p->up)
				{
					MoveTo(p->X(), Y());
					currState = UP;
					Up();
				}
			}
			break;
		case DOWN:
			if (x > p->X())
			{
				if (p->down)
				{
					MoveTo(p->X(), Y());
					currState = DOWN;
					Down();
				}
			}
			break;
		}
		break;

	case UP:
		// -----------------------
		// CurrentState == UP
		// -----------------------

		if (y < p->Y())
		{
			if (!p->up)
			{
				MoveTo(x, p->Y());
				currState = STOPED;
				Stop();
			}
		}

		switch (nextState)
		{
		case LEFT:
			if (y < p->Y())
			{
				if (p->left)
				{
					MoveTo(x, p->Y());
					currState = LEFT;
					Left();
				}
			}
			break;
		case RIGHT:
			if (y < p->Y())
			{
				if (p->right)
				{
					MoveTo(x, p->Y());
					currState = RIGHT;
					Right();
				}
			}
			break;
		case UP:
			if (y < p->Y())
			{
				if (!p->up)
				{
					MoveTo(x, p->Y());
					currState = STOPED;
					Stop();
				}
			}
			break;
		case DOWN:
			currState = DOWN;
			Down();
			break;
		}
		break;

	case DOWN:
		// -----------------------
		// CurrentState == DOWN
		// -----------------------

		if (y > p->Y())
		{
			if (!p->down)
			{
				MoveTo(x, p->Y());
				currState = STOPED;
				Stop();
			}
		}

		switch (nextState)
		{
		case LEFT:
			if (y > p->Y())
			{
				if (p->left)
				{
					MoveTo(x, p->Y());
					currState = LEFT;
					Left();
				}
			}
			break;
		case RIGHT:
			if (y > p->Y())
			{
				if (p->right)
				{
					MoveTo(x, p->Y());
					currState = RIGHT;
					Right();
				}
			}
			break;
		case UP:
			currState = UP;
			Up();
			break;
		case DOWN:
			if (y > p->Y())
			{
				if (!p->down)
				{
					MoveTo(x, p->Y());
					currState = STOPED;
					Stop();
				}
			}
			break;
		}
		break;
	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	prevX = x;
	prevY = y;

	if (window->KeyDown(movementKeys.left))
	{
		nextState = LEFT;

		if (currState == RIGHT || currState == STOPED)
		{
			currState = LEFT;
			Left();
		}
	}

	if (window->KeyDown(movementKeys.right))
	{
		nextState = RIGHT;

		if (currState == LEFT || currState == STOPED)
		{
			currState = RIGHT;
			Right();
		}
	}

	if (window->KeyDown(movementKeys.up))
	{
		nextState = UP;

		if (currState == DOWN || currState == STOPED)
		{
			currState = UP;
			Up();
		}
	}

	if (window->KeyDown(movementKeys.down))
	{
		nextState = DOWN;

		if (currState == UP || currState == STOPED)
		{
			currState = DOWN;
			Down();
		}
	}

	if (timer->Elapsed() > 1 && ctrlShot && window->KeyDown(movementKeys.shoot))
	{
		timer->Start();

		ctrlShot = false;
		audio->Play(PROJECTILESOUND);

		float pX = 0;
		float pY = 0;
		float pVelX = 0;
		float pVelY = 0;

		Image* bulletImg = nullptr;

		switch (currState) {
		case UP: pVelX = 0; pVelY = -250.0f; pX = X(); pY = Y() - 15; bulletImg = specialPower ? specialPowerUp : bulletVerImg; break;
		case LEFT: pVelX = -250.0f; pVelY = 0;  pX = X() - 15; pY = Y(); bulletImg = specialPower ? specialPowerLeft : bulletHoriImg;  break;
		case DOWN: pVelX = 0; pVelY = 250.0f;  pX = X(); pY = Y() + 15; bulletImg = specialPower ? specialPowerDown : bulletVerImg;  break;
		case RIGHT: pVelX = 250.0f; pVelY = 0;  pX = X() + 15; pY = Y(); bulletImg = specialPower ? specialPowerRight : bulletHoriImg; break;
		}

		if (bulletImg) {
			Projectile* b = new Projectile(this, pVelX, pVelY, bulletImg);

			if (bulletImg == bulletVerImg) {
				b->BBox(new Rect(-2.5, 9, 2.5, -9));
			}
			else {
				b->BBox(new Rect(-9, 2.5, 9, -2.5));
			}

			b->MoveTo(pX, pY);

			GameManager::currLevel->scene->Add(b, MOVING);
		}
	}
	else if (window->KeyUp(movementKeys.shoot)) {
		ctrlShot = true;
	}

	if (specialPower)
	{
		if (specialPowerTimer->Elapsed() >= 8)
		{
			specialPower = false;
		}
	}

	// atualiza posição
	Translate(velX * gameTime, velY * gameTime);

	// mantém player dentro da tela
	if (x + 20 < 0)
		MoveTo(window->Width() + 20.f, Y());

	if (x - 20 > window->Width())
		MoveTo(-20.0f, Y());

	if (Y() + 20 < 0)
		MoveTo(x, window->Height() + 20.0f);

	if (Y() - 20 > window->Height())
		MoveTo(x, -20.0f);
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
	switch (currState)
	{
	case LEFT:  currSprite = spriteL; break;
	case RIGHT: currSprite = spriteR; break;
	case UP:    currSprite = spriteU; break;
	case DOWN:  currSprite = spriteD; break;
		//default:
		//	switch (nextState)
		//	{
		//	case LEFT:  currSprite = spriteL; break;
		//	case RIGHT: currSprite = spriteR; break;
		//	case UP:    currSprite = spriteU; break;
		//	case DOWN:  currSprite = spriteD; break;
		//	}
	}

	currSprite->Draw(x, y, Layer::UPPER);

	float heartX = 90.0f;
	if (playerType == PLAYER1)
	{
		letterP->Draw(30.0f, window->Height() - 18.0f);
		playerTypeSprite->Draw(53.0f, window->Height() - 15.0f);

		for (int i = 0; i < life; i++)
		{
			lifeChain[i]->Draw(heartX, window->Height() - 15.0f);
			heartX += 40.0f;
		}
	}
	else
	{
		heartX = window->Width() - 184.0f;
		letterP->Draw(window->Width() - 247.0f, window->Height() - 18.0f);
		playerTypeSprite->Draw(window->Width() - 224.0f, window->Height() - 15.0f);
		for (int i = 0; i < life; i++)
		{
			lifeChain[i]->Draw(heartX, window->Height() - 15.0f);
			heartX += 40.0f;
		}
	}
}