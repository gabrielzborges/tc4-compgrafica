#ifndef CIRCULO_H
#define CIRCULO_H


#include "../InimigoVoador/InimigoVoador.h"
// #include "../tiros/tiros.h"
#include "../aviao/aviao.h"
#include <string>

class Circulo {
private:
    float raio, x, y, x_init, y_init;
    std::string fill;
    int segmentos, id;
public:
    Circulo(float r, float x, float y, float segmentos, std::string color, int id);
    float getRaio();
    float getXCoord();
    float getYCoord();
    float getInitXCoord();
    float getInitYCoord();
    std::string getFill();
    int getNumeroSegmentos();
    int getId();
    void setCoords(float novo_x, float novo_y);
    void setRaio(float novoR);
    void drawCirculo();
    bool colideComigo(float x, float y, float raioDoOutro);
    bool pertenceAoMeuDisco(float x, float y);
    void estaTotalmenteDentro(Circulo* c, Aviao* a, std::string direcaoSentido, float delta);
    void inimigoEstaTotalmenteDentro(Circulo* c, InimigoVoador* a, std::string direcaoSentido, float delta);
    // bool baleado(Tiros* tiros);
    void moveX(float vx);
    void moveY(float vy);
    void aumentarRaio(float incremento);
    void diminRaio(float decremento);
    ~Circulo();
};


#endif