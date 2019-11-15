#ifndef BOMBAS_H
#define BOMBAS_H

#include "../bomba/bomba.h"
#include <vector>

class Bombas {
private:
    static int nth;
    std::vector<Bomba> lista;

public:
    Bombas();
    int getIncrementingNth();
    void resetNth();
    void addBomba(int id, float x, float y, float raioPlayer, float thetaAviaoMomento, 
                    float veloc);
    void drawBombas(Circulo* arena);
    void explodirBombaForaOuTempo(Circulo* arena);
    void moverBombas(float deltaVel);
    void limparBombas();
    void pararBombas();
    ~Bombas();
};


#endif