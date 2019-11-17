#ifndef INIMIGOSVOADORES_H
#define INIMIGOSVOADORES_H

#include "../InimigoVoador/InimigoVoador.h"
// #include "../tiros/tiros.h"
#include <vector>

class InimigosVoadores {
    private:
        std::vector<InimigoVoador> lista;
        float vel, velTiro, freqTiro, tempoControleTiro;

    public:
        InimigosVoadores();
        float getVel();
        float getVelTiro();
        float getFreqTiro();
        void setVel(float v);
        void setVelTiro(float vTiro);
        void setFreqTiro(float fTiro);
        void initThetaHelices();
        void initThetaCanhao();
        void initThetaPlane();
        void setInitConditions();
        InimigoVoador* getInimigoVoadorById(int id);
        void addInimigoVoador(int id, float raio, float vel, float velTiro, float freqTiro);
        bool atirar(float timeNow);
        void virarInimigos(float deltaTempoIdle);
        void moverInimigos(float deltaTempoIdle);
        void moverHelicesInimigos(float deltaTempoIdle);
        ~InimigosVoadores();
};

#endif