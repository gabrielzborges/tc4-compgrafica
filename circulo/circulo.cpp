#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "circulo.h"
#include <string>


Circulo::Circulo(float r, float x, float y, float num_segs, std::string color, int id) {
    this->fill = std::string(color);
    this->raio = r;
    this->x = x;
    this->y = y;
    this->segmentos = num_segs;
    this->id = id;
    this->x_init = x;
    this->y_init = y;
}

float Circulo::getRaio() {
    return this->raio;
}

float Circulo::getXCoord() {
    return this->x;
}

float Circulo::getYCoord() {
    return this->y;
}

float Circulo::getInitXCoord(){
    return this->x_init;
}

float Circulo::getInitYCoord(){
    return this->y_init;
}

std::string Circulo::getFill(){
    return this->fill;
}

int Circulo::getNumeroSegmentos() {
    return this->segmentos;
}

int Circulo::getId() {
    return this->id;
}

void Circulo::setCoords(float novo_x, float novo_y){
    this->x = novo_x;
    this->y = novo_y;
}

void Circulo::setRaio(float novoR){
    this->raio = novoR;
}

void Circulo::drawCirculo() {
    if(this->fill.compare("green") == 0){
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_LINES);
    } else if(this->fill.compare("blue") == 0){
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
    } else if(this->fill.compare("red") == 0){
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
    } else if(this->fill.compare("orange") == 0){
        glColor3f(1.0, 0.5, 0.0);
        glBegin(GL_POLYGON);
    } else if(this->fill.compare("tiro") == 0){
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
    } else if(this->fill.compare("bomba") == 0){
        glColor3f(0.5, 0.35, 0.05);
        glBegin(GL_POLYGON);
    }
    
        for( int n = 0; n <= this->getNumeroSegmentos(); ++n ) {
            float angulo = 2.0f * 3.1415926f * (float)n / (float)this->getNumeroSegmentos();
            glVertex2f(this->getXCoord() +  sin(angulo) * this->getRaio(), this->getYCoord() + cos(angulo) * this->getRaio());
        }
    glEnd();
}

bool Circulo::colideComigo(float x, float y, float raioDoOutro) {
    //calcular distancia (quadrada pois nao precisa tirar a raiz se comparar com a soma dos raios ao quadrado) dos centros
    float distCentros = (this->getXCoord() - x) * (this->getXCoord() - x) + (this->getYCoord() - y) * (this->getYCoord() - y);

    //Somar o raio dos dois e verificar com a distancia dos centros
    float somaRaios = (this->getRaio() + raioDoOutro) * (this->getRaio() + raioDoOutro);

    return somaRaios >= distCentros;
}

bool Circulo::pertenceAoMeuDisco(float x, float y){
    //calcular distancia (quadrada pois nao precisa tirar a raiz se comparar com o raio ao quadrado) do centro ao ponto do mouse
    float distCentroAoMouse = (this->getXCoord() - x) * (this->getXCoord() - x) + (this->getYCoord() - y) * (this->getYCoord() - y);

    //raio da circunferencia pois se a distancia for menor ou igual ao raio entao o mouse esta sobre a circunferencia
    return distCentroAoMouse <= (this->getRaio()*this->getRaio());
}

void Circulo::estaTotalmenteDentro(Circulo* c, Aviao* a, std::string direcaoSentido, float delta){
    //calcular distancia  do centro ao aviao
    float distCentroAoJogador = sqrt(pow(this->getXCoord() - c->getXCoord(), 2) + pow(this->getYCoord() - c->getYCoord(), 2));

    if(distCentroAoJogador > (this->getRaio() - c->getRaio())){  //saiu
        if(direcaoSentido.compare("direita") == 0){
            c->moveX(-delta);
        } else if(direcaoSentido.compare("esquerda") == 0){
            c->moveX(delta);
        } else if(direcaoSentido.compare("cima") == 0){
            c->moveY(-delta);
        } else if(direcaoSentido.compare("baixo") == 0){
            c->moveY(delta);
        }
        float x = c->getXCoord() - this->getXCoord();
        float y = c->getYCoord() - this->getYCoord();
        float theta1 = atan2(y, x) * 180/M_PI;
        float theta2 = ((a->getThetaPlane()) - 90);
        float theta3 = (-2 * (theta1 - theta2)) * M_PI/180;

        c->setCoords(
            ((x*cos(theta3)) - (y*sin(theta3))) + this->getXCoord(),
            ((x*sin(theta3)) + (y*cos(theta3))) + this->getYCoord()
        );

    }
}

void Circulo::inimigoEstaTotalmenteDentro(Circulo* c, InimigoVoador* a, std::string direcaoSentido, float delta){
    //calcular distancia  do centro ao aviao
    float distCentroAoJogador = sqrt(pow(this->getXCoord() - c->getXCoord(), 2) + pow(this->getYCoord() - c->getYCoord(), 2));

    if(distCentroAoJogador > (this->getRaio() - c->getRaio())){  //saiu
        if(direcaoSentido.compare("direita") == 0){
            c->moveX(-delta);
        } else if(direcaoSentido.compare("esquerda") == 0){
            c->moveX(delta);
        } else if(direcaoSentido.compare("cima") == 0){
            c->moveY(-delta);
        } else if(direcaoSentido.compare("baixo") == 0){
            c->moveY(delta);
        }
        float x = c->getXCoord() - this->getXCoord();
        float y = c->getYCoord() - this->getYCoord();
        float theta1 = atan2(y, x) * 180/M_PI;
        float theta2 = ((a->getThetaMyPlane()) - 90);
        float theta3 = (-2 * (theta1 - theta2)) * M_PI/180;

        c->setCoords(
            ((x*cos(theta3)) - (y*sin(theta3))) + this->getXCoord(),
            ((x*sin(theta3)) + (y*cos(theta3))) + this->getYCoord()
        );
    }
}

// bool Circulo::baleado(Tiros* tiros){
//     for(Tiro t : tiros->getLista()){
//         if(t.getAtirador() == 'i' && this->colideComigo(t.getX(), t.getY(), t.getR())){
//             return true;
//         }
//     }
//     return false;
// }

void Circulo::moveX(float vx){
    this->x += vx;
}

void Circulo::moveY(float vy){
    this->y += vy;
}

void Circulo::aumentarRaio(float incremento){
    this->raio += incremento;
}

void Circulo::diminRaio(float decremento){
    this->raio -= decremento;
}

Circulo::~Circulo()
{
}