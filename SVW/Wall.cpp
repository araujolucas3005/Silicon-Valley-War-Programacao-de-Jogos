/**********************************************************************************
// Pivot (Código Fonte)
//
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Ponto de mudança de direção para o jogador e fantasmas
//
**********************************************************************************/

#include "SVW.h"
#include "Wall.h"

// ---------------------------------------------------------------------------------

Wall::Wall(float x1, float y1, float x2, float y2)
{
    OutputDebugString((std::to_string(x1) + ":" + std::to_string(y2) + "\n").c_str());
    BBox(new Rect(x1, y1, x2, y2));
    type = WALL;
}

// ---------------------------------------------------------------------------------

Wall::~Wall()
{
}

void Wall::OnCollision(Object* obj) {
    OutputDebugString("Test");
}

// ---------------------------------------------------------------------------------

