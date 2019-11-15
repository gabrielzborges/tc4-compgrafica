#include "bomba.h"
#include <GL/glut.h>
#include <math.h>
#include <iostream>

Bomba::Bomba(int id, float raioPlayer, float theta, float x, float y, float veloc) : 
            Circulo(0.3 *raioPlayer, x, y, 100, "bomba", id){
    this->raio = 0.3 *raioPlayer;
    this->vel = veloc;
    this->theta = theta;
}

float Bomba::getX(){
    return this->getXCoord();
}

float Bomba::getY(){
    return this->getYCoord();
}

float Bomba::getR(){
    return this->getRaio();
}

float Bomba::getInitialR(){
    return this->raio;
}

int Bomba::getid(){
    return this->getId();
}

float Bomba::getVel(){
    return this->vel;
}

void Bomba::setVel(float new_vel){
    this->vel = new_vel;
}

//diminui o raio ate a metade em quatro segundos
void Bomba::diminuirRaio(float deltaT){
    float decrementLenght = this->raio / 4.0;
    float decrementVel = decrementLenght * deltaT/2;
    this->diminRaio(decrementVel);
}

void Bomba::mover(float deltaT){
    float x_bomba = cos(this->theta * M_PI/180) * deltaT;
    float y_bomba = sin(this->theta * M_PI/180) * deltaT;

    this->moveX(this->vel * x_bomba);
    this->moveY(this->vel * y_bomba);

    this->diminuirRaio(deltaT);
}

void Bomba::drawBomba(){
    this->drawCirculo();
}

Bomba::~Bomba(){

}