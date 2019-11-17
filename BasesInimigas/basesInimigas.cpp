#include "./basesInimigas.h"
// #include <GL/glut.h>

BaseInimiga baseNotFound = BaseInimiga(-1.0);

BasesInimigas::BasesInimigas(){

}

BaseInimiga* BasesInimigas::getBaseInimigaById(int id){
    for(int i = 0; i < this->lista.size(); i++){
        if(this->lista[i].getId() == id){
            return &this->lista[i];
        }
    }
    return &baseNotFound;
}

void BasesInimigas::addBaseInimiga(int id){
    BaseInimiga base = BaseInimiga(id);
    this->lista.push_back(base);
}

int BasesInimigas::numBasesBombardeadas(){
    int res = 0;
    for(int i = 0; i < this->lista.size(); i++){
        if(this->lista[i].estaBombardeada()){
            res++;
        }
    }
    return res;
}

int BasesInimigas::numBasesVivas(){
    return (this->lista.size() - this->numBasesBombardeadas());
}

BasesInimigas::~BasesInimigas(){

}