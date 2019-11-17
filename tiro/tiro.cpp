#include "tiro.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>

Tiro::Tiro(int id, float x, float y, float raioPlayer, float theta, 
            float veloc, char shooter) : Circulo(raioPlayer*0.1, x, y, 100, "tiro", id){
    this->raioPlayer = raioPlayer;
    this->theta = theta;
    this->vel = veloc;
    this->atirador = shooter;
}

float Tiro::getX(){
    return this->getXCoord();
}

float Tiro::getY(){
    return this->getYCoord();
}
float Tiro::getR(){
    return this->getRaio();
}

int Tiro::getid(){
    return this->getId();
}

float Tiro::getVel(){
    return this->vel;
}

char Tiro::getAtirador(){
    return this->atirador;
}

void Tiro::setVel(float new_vel){
    this->vel = new_vel;
}

void Tiro::mover(float deltaVel){
    float x_tiro = cos(this->theta*M_PI/180)*deltaVel;
    float y_tiro = sin(this->theta*M_PI/180)*deltaVel;

    this->moveX(x_tiro * this->vel);
    this->moveY(y_tiro * this->vel);
}

void Tiro::drawTiro(){
    this->drawCirculo();
}

Tiro::~Tiro(){
}
