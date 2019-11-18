#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "aviao.h"


float Aviao::getThetaCanhao(){
    return this->thetaCanhao;
}

float Aviao::getThetaPlane(){
    return this->thetaPlane;
}

bool Aviao::getPerdeu(){
    return this->perdeu;
}

bool Aviao::getGanhou(){
    return this->ganhou;
}

void Aviao::setThetaPlane(float theta){
    this->thetaPlane = theta * 180/M_PI;
}

void Aviao::setThetaCanhao(float theta){
    this->thetaCanhao = theta * 180/M_PI;
}

void Aviao::setThetaHelice(float theta){
    this->thetaHelice = theta * 180/M_PI;
}

void Aviao::setPerdeu(bool estado){
    this->perdeu = estado;
}

void Aviao::setGanhou(bool estado){
    this->ganhou = estado;
}

void Aviao::rotatePlane(float theta){
    this->thetaPlane += 180*theta/M_PI;
}
void Aviao::rotateCanhao(float theta){
    float ang = 180*theta/M_PI;
    if(theta > 0 && this->thetaCanhao < 45){
        this->thetaCanhao += ang;
        if(this->thetaCanhao > 45){
            this->thetaCanhao = 45;
        }
    } else if(ang < 0 && this->thetaCanhao > -45){
        this->thetaCanhao += ang;
        if(this->thetaCanhao < -45){
            this->thetaCanhao = -45;
        }
    }
}

void Aviao::rotateHelice(float delta, float raioMaior){
    // this->gThetaWheel -= delta*360/(2*3.14*radiusWheel);
    this->thetaHelice += delta*180/(M_PI*0.1*raioMaior);
}

void Aviao::desenhaFuselagem(float raioMaior, float raioMenor, char tipo){
    glPushMatrix();
    if(tipo == 'j'){
        glColor3f(0.0, 0.7, 0.0);
    } else {
        glColor3f(1.0, 0.0, 0.0);
    }
    glBegin(GL_POLYGON);
        for( int n = 0; n <= 360; ++n ) {
            float angulo = 2.0f * M_PI * (float)n / (float)360;
            glVertex2f(sin(angulo) * raioMaior, - cos(angulo) * raioMenor);
        }
    glEnd();
    glPopMatrix();
}

void Aviao::desenhaAsa(float raioMaior){
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3d(raioMaior*0.15, 0.0, 0.0);
        glVertex3d(-raioMaior*0.2, 0.0, 0.0);
        glVertex3d(raioMaior*0.15, raioMaior, 0.0);
        glVertex3d(-raioMaior*0.2, raioMaior, 0.0);

        glVertex3d(raioMaior*0.15, 0.0, 0.0);
        glVertex3d(-raioMaior*0.2, 0.0, 0.0);
        glVertex3d(raioMaior*0.15, -raioMaior, 0.0);
        glVertex3d(-raioMaior*0.2, -raioMaior, 0.0);
    glEnd();
}

void Aviao::desenhaCauda(float raioMaior){
    glPushMatrix();
    glTranslatef(-raioMaior, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f (0, (0.05 * raioMaior), 0.0);   
		glVertex3f (0, -(0.05 * raioMaior), 0.0);
		glVertex3f (raioMaior/2, -(0.05 * raioMaior), 0.0);
		glVertex3f (raioMaior/2, (0.05 * raioMaior), 0.0);
    glEnd();
    glPopMatrix();
}

void Aviao::desenhaCabine(float raioMaior, float raioMenor){
    glPushMatrix();
    glTranslatef(raioMaior, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        for( int n = 0; n <= 100; ++n ) {
            float angulo = 2.0f * 3.1415926f * (float)n / (float)100;
            glVertex2f(sin(angulo) * raioMaior, -cos(angulo) * raioMenor);
        }
    glEnd();
    glPopMatrix();
}

void Aviao::desenhaCanhao(float raioMaior){
    glPushMatrix();
    glTranslatef(raioMaior, 0.0, 0.0);
    glRotatef(this->thetaCanhao, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f (0, (0.05 * raioMaior), 0.0);   
		glVertex3f (0, -(0.05 * raioMaior), 0.0);
		glVertex3f (raioMaior/2, -(0.05 * raioMaior), 0.0);
		glVertex3f (raioMaior/2, (0.05 * raioMaior), 0.0);
    glEnd();
    glPopMatrix();
}

void Aviao::desenhaHelice(float raioMaior){
    //ESQUERDA
    glPushMatrix();
    glTranslatef(0.0, raioMaior/2, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(0.0, -0.05*raioMaior, 0.0);   
		glVertex3f(raioMaior*0.3, -0.05*raioMaior, 0.0);
		glVertex3f(0.0, 0.15*raioMaior, 0.0);
		glVertex3f(raioMaior*0.3, 0.15*raioMaior, 0.0);
    glEnd();
    //--- Helices
        glPushMatrix();
        glTranslatef(raioMaior*0.4, 0.05*raioMaior, 0.0);
        glRotatef(this->thetaHelice, 1.0, 0.0, 0.0);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_TRIANGLES);
		    glVertex3f(-0.15*raioMaior, 0.15*raioMaior, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
		    glVertex3f(0.15*raioMaior, 0.15*raioMaior, 0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
		    glVertex3f(-0.15*raioMaior, -0.15*raioMaior, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
		    glVertex3f(0.15*raioMaior, -0.15*raioMaior, 0.0);
        glEnd();
        glPopMatrix();
    glPopMatrix();

    //DIREITA
    glPushMatrix();
    glTranslatef(0.0, -raioMaior/2, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(0.0, 0.05*raioMaior, 0.0);   
		glVertex3f(raioMaior*0.3, 0.05*raioMaior, 0.0);
		glVertex3f(0.0, -0.15*raioMaior, 0.0);
		glVertex3f(raioMaior*0.3, -0.15*raioMaior, 0.0);
    glEnd();
    //--- Helices
        glPushMatrix();
        glTranslatef(raioMaior*0.4, -0.05*raioMaior, 0.0);
        glRotatef(this->thetaHelice, 1.0, 0.0, 0.0);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0, 0.0, 0.0);
		    glVertex3f(-0.15*raioMaior, 0.15*raioMaior, 0.0);
		    glVertex3f(0.15*raioMaior, 0.15*raioMaior, 0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3f(0.0, 0.0, 0.0);
		    glVertex3f(-0.15*raioMaior, -0.15*raioMaior, 0.0);
		    glVertex3f(0.15*raioMaior, -0.15*raioMaior, 0.0);
        glEnd();
        glPopMatrix();
    glPopMatrix();
}

void Aviao::desenhaAviao(float x, float y, float raioMaior, char tipo){
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glRotatef(this->thetaPlane, 0.0, 0.0, 1.0);
    float raioMenor = 0.3 * raioMaior;
    this->desenhaAsa(raioMaior);
    this->desenhaHelice(raioMaior);
    this->desenhaFuselagem(raioMaior, raioMenor, tipo);
    this->desenhaCauda(raioMaior);
    this->desenhaCabine(0.35*raioMaior, 0.25*raioMenor);
    this->desenhaCanhao(raioMaior);
    glPopMatrix();
}

// void Aviao::atirar(float x, floaty, float raioMaior){
//     float x_tiro =  + raioMaior*cos(thetaAviaoMomento) + raioPlayer/2*cos(thetaAviaoMomento + thetaCanhaoMomento);
//     float y_tiro = y + raioPlayer*sin(thetaAviaoMomento) + raioPlayer/2*sin(thetaAviaoMomento + thetaCanhaoMomento);
//     Tiro t = Tiro(id, x_tiro, y_tiro, raioPlayer, thetaAviaoMomento + thetaCanhaoMomento, veloc);
// }

Aviao::Aviao(/* args */)
{

}

Aviao::~Aviao()
{
}