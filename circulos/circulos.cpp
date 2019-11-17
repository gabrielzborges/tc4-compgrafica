#include "circulos.h"
#include <iostream>
#include <math.h>
#include <string>

Circulos::Circulos(/* args */){

}

std::vector<Circulo> Circulos::getLista(){
    return this->lista;
}

Circulo* Circulos::getLastAdded(){
    return &this->lista[this->lista.size()];
}

void Circulos::setInitalPositions(){
    for(int i = 0; i < this->lista.size(); i++){
        this->lista[i].setCoords(this->lista[i].getInitXCoord(), this->lista[i].getInitYCoord());
        this->lista[i].setEstaMorto(false);
    }
}

void Circulos::addCirculo(float r, float x, float y, float num_segs, std::string color, int id) {
    Circulo c = Circulo(r, x, y, num_segs, color, id);
    this->lista.push_back(c);
}

void Circulos::drawTodosCirculos() {
    for(Circulo c : this->lista){
        c.drawCirculo();
    }
}

bool Circulos::colideComAlgumExistente(float x, float y, float raioDoModelo){
    for(Circulo c : this->lista){
        if(c.colideComigo(x, y, raioDoModelo)){
            return true;
        }
    }
    return false;
}

bool Circulos::colideComInimigo(float x, float y, float raio){
    for(Circulo c : this->lista){
        if(!c.estaMorto() && c.getFill().compare("red") == 0 && c.colideComigo(x, y, raio)){
            return true;
        }
    }
    return false;
}

int Circulos::estaSobreQual(float x, float y){
    for(int pos = 0; pos < this->lista.size(); pos++){
        if(this->lista[pos].pertenceAoMeuDisco(x, y)){
            return pos;
        }
    }
    return -1;
}

void Circulos::arrastaCirculoPorPosicao(float novo_x, float novo_y, int pos){
    this->lista[pos].setCoords(novo_x, novo_y);
}

void Circulos::moverInimigos(Circulo* arena, float deltaTempoIdle, InimigosVoadores inimigos){
    float velAjustada = inimigos.getVel() * deltaTempoIdle;
    for(int i = 0; i < this->lista.size(); i++){
        if(!this->lista[i].estaMorto() && this->lista[i].getFill().compare("red") == 0){
            InimigoVoador* aux = inimigos.getInimigoVoadorById(this->lista[i].getId());
            float velX = velAjustada * cos(aux->getThetaMyPlane() * M_PI/180);
            float velY = velAjustada * sin(aux->getThetaMyPlane() * M_PI/180);
            this->lista[i].moveX(velX);
            arena->inimigoEstaTotalmenteDentro(&this->lista[i], aux,"direita", velX);
            this->lista[i].moveY(velY);
            arena->inimigoEstaTotalmenteDentro(&this->lista[i], aux, "cima", velY);
        }
    }
}

void Circulos::teletransporteInimigos(Circulo* arena, InimigosVoadores inimigos, float deltaTempoIdle){
    float velAjustada = inimigos.getVel() * deltaTempoIdle;
    for(int i = 0; i < this->lista.size();  i++){
        if(this->lista[i].getFill().compare("red") == 0){
            // Circulo* c_aux = &this->lista[i];
            InimigoVoador* aux = inimigos.getInimigoVoadorById(this->lista[i].getId());
            float velX = velAjustada * cos(aux->getThetaMyPlane() * M_PI/180);
            float velY = velAjustada * sin(aux->getThetaMyPlane() * M_PI/180);
            arena->inimigoEstaTotalmenteDentro(&this->lista[i], aux, "cima", velY);
            // arena->inimigoEstaTotalmenteDentro(&this->lista[i], aux,"direita", velX);
        }
    }
}

void Circulos::matarCirculoById(int id, float x, float y){
    for(int i = 0; i < this->lista.size(); i++){
        if(this->lista[i].getId() == id && this->lista[i].getXCoord() == x 
            && this->lista[i].getYCoord() == y 
            && this->lista[i].getFill().compare("red") == 0) {
                this->lista[i].setEstaMorto(true);
        }
    }
}

Circulo* Circulos::getCirculoById(int id){
    for(int i = 0; i < this->lista.size(); i++){
        if(this->lista[i].getId() == id){
            return &this->lista[i];
        }
    }
}

Circulo* Circulos::getCirculoByColor(std::string color){
    for(int i = 0; i < this->lista.size(); i++){
        if(this->lista[i].getFill().compare(color) == 0){
            return &this->lista[i];
        }
    }
}

Circulos::~Circulos()
{
}