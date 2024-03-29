#ifndef AVIAO_H
#define AVIAO_H

// #include "../tiro/tiro.h"
class Aviao
{
private:
    /* data */
    float thetaCanhao;
    float thetaPlane;
    float thetaHelice;
    bool perdeu, ganhou;
public:
    float getThetaCanhao();
    float getThetaPlane();
    bool getPerdeu();
    bool getGanhou();
    void setThetaPlane(float theta);
    void setThetaCanhao(float theta);
    void setThetaHelice(float theta);
    void setPerdeu(bool estado);
    void setGanhou(bool estado);
    void rotatePlane(float theta);
    void rotateCanhao(float theta);
    void rotateHelice(float delta, float raioMaior);
    void desenhaFuselagem(float raioMaior, float raioMenor, char tipo);
    void desenhaAsa(float raioMaior);
    void desenhaCauda(float raioMaior);
    void desenhaCabine(float raioMaior, float raioMenor);
    void desenhaCanhao(float raioMaior);
    void desenhaHelice(float raioMaior);
    void desenhaAviao(float x, float y, float raioMaior, char tipo);
    // Tiro atirar(float x, float y, float raioMaior);

    Aviao(/* args */);
    ~Aviao();
};

#endif