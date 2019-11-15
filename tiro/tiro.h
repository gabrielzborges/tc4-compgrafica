#ifndef TIRO_H
#define TIRO_H


#include "../circulo/circulo.h"

class Tiro: Circulo {
private:
    /* data */
    float vel, raioPlayer, theta;
public:
    Tiro(int id, float x, float y, float raioPlayer, float theta, float veloc);
    float getX();
    float getY();
    float getR();
    int getid();
    float getVel();
    void setVel(float new_vel);
    void mover(float deltaVel);
    void drawTiro();
    ~Tiro();
};


#endif