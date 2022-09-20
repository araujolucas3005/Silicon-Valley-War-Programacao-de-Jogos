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
#include "Wall.h"
#include "EndGame.h"
#include <string>
#include <fstream>
#include <random>
#include <math.h>
using std::ifstream;
using std::string;

enum { MUSIC, SHOOT, BEEP, EXPLOSION, BLUE_EXPLOSION, PUFF };

// ------------------------------------------------------------------------------

std::random_device dev;
std::mt19937 rng(dev());

// ------------------------------------------------------------------------------

void Level1::Init()
{
    GameManager::currLevel = this;

    fontTimer = new Font("Resources/Digital.png");
    fontTimer->Spacing(24);

    // cria gerenciador de cena
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/Level1.jpg");

    explosionTs = new TileSet("Resources/Explosion2Small.png", 70, 40.66666f, 1, 6);
    blueExplosionTs = new TileSet("Resources/BlueExplosion2.png", 152, 88.16666f, 1, 6);
    puffTs = new TileSet("Resources/Puff.png", 128, 128, 10, 10);

    GameManager::blueExplosionTs = blueExplosionTs;
    GameManager::explosionTs = explosionTs;
    GameManager::puffTs = puffTs;

    playerOne = new Player({ 'W', 'A', 'S', 'D', 'K' }, PLAYER1, 0);
    playerOne->MoveTo(250.0f, 450.0f);
    scene->Add(playerOne, MOVING);

    playerTwo = new Player({ VK_UP, VK_LEFT, VK_DOWN, VK_RIGHT, VK_NUMPAD0 }, PLAYER2, 1);
    playerTwo->MoveTo(705.0f, 450.0f);
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
            fin >> y1; fin >> x2; fin >> y2;;

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

    audio = new Audio();
    audio->Add(MUSIC, "Resources/PVPMusic.wav");
    audio->Add(BEEP, "Resources/Beep.wav");
    audio->Play(MUSIC);

    foodTime = new Timer();
    foodTime->Start();

    levelTimer = new Timer();
    levelTimer->Start();

    endingTimer = new Timer();
    endingTimer->Start();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete foodTime;
    delete backg;
    delete scene;
    delete explosionTs;
    delete blueExplosionTs;
    delete puffTs;
    delete audio;
    delete fontTimer;
    delete levelTimer;
    delete endingTimer;
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
    int elapsed = floor(levelTimer->Elapsed());
    if (60 - elapsed <= 0) {
        if (playerOne->LifeCount() < playerTwo->LifeCount()) {
            GameManager::winner = PLAYER2;
        }
        else if (playerOne->LifeCount() > playerTwo->LifeCount()) {
            GameManager::winner = PLAYER1;
        }
        else {
            GameManager::draw = true;
        }

        Engine::Next<EndGame>();
        return;
    }

    if (60 - elapsed <= 5 && endingTimer->Elapsed() > 1.0f) {
        audio->Play(BEEP);
        endingTimer->Start();
    }

   /* if (elapsed >= 40 && elapsed < 50 && !musicCtrl[0]) {
        musicCtrl[0] = true;
        audio->Add(MUSIC, "Resources/PVPMusicFast.wav");
        audio->Play(MUSIC);
    }
    else if (elapsed >= 50 && !musicCtrl[0]) {
        musicCtrl[0] = true;
        audio->Add(MUSIC, "Resources/PVPMusicVeryFast.wav");
        audio->Play(MUSIC);
    }*/

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

    if (window->KeyDown(VK_ESCAPE)) {
        Engine::Next<Home>();
    } else if (GameManager::endGame)
    {
        GameManager::endGame = false;
        // volta para a tela de abertura
        Engine::Next<EndGame>();
    }
    else
    {
        // Adiciona comidas aleatorias na cena se o tempo se passou e se nao atingiu o limite de comidas
        if (foodTime->Elapsed() >= 5 && (GameManager::foodNow < GameManager::foodLimit))
        {
            std::uniform_int_distribution<std::mt19937::result_type> randomFt(0, 1);
            std::uniform_int_distribution<std::mt19937::result_type> randomPos(0, GameManager::PivotPositions.size() - 1);
            pair<float, float> foodPos = GameManager::PivotPositions[randomPos(rng)];
            scene->Add(new Food((FOODTYPE) randomFt(rng), foodPos.first, foodPos.second), STATIC);
            GameManager::foodNow++;
            foodTime->Start();
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

    Color white(1.0f, 1.0f, 1.0f, 1.0f);
    Color red(1.0f, 0.2f, 0.2f, 1.0f);
    Color yellow(1.0f, 1.0f, 0.4f, 1.0f);

    int elapsed = floor(levelTimer->Elapsed());
    int gameElapsed = 60 - elapsed;
    string elapsedStr = (gameElapsed < 10 ? "0" : "") + std::to_string(gameElapsed);

    fontTimer->Draw(window->CenterX()+15, 45, elapsedStr, gameElapsed > 20 ? white : gameElapsed > 10 ? yellow : red);

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------