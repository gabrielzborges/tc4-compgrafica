#ifndef TIROS_H
#define TIROS_H

#include <vector>
#include "../tiro/tiro.h"

class Tiros {
 private:
    static int nth;
    std::vector<Tiro> lista;

public:
    Tiros();
    int getIncrementingNth();
    std::vector<Tiro> getLista();
    void resetNth();
    void addTiro(int id, float x, float y, float raioPlayer, float thetaAviaoMomento, 
                    float thetaCanhaoMomento, float veloc, char quem);
    void drawTiros(Circulo* arena);
    void deletarTiroForaArena(Circulo* arena);
    void moverTiros(float deltaVel);
    bool playerBaleado(Circulo* player);
    void limparTiros();
    void pararTiros();
    ~Tiros();
};

#endif