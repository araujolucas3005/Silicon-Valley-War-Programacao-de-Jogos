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
#include "Player.h"
#include "Pivot.h"
#include "Food.h"
#include "GameManager.h"
#include <string>
#include <fstream>
#include <random>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

std::random_device dev;
std::mt19937 rng(dev());

// ------------------------------------------------------------------------------

void Level1::Init()
{
    GameManager::currLevel = this;

    // cria gerenciador de cena
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/Level1.jpg");

    Player* playerOne = new Player({ VK_UP, VK_LEFT, VK_DOWN, VK_RIGHT, VK_NUMPAD0 }, PLAYER1);
    playerOne->MoveTo(600.0f, 450.0f);
    scene->Add(playerOne, MOVING);

    Player* playerTwo = new Player({ 'W', 'A', 'S', 'D', 'K' }, PLAYER2);
    playerTwo->MoveTo(400.0f, 450.0f);
    scene->Add(playerTwo, MOVING);

    // cria pontos de mudança de direção
    Pivot * pivot;
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
            GameManager::PivotPositions.push_back({ posX, posY });
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

    foodTime = new Timer();
    foodTime->Start();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete foodTime;
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
    
    if (window->KeyDown(VK_ESCAPE) || GameManager::endGame)
    {
        GameManager::endGame = false;
        // volta para a tela de abertura
        Engine::Next<Home>();
    }
    else
    {
        // Adiciona comidas aleatorias na cena se o tempo se passou e se nao atingiu o limite de comidas
        if (foodTime->Elapsed() > 30 && (GameManager::foodNow < GameManager::foodLimit))
        {
            std::uniform_int_distribution<std::mt19937::result_type> randomFt(0, 1);
            std::uniform_int_distribution<std::mt19937::result_type> randomPos(0, GameManager::PivotPositions.size() - 1);
            foodTime->Start();
            pair<float, float> foodPos = GameManager::PivotPositions[randomPos(rng)];
            scene->Add(new Food((FOODTYPE) randomFt(rng), foodPos.first, foodPos.second), STATIC);
            GameManager::foodNow++;
        }

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