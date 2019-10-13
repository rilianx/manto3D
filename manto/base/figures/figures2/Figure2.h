//
// Created by Braulio Lobo on 9/18/19.
//

#ifndef MANTO_FIGURE2_H
#define MANTO_FIGURE2_H


#include <string>

class Figure2 {

    bool dominated = false;

protected:

    /**
     * Genera una cadena de caracteres con un formate determinado para luego
     * ser leido por un graficador o interprete.
     * @param x     - Coordenada en el eje X.
     * @param y     - Coordenada en el eje Y.
     * @param z     - Coordenada en el eje Z.
     * @return      - Retorna una cadena de caracteres generada.
     */
    std::string getStringCoordenateToGraph(float x, float y, float z);

public:
    bool isDominated() const;
    void setDominated(bool dominated);

    virtual float getKey() = 0;
    virtual std::string toString() = 0;
    virtual std::string toGraphString(int PROJECTION_PLANE) = 0;
};


#endif //MANTO_FIGURE2_H
