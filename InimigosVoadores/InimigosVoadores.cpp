#include <iostream>
#include <math.h>
#include "./InimigosVoadores.h"

InimigoVoador notFound = InimigoVoador(-1, -1.0, -1.0, -1.0, -1.0);

InimigosVoadores::InimigosVoadores(){
    this->vel = 0.0;
    this->velTiro = 0.0;
    this->freqTiro = 0.0;
}

float InimigosVoadores::getVel(){
    return this->vel;
}

float InimigosVoadores::getVelTiro(){
    return this->velTiro;
}

float InimigosVoadores::getFreqTiro(){
    return this->freqTiro;
}

void InimigosVoadores::setVel(float v){
    this->vel = v;
}
   
void InimigosVoadores::setVelTiro(float vTiro){
    this->velTiro = vTiro;
}

void InimigosVoadores::setFreqTiro(float fTiro){
    this->freqTiro =  fTiro;
}

void InimigosVoadores::initThetaHelices(){
    for(int i = 0; i < this->lista.size(); i++){
        this->lista[i].setThetaMyHelice(0.0);
    }
}

void InimigosVoadores::initThetaCanhao(){
    for(int i = 0; i < this->lista.size(); i++){
        this->lista[i].setThetaMyCanhao(0.0);
    }
}

void InimigosVoadores::initThetaPlane(){
    for(int i = 0; i < this->lista.size(); i++){
        this->lista[i].setThetaMyPlane(0.0);
    }
}

void InimigosVoadores::setInitConditions(){
    for(int i = 0; i < this->lista.size(); i++){
        this->lista[i].setThetaMyHelice(0.0);
        this->lista[i].setThetaMyCanhao(0.0);
        this->lista[i].setThetaMyPlane(0.0);
        this->lista[i].setInitialConditions();
    }
}

InimigoVoador* InimigosVoadores::getInimigoVoadorById(int id){
    for(int i = 0; i < this->lista.size(); i++){
        if(this->lista[i].getId() == id){
            return &this->lista[i];
        }
    }
    return &notFound;
}

void InimigosVoadores::addInimigoVoador(int id, float raio, float vel, float velTiro, float freqTiro){
    InimigoVoador iniVoador = InimigoVoador(id, raio, vel, velTiro, freqTiro);
    this->lista.push_back(iniVoador);
}

void InimigosVoadores::moverHelicesInimigos(float deltaTempoIdle){
    for(int i = 0; i < this->lista.size(); i++){
        this->lista[i].rotateMyHelice(deltaTempoIdle, this->getVel());
    }
}

void InimigosVoadores::virarInimigos(float deltaTempoIdle){
    for(int i = 0; i < this->lista.size(); i++){
        this->lista[i].moverAleatoriamente(deltaTempoIdle);
    }
}

// void InimigosVoadores::moverInimigos(float deltaTempoIdle){
//     float velAjustado = this->vel * deltaTempoIdle;
//     for(int i = 0; i < this->lista.size(); i++){
//         float velX = velAjustado * cos(this->lista[i].getThetaMyPlane() * M_PI/180);
//         // std::cout << "velX: " << velX << std::endl;
//         float velY = velAjustado * sin(this->lista[i].getThetaMyPlane() * M_PI/180);
//         // std::cout << "velY: " << velY << std::endl;
//         if(this->lista[i].getId() == 4){
//             std::cout << "x:" << this->lista[i].getCirculo()->getXCoord() << std::endl;
//         }
//         this->lista[i].getCirculo()->moveX(velX);
//         this->lista[i].getCirculo()->moveY(velY);
//         if(this->lista[i].getId() == 4){
//             std::cout << "x:" << this->lista[i].getCirculo()->getXCoord() << std::endl;
//         }
//         //rotateHelices
//         //moverAleatoriamente isso para girar o aviao
//     }
// }

InimigosVoadores::~InimigosVoadores(){

}