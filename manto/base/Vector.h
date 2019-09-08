//
// Created by Braulio Lobo on 9/6/19.
//

#ifndef MANTO_VECTOR_H
#define MANTO_VECTOR_H


#include <ostream>

class Vector {
    float x{};
    float y{};
    float z{};

public:
    Vector(float x, float y, float z);

    Vector();

    /**
     * Calucla el producto cruz entre dos vectores (this y el vector parametro)
     * @param vector    - Vector con el que se quiere realizar el producto cruz
     * @return          - Retorna un vector resultante del producto cruz
     */
    Vector crossProduct(Vector vector) const;

    /**
     * Calcula el producto escalar entre dos vectores
     * @param vector    - Vector con el que se quiere realizar el producto
     *                    escalar.
     * @return          - Retorna una flotante resultante del producto escalar.
     */
    float dotProduct(Vector vector) const;



    float getX() const;
    float getY() const;
    float getZ() const;

    /**
     * Genera una cadena con las caracteristicas del vector
     * @return - Retorna un string con las coordenadas del vector
     */
    std::string toString();

    /**
     * Comprueba si dos vectores son equivalentes
     * @param vector    - Vector que se quiere comparar
     * @return          - Retorna verdadero si el vector pasado como
     *                    parametro es equivalente al this.
     */
    bool equals(Vector vector) const;
};



#endif //MANTO_VECTOR_H
