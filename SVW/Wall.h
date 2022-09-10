/**********************************************************************************
// Pivot (Arquivo de Cabeçalho)
//
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Ponto de mudança de direção para o jogador e fantasmas
//
**********************************************************************************/

#ifndef _SVW_WALL_H_
#define _SVW_WALL_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                          // tipos específicos da engine
#include "Object.h"                         // interface de Object

// ---------------------------------------------------------------------------------

class Wall : public Object
{
public:
    Wall(float x1, float y1, float x2, float y2);  // construtor
    ~Wall();                               // destrutor

    void Update() {};                       // atualização
    void Draw() {};                         // desenho

    void OnCollision(Object* obj);
};

// ---------------------------------------------------------------------------------

#endif