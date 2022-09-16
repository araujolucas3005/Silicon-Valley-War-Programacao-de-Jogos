/**********************************************************************************
// Animation (Arquivo de Cabe�alho)
//
// Cria��o:     28 Set 2011
// Atualiza��o: 27 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Classe para animar sequ�ncias em folha de sprites
//
**********************************************************************************/

#ifndef _PROGJOGOS_ANIMATION_H_
#define _PROGJOGOS_ANIMATION_H_

// ---------------------------------------------------------------------------------

#include "Sprite.h"                 // tipo sprite para renderiza��o
#include "TileSet.h"                // folha de sprites da anima��o
#include "Timer.h"                  // tempo entre quadros da anima��o
#include "Types.h"                  // tipos espec�ficos da engine

// ---------------------------------------------------------------------------------

class Animation
{
private:
    uint  iniFrame;                 // quadro inicial da seq��ncia
    uint  endFrame;                 // quadro final da seq��ncia
    bool  animLoop;                 // anima��o em loop infinito
    float animDelay;                // espa�o de tempo entre quadros (em segundos)
    Timer timer;                    // medidor de tempo entre quadros da anima��o
    TileSet* tileSet;              // ponteiro para folha de sprites da anima��o
    SpriteData sprite;              // sprite a ser desenhado

public:
    uint  frame;                    // quadro atual da anima��o    

    // construtor
    Animation(TileSet* tiles, float delay, bool repeat);

    // desenha o quadro atual da anima��o
    void Draw(float x, float y, float z = Layer::MIDDLE);

    // desenha um quadro da folha de sprites
    void Draw(uint animFrame, float x, float y, float z = Layer::MIDDLE);

    bool Inactive();                // verifica se a anima��o j� encerrou
    void NextFrame();               // passa para o pr�ximo frame da anima��o
    void Restart();                 // reinicia a animac�o (pelo primeiro frame da seq��ncia)
};

// ---------------------------------------------------------------------------------
// fun��es membro inline

// desenha quadro atual da anima��o
inline void Animation::Draw(float x, float y, float z)
{
    Draw(frame, x, y, z);
}

// verifica se a anima��o j� encerrou
inline bool Animation::Inactive()
{
    return !animLoop && (frame > endFrame || (frame == endFrame && timer.Elapsed(animDelay)));
}

// reinicia a animac�o (pelo primeiro frame da sequencia)
inline void Animation::Restart()
{
    frame = 0; timer.Start();
}

// ---------------------------------------------------------------------------------

#endif