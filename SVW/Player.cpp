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
#include "Projectile.h"
#include "GameManager.h"

// ---------------------------------------------------------------------------------

Player::Player(MovementKeys movementKeys)
{
	this->movementKeys = movementKeys;

	spriteL = new Sprite("Resources/PacManL.png");
	spriteR = new Sprite("Resources/PacManR.png");
	spriteU = new Sprite("Resources/PacManU.png");
	spriteD = new Sprite("Resources/PacManD.png");

	bulletHoriImg = new Image("Resources/BulletHori.png");
	bulletVerImg = new Image("Resources/BulletVer.png");

	// imagem do pacman é 48x48 (com borda transparente de 4 pixels)
	BBox(new Rect(-20, -20, 20, 20));
	type = PLAYER;

	ctrlShot = true;

	timer = new Timer();
	timer->Start();
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete spriteL;
	delete spriteR;
	delete spriteU;
	delete spriteD;
	delete bulletHoriImg;
	delete bulletVerImg;
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
	velY = -250.0f;
}

// ---------------------------------------------------------------------------------

void Player::Down()
{
	velX = 0;
	velY = 250.0f;
}

// ---------------------------------------------------------------------------------

void Player::Left()
{
	velX = -250.0f;
	velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Right()
{
	velX = 250.0f;
	velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	if (obj->Type() == PLAYER)
	{
		Stop();
		Player* player = (Player*)obj;

		switch (currState)
		{
		case UP:
			MoveTo(x, player->Y() + 42);
			break;
		case DOWN:
			MoveTo(x, player->Y() - 42);
			break;
		case LEFT:
			MoveTo(player->X() + 42, y);
			break;
		case RIGHT:
			MoveTo(player->X() - 42, y);
			break;
		default:
			break;
		}
		currState = STOPED;
	}
	if (obj->Type() == PIVOT)
		PivotCollision(obj);
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

		float pX = 0;
		float pY = 0;
		float pVelX = 0;
		float pVelY = 0;

		Image* bulletImg = nullptr;

		switch (currState) {
			case UP: pVelX = 0; pVelY = -250.0f; pX = X(); pY = Y() - 15; bulletImg = bulletVerImg; break;
			case LEFT: pVelX = -250.0f; pVelY = 0;  pX = X() - 15; pY = Y(); bulletImg = bulletHoriImg;  break;
			case DOWN: pVelX = 0; pVelY = 250.0f;  pX = X(); pY = Y() + 15; bulletImg = bulletVerImg;  break;
			case RIGHT: pVelX = 250.0f; pVelY = 0;  pX = X() + 15; pY = Y(); bulletImg = bulletHoriImg; break;
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
	case LEFT:  spriteL->Draw(x, y, Layer::UPPER); break;
	case RIGHT: spriteR->Draw(x, y, Layer::UPPER); break;
	case UP:    spriteU->Draw(x, y, Layer::UPPER); break;
	case DOWN:  spriteD->Draw(x, y, Layer::UPPER); break;
	default:
		switch (nextState)
		{
		case LEFT:  spriteL->Draw(x, y, Layer::UPPER); break;
		case RIGHT: spriteR->Draw(x, y, Layer::UPPER); break;
		case UP:    spriteU->Draw(x, y, Layer::UPPER); break;
		case DOWN:  spriteD->Draw(x, y, Layer::UPPER); break;
		default:    spriteL->Draw(x, y, Layer::UPPER);
		}
	}
}