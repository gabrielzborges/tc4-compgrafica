#ifndef BASEINIMIGAS_H
#define BASEINIMIGAS_H

#include "../BaseInimiga/baseInimiga.h"
#include <vector>

class BasesInimigas {
    private:
    std::vector<BaseInimiga> lista;

    public:
    BasesInimigas();
    BaseInimiga* getBaseInimigaById(int id);
    void setInitConditions();
    void addBaseInimiga(int id);
    int numBasesBombardeadas();
    int numBasesVivas();
    ~BasesInimigas();
};

#endif