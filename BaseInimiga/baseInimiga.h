#ifndef BASEINIMIGA_H
#define BASEINIMIGA_H

class BaseInimiga {
    private:
    int id;
    bool bombardeada;

    public:
    BaseInimiga(int id);
    void desenhaBaseInimiga(float x, float y, float raio);
    bool estaBombardeada();
    int getId();
    void setBombardeamento(bool estado);
    ~BaseInimiga();
};

#endif