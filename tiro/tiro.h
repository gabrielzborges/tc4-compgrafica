#ifndef TIRO_H
#define TIRO_H


#include "../circulo/circulo.h"

class Tiro: Circulo {
private:
    /* data */
    float vel, raioPlayer, theta;
    char atirador;
public:
    Tiro(int id, float x, float y, float raioPlayer, float theta, float veloc, char shooter);
    float getX();
    float getY();
    float getR();
    int getid();
    float getVel();
    char getAtirador();
    void setVel(float new_vel);
    void mover(float deltaVel);
    void drawTiro();
    ~Tiro();
};


#endif