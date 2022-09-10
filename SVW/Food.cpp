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
}

// ---------------------------------------------------------------------------------

Food::~Food()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Food::Update()
{
}

// ---------------------------------------------------------------------------------
