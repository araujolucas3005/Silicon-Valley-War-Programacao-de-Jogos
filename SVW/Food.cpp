/**********************************************************************************
// Food (Código Fonte)
// 
// Criação:     03 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Comida do SVW
//
**********************************************************************************/

#include "SVW.h"
#include "Food.h"
#include "GameManager.h"

// ---------------------------------------------------------------------------------

Food::Food(FOODTYPE ft, float x, float y)
{
    BBox(new Rect(-8, -8, 8, 8));
    foodType = ft;
    type = FOOD;

    if (ft == MONEY)
        sprite = new Sprite("Resources/MoneyFood.png");
    else
        sprite = new Sprite("Resources/IdeaFood.png");

    MoveTo(x, y);

    timer = new Timer();
    auxTimer = new Timer();

    timer->Start();
    auxTimer->Start();
}

// ---------------------------------------------------------------------------------

Food::~Food()
{
    delete sprite;
    delete timer;
    delete auxTimer;
}

// ---------------------------------------------------------------------------------

void Food::Update()
{
    if (timer->Elapsed() > 20) {
        GameManager::foodNow--;

        GameManager::currLevel->scene->Delete(this, STATIC);
    }
}

void Food::Draw()
{
    float auxElapsed = auxTimer->Elapsed();

    if (timer->Elapsed() > 15 && auxElapsed > 0.5f) {
        if (auxElapsed > 1.0f)
            auxTimer->Start();
        sprite->Draw(-50, -50, z);
    }
    else 
        sprite->Draw(x, y, z);
}


// ---------------------------------------------------------------------------------
