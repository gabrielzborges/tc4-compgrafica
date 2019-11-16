#include "circulos.h"
#include <iostream>
#include <string>

Circulos::Circulos(/* args */){

}

std::vector<Circulo> Circulos::getLista(){
    return this->lista;
}

Circulo* Circulos::getLastAdded(){
    return &this->lista[this->lista.size()];
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
        if(c.getFill().compare("red") == 0 && c.colideComigo(x, y, raio)){
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