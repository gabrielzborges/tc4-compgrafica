#ifndef INIMIGOSVOADORES_H
#define INIMIGOSVOADORES_H

#include "../InimigoVoador/InimigoVoador.h"
#include <vector>

class InimigosVoadores {
    private:
        std::vector<InimigoVoador> lista;
        float vel, velTiro, freqTiro;

    public:
        InimigosVoadores();
        void setVel(float v);
        void setVelTiro(float vTiro);
        void setFreqTiro(float fTiro);
        InimigoVoador* getInimigoVoadorById(int id);
        void addInimigoVoador(int id, float vel, float velTiro, float freqTiro, Circulo* c);
        void moverInimigos(float deltaTempoIdle);
        ~InimigosVoadores();
};

#endif