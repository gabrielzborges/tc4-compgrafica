#include "./basesInimigas.h"
// #include <GL/glut.h>

BaseInimiga baseNotFound = BaseInimiga(-1.0);

BasesInimigas::BasesInimigas(){
    this->bombardeadas = 0;
}

BaseInimiga* BasesInimigas::getBaseInimigaById(int id){
    for(int i = 0; i < this->lista.size(); i++){
        if(this->lista[i].getId() == id){
            return &this->lista[i];
        }
    }
    return &baseNotFound;
}

void BasesInimigas::setInitConditions(){
    this->bombardeadas = 0;
}

void BasesInimigas::addBaseInimiga(int id){
    BaseInimiga base = BaseInimiga(id);
    this->lista.push_back(base);
}

int BasesInimigas::numBasesBombardeadas(){
    return this->bombardeadas;
}

int BasesInimigas::numBasesVivas(){
    return (this->lista.size() - this->bombardeadas);
}

void BasesInimigas::incrementNumBombardeadas(){
    this->bombardeadas += 1;
}

BasesInimigas::~BasesInimigas(){

}