/**********************************************************************************
// Food (Arquivo de Cabeçalho)
// 
// Criação:     03 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Comida do SVW
//
**********************************************************************************/

#ifndef _SVW_FOOD_H_
#define _SVW_FOOD_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                      // tipos específicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites

// ---------------------------------------------------------------------------------

enum FOODTYPE { MONEY, IDEA };

class Food : public Object
{
private:
    Sprite * sprite = nullptr;          // sprite da comida

public:
    Food(FOODTYPE, float, float);       // construtor
    ~Food();                            // destrutor
    FOODTYPE foodType;

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Food::Draw()
{ sprite->Draw(x, y, z); }

// ---------------------------------------------------------------------------------

#endif