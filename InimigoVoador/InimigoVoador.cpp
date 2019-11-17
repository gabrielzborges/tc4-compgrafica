#include "./InimigoVoador.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

InimigoVoador::InimigoVoador(int id, float raio, float vel, float velTiro, float freqTiro) : Aviao() {
    this->id = id;
    this->raio = raio;
    this->vel = vel;
    this->velTiro = velTiro;
    this->freqTiro = freqTiro;
    this->estaVirando = false;
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

void InimigoVoador::moverAleatoriamente(float deltaTempoIdle){
    if(this->estaVirando){
        if(this->sentidoVirar == 1){
            this->rotatePlane((M_PI/2)*(deltaTempoIdle));
            if(this->getThetaPlane() >= this->thetaAlvo){
                this->setThetaPlane(this->thetaAlvo);
                this->estaVirando = false;
            }
        } else {
            this->rotatePlane(-(M_PI/2)*(deltaTempoIdle));
            if(this->getThetaPlane() <= this->thetaAlvo){
                this->setThetaPlane(this->thetaAlvo);
                this->estaVirando = false;
            }
        }
    } else {
        // srand (time(NULL));
        int targetAngle = rand() % 360 + 1;
        this->sentidoVirar = rand() % 2;
        if(this->sentidoVirar == 1){
            this->thetaAlvo = this->getThetaPlane() + targetAngle;
        } else {
            this->thetaAlvo = this->getThetaPlane() - targetAngle;
        }
        this->estaVirando = true;
    }
}

InimigoVoador::~InimigoVoador(){

}