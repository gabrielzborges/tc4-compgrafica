#include "./baseInimiga.h"
#include <GL/glut.h>

BaseInimiga::BaseInimiga(int id){
    this->id = id;
    this->bombardeada = false;
}

void BaseInimiga::desenhaBaseInimiga(float x, float y, float raio){
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    //desenha quadrado
    glColor3f((128.0/255.0), (128.0/255.0), (128.0/255.0));
    glBegin(GL_QUADS);
        glVertex3f(-raio * 0.75, 0.75 * raio, 0.0);
        glVertex3f(raio * 0.75, 0.75 * raio, 0.0);
        glVertex3f(raio * 0.75, -0.75 * raio, 0.0);
        glVertex3f(-raio * 0.75, -0.75 * raio, 0.0);
    glEnd();

    //desenha canhao da base
    glRotatef(30, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f (0, (0.05 * raio), 0.0);   
		glVertex3f (0, -(0.05 * raio), 0.0);
		glVertex3f (0.65 * raio, -(0.05 * raio), 0.0);
		glVertex3f (0.65 * raio, (0.05 * raio), 0.0);
    glEnd();
    glPopMatrix();
}

bool BaseInimiga::estaBombardeada(){
    return this->bombardeada;
}

int BaseInimiga::getId(){
    return this->id;
}

void BaseInimiga::setBombardeamento(bool estado){
    this->bombardeada = estado;
}

BaseInimiga::~BaseInimiga(){

}