/**********************************************************************************
// Home (Código Fonte) 
// 
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Tela de abertura do jogo SVW
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "Level1.h"
#include "CharSelect.h"

enum { MUSIC, TRANSITION };

// ------------------------------------------------------------------------------

void Home::Init()
{
    backg = new Sprite("Resources/menu_principal_v2.png");
    controls = new Sprite("Resources/controles.png");
    audio = new Audio();
    audio->Add(MUSIC, "Resources/HomeMusic.wav");
    audio->Add(TRANSITION, "Resources/Transition.wav");
    audio->Play(MUSIC);

    
}

// ------------------------------------------------------------------------------

void Home::Finalize()
{
    delete backg;
    delete audio;
}

// ------------------------------------------------------------------------------

void Home::Update()
{
    // sai do jogo com a tecla ESC
    if (ctrlKeyESC && window->KeyDown(VK_ESCAPE))
    {
        ctrlKeyESC = false;
        window->Close();
    }
    else if (window->KeyUp(VK_ESCAPE))
    {
        ctrlKeyESC = true;
    }

    // passa ao primeiro nível com ENTER
    if (ctrlKeyEnter && window->KeyDown(VK_RETURN)) {
        ctrlKeyEnter = false;
        audio->Play(TRANSITION);
        Sleep(500); //Delay para haver o som de transição
        Engine::Next<CharSelect>();
    }
    else if (window->KeyUp(VK_RETURN)) {
        ctrlKeyEnter = true;
    }
}

// ------------------------------------------------------------------------------

void Home::Draw()
{
    if (window->KeyDown('Q')) {
        controls->Draw(float(window->CenterX()), float(window->CenterY()), Layer::FRONT);
    }

    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
}

// ------------------------------------------------------------------------------