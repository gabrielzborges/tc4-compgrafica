#include "./InimigoVoador.h"
#include <math.h>

InimigoVoador::InimigoVoador(int id, float raio, float vel, float velTiro, float freqTiro) : Aviao() {
    this->id = id;
    this->raio = raio;
    this->vel = vel;
    this->velTiro = velTiro;
    this->freqTiro = freqTiro;
}

int InimigoVoador::getId(){
    return this->id;
}

float InimigoVoador::getRaio(){
    return this->raio;
}

float InimigoVoador::getVel(){
    return this->vel;
}

float InimigoVoador::getVelTiro(){
    return this->velTiro;
}

float InimigoVoador::getFreqTiro(){
    return this->freqTiro;
}

float InimigoVoador::getThetaMyPlane(){
    return this->getThetaPlane();
}

void InimigoVoador::setThetaMyHelice(float theta){
    this->setThetaHelice(theta);
}

void InimigoVoador::setThetaMyCanhao(float theta){
    this->setThetaCanhao(theta);
}

void InimigoVoador::desenhaInimigoVoador(float x, float y){
    this->desenhaAviao(x, y, this->getRaio(), 'i');
}

void InimigoVoador::rotateMyHelice(float deltaTempoIdle, float vel_inimigo){
    float velAjustada = vel_inimigo * deltaTempoIdle;
    float velX = velAjustada * cos(this->getThetaMyPlane() * M_PI/180);
    float velY = velAjustada * sin(this->getThetaMyPlane() * M_PI/180);
    this->rotateHelice(sqrt(pow(velX, 2) + pow(velY, 2)), this->getRaio());
}

void InimigoVoador::moverAleatoriamente(){}

InimigoVoador::~InimigoVoador(){

}