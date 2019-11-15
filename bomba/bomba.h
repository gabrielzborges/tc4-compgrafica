#ifndef BOMBA_H
#define BOMBA_H

#include "../circulo/circulo.h"

class Bomba: Circulo {
private:
    float vel, raio, theta;

public:
    Bomba(int id, float raioPlayer, float theta, float x, float y, float veloc);
    float getX();
    float getY();
    float getR();
    float getInitialR();
    int getid();
    float getVel();
    void setVel(float new_vel);
    void diminuirRaio(float deltaT);
    void mover(float deltaT);
    void drawBomba();
    ~Bomba();
};

#endif