#ifndef CIRCULOS_H
#define CIRCULOS_H


#include "../circulo/circulo.h"
#include <string>
#include <vector>

class Circulos
{
private:
    std::vector<Circulo> lista;
public:
    Circulos(/* args */);
    std::vector<Circulo> getLista();
    // void addCirculo(Circulo c);
    void addCirculo(float r, float x, float y, float num_segs, std::string color, int id);
    void drawTodosCirculos();
    bool colideComAlgumExistente(float x, float y, float raioDoModelo);
    bool colideComInimigo(float x, float y, float raio);
    int estaSobreQual(float x, float y);
    void arrastaCirculoPorPosicao(float novo_x, float novo_y, int pos);
    Circulo* getCirculoById(int id);
    Circulo* getCirculoByColor(std::string color);
    ~Circulos();
};

#endif