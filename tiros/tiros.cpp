#include "tiros.h"
#include <math.h>
#include <iostream>

int Tiros::nth = -1;

Tiros::Tiros(){

}

int Tiros::getIncrementingNth(){
    this->nth++;
    return this->nth;
}

std::vector<Tiro> Tiros::getLista(){
    return this->lista;
}

void Tiros::resetNth(){
    this->nth = -1;
}

void Tiros::addTiro(int id, float x, float y, float raioPlayer, float thetaAviaoMomento, 
                    float thetaCanhaoMomento, float veloc, char quem){
    float x_tiro = x + raioPlayer*cos(thetaAviaoMomento*M_PI/180) + raioPlayer/2*cos((thetaAviaoMomento + thetaCanhaoMomento)*M_PI/180);
    float y_tiro = y + raioPlayer*sin(thetaAviaoMomento*M_PI/180) + raioPlayer/2*sin((thetaAviaoMomento + thetaCanhaoMomento)*M_PI/180);
    Tiro t = Tiro(id, x_tiro, y_tiro, raioPlayer, thetaAviaoMomento + thetaCanhaoMomento, veloc, quem);
    this->lista.push_back(t);
}

void Tiros::drawTiros(Circulo* arena){
    for(int i = 0; i < lista.size(); i++){
        lista[i].drawTiro();
    }
    this->deletarTiroForaArena(arena);
}

void Tiros::deletarTiroForaArena(Circulo* arena){
    int lista_size = lista.size();
    float distCentroAoTiro = 0.0;
    for(auto it = this->lista.rbegin(); it != this->lista.rend(); ++it){
        distCentroAoTiro = sqrt(pow(arena->getXCoord() - it->getX(), 2) + pow(arena->getYCoord() - it->getY(), 2));
        if(distCentroAoTiro > (arena->getRaio() - it->getR())){//saiu
            auto it_corrigido = it.base();
            this->lista.erase(--it_corrigido);
        }
    }
}

void Tiros::moverTiros(float deltaVel){
    for(int i = 0; i < this->lista.size(); i++){
        lista[i].mover(deltaVel);
    }
}

bool Tiros::playerBaleado(Circulo* player){
    for(int i = 0; i < this->lista.size(); i++){
        if(this->lista[i].getAtirador() == 'i' 
            && player->colideComigo(this->lista[i].getX(), this->lista[i].getY(), 
                                        this->lista[i].getR())){
            return true;
        }
    }
    return false;
}

void Tiros::limparTiros(){
    this->lista.clear();
}

void Tiros::pararTiros(){
    for(int i = 0; i < this->lista.size(); i++){
        lista[i].setVel(0.0);
    }
}

Tiros::~Tiros(){

}