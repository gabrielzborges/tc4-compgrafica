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
    void resetNth();
    void addTiro(int id, float x, float y, float raioPlayer, float thetaAviaoMomento, 
                    float thetaCanhaoMomento, float veloc);
    void drawTiros(Circulo* arena);
    void deletarTiroForaArena(Circulo* arena);
    void moverTiros(float deltaVel);
    void limparTiros();
    void pararTiros();
    ~Tiros();
};

#endif