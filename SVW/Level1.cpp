/**********************************************************************************
// Level1 (Código Fonte)
//
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nível 1 do jogo SVW
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "Player.h"
#include "Pivot.h"
#include "GameManager.h"
#include "Wall.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

void Level1::Init()
{
	GameManager::currLevel = this;

	// cria gerenciador de cena
	scene = new Scene();

	// cria background
	backg = new Sprite("Resources/Level1.jpg");

	Player* playerOne = new Player({ VK_UP, VK_LEFT, VK_DOWN, VK_RIGHT, VK_NUMPAD0 });
	playerOne->MoveTo(600.0f, 450.0f);
	scene->Add(playerOne, MOVING);

	Player* playerTwo = new Player({ 'W', 'A', 'S', 'D', 'K' });
	playerTwo->MoveTo(400.0f, 450.0f);
	scene->Add(playerTwo, MOVING);

	// cria pontos de mudança de direção
	Pivot* pivot;
	bool left, right, up, down;
	float posX, posY;

	// cria pivôs a partir do arquivo
	ifstream fin;
	fin.open("PivotsL1.txt");
	fin >> left;
	while (!fin.eof())
	{
		if (fin.good())
		{
			// lê linha de informações do pivô
			fin >> right; fin >> up; fin >> down; fin >> posX; fin >> posY;
			pivot = new Pivot(left, right, up, down);
			pivot->MoveTo(posX, posY);
			scene->Add(pivot, STATIC);
		}
		else
		{
			// ignora comentários
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}
		fin >> left;
	}
	fin.close();

	fin.open("RangedPivotsL1.txt");
	bool wich;
	float end;
	fin >> left;
	while (!fin.eof())
	{
		if (fin.good())
		{
			// lê linha de informações do pivô
			fin >> right; fin >> up; fin >> down; fin >> posX; fin >> posY; fin >> wich; fin >> end;

			if (wich) {
				for (float i = posX; i <= end; i += 7.0f) {
					pivot = new Pivot(left, right, up, down);
					pivot->MoveTo(i, posY);
					scene->Add(pivot, STATIC);
				}
			}
			else {
				for (float i = posY; i <= end; i += 7.0f) {
					pivot = new Pivot(left, right, up, down);
					pivot->MoveTo(posX, i);
					scene->Add(pivot, STATIC);
				}
			}
		}
		else
		{
			// ignora comentários
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}
		fin >> left;
	}
	fin.close();

	Wall* wall;
	float temp;
	float x1, y1, x2, y2;
	float X1, Y1, X2, Y2;
	fin.open("WallsL1.txt");
	fin >> x1;
	while (!fin.eof())
	{
		if (fin.good())
		{
			// lê linha de informações do pivô
			fin >> y1; fin >> x2; fin >> y2;

			X1 = (x1 - x2) / 2.0f;
			X2 = -X1;

			Y1 = (y1 - y2) / 2.0f;
			Y2 = -Y1;

			wall = new Wall(X1, Y1, X2, Y2);
			wall->MoveTo(x1 + X2, y1 + Y2);
			scene->Add(wall, STATIC);

			temp = x2;
			x2 = window->Width() - x1;
			x1 = window->Width() - temp;

			wall = new Wall(X1, Y1, X2, Y2);
			wall->MoveTo(x1 + X2, y1 + Y2);
			scene->Add(wall, STATIC);
		}
		else
		{
			// ignora comentários
			fin.clear();
			char temp[80];
			fin.getline(temp, 80);
		}
		fin >> x1;
	}
	fin.close();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
	delete backg;
	delete scene;
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
	// habilita/desabilita bounding box
	if (ctrlKeyB && window->KeyDown('B'))
	{
		viewBBox = !viewBBox;
		ctrlKeyB = false;
	}
	else if (window->KeyUp('B'))
	{
		ctrlKeyB = true;
	}

	if (window->KeyDown(VK_ESCAPE))
	{
		// volta para a tela de abertura
		Engine::Next<Home>();
	}
	else if (window->KeyDown('N'))
	{
		// passa manualmente para o próximo nível
		Engine::Next<Level2>();
	}
	else
	{
		// atualiza cena
		scene->Update();
		scene->CollisionDetection();
	}
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
	// desenha cena
	backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
	scene->Draw();

	// desenha bounding box dos objetos
	if (viewBBox)
		scene->DrawBBox();
}

// ------------------------------------------------------------------------------