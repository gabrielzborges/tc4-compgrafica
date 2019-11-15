#ifndef CIRCULO_H
#define CIRCULO_H


#include <string>
#include "../aviao/aviao.h"

class Circulo {
private:
    float raio, x, y; 
    std::string fill;
    int segmentos, id;
public:
    Circulo(float r, float x, float y, float segmentos, std::string color, int id);
    float getRaio();
    float getXCoord();
    float getYCoord();
    std::string getFill();
    int getNumeroSegmentos();
    int getId();
    void setCoords(float novo_x, float novo_y);
    void setRaio(float novoR);
    void drawCirculo();
    bool colideComigo(float x, float y, float raioDoOutro);
    bool pertenceAoMeuDisco(float x, float y);
    void estaTotalmenteDentro(Circulo* c, Aviao* a, std::string direcaoSentido, float delta);
    void moveX(float vx);
    void moveY(float vy);
    void aumentarRaio(float incremento);
    void diminRaio(float decremento);
    ~Circulo();
};


#endif