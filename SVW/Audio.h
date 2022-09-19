/**********************************************************************************
// Audio (Arquivo de Cabe�alho)
// 
// Cria��o:     14 Out 2011
// Atualiza��o: 11 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Classe para reproduzir �udio
//
**********************************************************************************/

#ifndef _PROGJOGOS_AUDIO_H_
#define _PROGJOGOS_AUDIO_H_

// ---------------------------------------------------------------------------------

#include "Sound.h"                              // guarda o som no formato WAVE
#include "Types.h"                              // tipos espec�ficos da engine
#include <XAudio2.h>                            // XAudio2 API
#include <unordered_map>                        // tabela de dispers�o
#include <string>                               // tipo string da STL
using std::unordered_map;
using std::string;

// ---------------------------------------------------------------------------------

class Audio
{
private:
    IXAudio2* audioEngine;                      // sistema de �udio (engine)
    IXAudio2MasteringVoice* masterVoice;        // dispositivo principal de �udio
    unordered_map<uint, Sound*> sounds;         // cole��o de sons

public:
    Audio();                                    // construtor
    ~Audio();                                   // destrutor

    void Add(uint id, string filename);         // adiciona um som <id, filename>
    void Play(uint id);                         // reproduz som atrav�s do seu id
}; 

// ---------------------------------------------------------------------------------

#endif