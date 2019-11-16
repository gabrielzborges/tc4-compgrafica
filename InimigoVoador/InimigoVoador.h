#ifndef INIMIGOVOADOR_H
#define INIMIGOVOADOR_H

#include "../aviao/aviao.h"
#include "../circulo/circulo.h"

class InimigoVoador: Aviao {
private:
    int id;
    float vel, velTiro, freqTiro;

public:
    InimigoVoador(int id, float vel, float velTiro, float freqTiro);
    int getId();
    float getVel();
    float getVelTiro();
    float getFreqTiro();
    float getThetaMyPlane();
    void desenhaInimigoVoador(float x, float y, float raio);
    void moverAleatoriamente();
    ~InimigoVoador();
};

#endif