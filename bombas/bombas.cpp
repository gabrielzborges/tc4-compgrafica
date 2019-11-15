#include "bombas.h"
#include <iostream>
#include <math.h>


int Bombas::nth = -1;

Bombas::Bombas(){

}

int Bombas::getIncrementingNth(){
    this->nth++;
    return this->nth;
}

void Bombas::resetNth(){
    this->nth = -1;
}

void Bombas::addBomba(int id, float x, float y, float raioPlayer, float thetaAviaoMomento, 
                    float veloc){
    Bomba b = Bomba(id, raioPlayer, thetaAviaoMomento, x, y, veloc);
    this->lista.push_back(b);
}

void Bombas::drawBombas(Circulo* arena){
    for(int i = 0; i < lista.size(); i++){
        lista[i].drawBomba();
    }
    this->explodirBombaForaOuTempo(arena);
}

void Bombas::explodirBombaForaOuTempo(Circulo* arena){
    int lista_size = lista.size();
    float distCentroAoTiro = 0.0;
    for(auto it = this->lista.rbegin(); it != this->lista.rend(); ++it){
        distCentroAoTiro = sqrt(pow(arena->getXCoord() - it->getX(), 2) + pow(arena->getYCoord() - it->getY(), 2));
        if(distCentroAoTiro > (arena->getRaio() - it->getR())){//saiu
            std::cout << "Bomba " << it->getid() << " - saiu da arena!" << std::endl;
            auto it_corrigido = it.base();
            this->lista.erase(--it_corrigido);
        } else if(it->getR() <= it->getInitialR()/2.0){
            std::cout << "Bomba " << it->getid() << " - explodiu! Raio inicial: " << it->getInitialR() << "; Raio final: " << it->getR() << std::endl;
            auto it_corrigido = it.base();
            this->lista.erase(--it_corrigido);
        }
    }
}

void Bombas::moverBombas(float deltaVel){
    for(int i = 0; i < this->lista.size(); i++){
        lista[i].mover(deltaVel);
    }
}

void Bombas::limparBombas(){
    this->lista.clear();
}

void Bombas::pararBombas(){
    for(int i = 0; i < this->lista.size(); i++){
        lista[i].setVel(0.0);
    }
}

Bombas::~Bombas(){

}