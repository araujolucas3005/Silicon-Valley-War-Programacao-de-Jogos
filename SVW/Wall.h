/**********************************************************************************
// Pivot (Arquivo de Cabe�alho)
//
// Cria��o:     01 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Ponto de mudan�a de dire��o para o jogador e fantasmas
//
**********************************************************************************/

#ifndef _SVW_WALL_H_
#define _SVW_WALL_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                          // tipos espec�ficos da engine
#include "Object.h"                         // interface de Object

// ---------------------------------------------------------------------------------

class Wall : public Object
{
public:
    Wall(float x1, float y1, float x2, float y2);  // construtor
    ~Wall();                               // destrutor

    void Update() {};                       // atualiza��o
    void Draw() {};                         // desenho

    void OnCollision(Object* obj);
};

// ---------------------------------------------------------------------------------

#endif