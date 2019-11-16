#include "./InimigoVoador.h"

InimigoVoador::InimigoVoador(int id, float vel, float velTiro, float freqTiro) : Aviao() {
    this->id = id;
    this->vel = vel;
    this->velTiro = velTiro;
    this->freqTiro = freqTiro;
}

int InimigoVoador::getId(){
    return this->id;
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

void InimigoVoador::desenhaInimigoVoador(float x, float y, float raio){
    this->desenhaAviao(x, y, raio, 'i');
}

void InimigoVoador::moverAleatoriamente(){}

InimigoVoador::~InimigoVoador(){

}