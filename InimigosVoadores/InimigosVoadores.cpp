#include <iostream>
#include <math.h>
#include "./InimigosVoadores.h"

Circulo notFoundCirculo = Circulo(-1.0, -1.0, -1.0, -1.0, "none", -1);
InimigoVoador notFound = InimigoVoador(-1, -1.0, -1.0, -1.0, &notFoundCirculo);

InimigosVoadores::InimigosVoadores(){
    this->vel = 0.0;
    this->velTiro = 0.0;
    this->freqTiro = 0.0;
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

InimigoVoador* InimigosVoadores::getInimigoVoadorById(int id){
    for(int i = 0; i < this->lista.size(); i++){
        if(this->lista[i].getId() == id){
            return &this->lista[i];
        }
    }
    return &notFound;
}

void InimigosVoadores::addInimigoVoador(int id, float vel, float velTiro, float freqTiro, Circulo* c){
    InimigoVoador iniVoador = InimigoVoador(id, vel, velTiro, freqTiro, c);
    this->lista.push_back(iniVoador);
}

void InimigosVoadores::moverInimigos(float deltaTempoIdle){
    float velAjustado = this->vel * deltaTempoIdle;
    for(int i = 0; i < this->lista.size(); i++){
        float velX = velAjustado * cos(this->lista[i].getThetaMyPlane() * M_PI/180);
        // std::cout << "velX: " << velX << std::endl;
        float velY = velAjustado * sin(this->lista[i].getThetaMyPlane() * M_PI/180);
        // std::cout << "velY: " << velY << std::endl;
        if(this->lista[i].getId() == 4){
            std::cout << "x:" << this->lista[i].getCirculo()->getXCoord() << std::endl;
        }
        this->lista[i].getCirculo()->moveX(velX);
        this->lista[i].getCirculo()->moveY(velY);
        if(this->lista[i].getId() == 4){
            std::cout << "x:" << this->lista[i].getCirculo()->getXCoord() << std::endl;
        }
        //rotateHelices
        //moverAleatoriamente isso para girar o aviao
    }
}

InimigosVoadores::~InimigosVoadores(){

}