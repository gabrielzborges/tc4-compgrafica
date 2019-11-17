#ifndef CIRCULOS_H
#define CIRCULOS_H


#include "../circulo/circulo.h"
#include "../InimigosVoadores/InimigosVoadores.h"
#include <string>
#include <vector>

class Circulos
{
private:
    std::vector<Circulo> lista;
public:
    Circulos(/* args */);
    std::vector<Circulo> getLista();
    Circulo* getLastAdded();
    void setInitalPositions();
    void setInitialConditions();
    // void addCirculo(Circulo c);
    void addCirculo(float r, float x, float y, float num_segs, std::string color, int id);
    void drawTodosCirculos();
    bool colideComAlgumExistente(float x, float y, float raioDoModelo);
    bool colideComInimigo(float x, float y, float raio);
    int estaSobreQual(float x, float y);
    void arrastaCirculoPorPosicao(float novo_x, float novo_y, int pos);
    void moverInimigos(Circulo* arena, float deltaTempoIdle, InimigosVoadores inimigos);
    void teletransporteInimigos(Circulo* arena, InimigosVoadores inimigos, float deltaTempoIdle);
    void matarCirculoById(int id, float x, float y);
    Circulo* getCirculoById(int id);
    Circulo* getCirculoByColor(std::string color);
    ~Circulos();
};

#endif