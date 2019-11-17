#ifndef INIMIGOVOADOR_H
#define INIMIGOVOADOR_H

#include "../aviao/aviao.h"
// #include "../circulo/circulo.h"

class InimigoVoador: Aviao {
private:
    int id;
    float raio, vel, velTiro, freqTiro;

public:
    InimigoVoador(int id, float raio, float vel, float velTiro, float freqTiro);
    int getId();
    float getRaio();
    float getVel();
    float getVelTiro();
    float getFreqTiro();
    float getThetaMyPlane();
    void setThetaMyHelice(float theta);
    void setThetaMyCanhao(float theta);
    void desenhaInimigoVoador(float x, float y);
    void rotateMyHelice(float deltaTempoIdle, float vel_inimigo);
    void moverAleatoriamente();
    ~InimigoVoador();
};

#endif