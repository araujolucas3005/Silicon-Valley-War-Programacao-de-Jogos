/**********************************************************************************
// Animation (C�digo Fonte)
//
// Cria��o:     28 Set 2011
// Atualiza��o: 31 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Classe para animar sequ�ncias em folha de sprites
//
**********************************************************************************/

#include "Engine.h"
#include "Animation.h"
#include "Renderer.h"

// ---------------------------------------------------------------------------------

Animation::Animation(TileSet* tiles, float delay, bool repeat) :
    tileSet(tiles),
    animDelay(delay),
    animLoop(repeat)
{
    // sempre inicia a anima��o pelo primeiro quadro
    frame = iniFrame = 0;

    // o �ltimo quadro � sempre um a menos que o n�mero de quadros
    endFrame = tileSet->Size() - 1;

    // configura sprite
    sprite.scale = 1.0f;
    sprite.rotation = 0.0f;
    sprite.width = tileSet->TileWidth();
    sprite.height = tileSet->TileHeight();
    sprite.texSize.x = float(tileSet->TileWidth()) / tileSet->Width();
    sprite.texSize.y = float(tileSet->TileHeight()) / tileSet->Height();
    sprite.texture = tileSet->View();

    // anima��o iniciada (come�a a contar o tempo)
    timer.Start();
}

// ---------------------------------------------------------------------------------

void Animation::NextFrame()
{
    // passa para o pr�ximo quadro ap�s espa�o de tempo estipulado em animDelay
    if (timer.Elapsed(animDelay))
    {
        frame++;

        // se chegou ao fim da anima��o
        if (frame > endFrame)
        {
            // se a anima��o estiver em loop
            if (animLoop)
            {
                // volta ao primeiro quadro 
                frame = 0;
                timer.Start();
            }
            else
            {
                // fica no �ltimo quadro
                frame = endFrame;
            }
        }
        else
        {
            // come�a a contar o tempo do novo frame
            timer.Start();
        }
    }
}

// ---------------------------------------------------------------------------------

void Animation::Draw(uint animFrame, float x, float y, float z)
{
    // configura dados b�sicos
    sprite.x = x;
    sprite.y = y;
    sprite.depth = z;

    // configura coordenadas da textura do sprite
    sprite.texCoord.x = (animFrame % tileSet->Columns()) * sprite.texSize.x;
    sprite.texCoord.y = (animFrame / tileSet->Columns()) * sprite.texSize.y;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(&sprite);
}

// --------------------------------------------------------------------------------