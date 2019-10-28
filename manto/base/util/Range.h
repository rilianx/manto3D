//
// Created by Braulio Lobo on 24-10-19.
//

#ifndef MANTO_RANGE_H
#define MANTO_RANGE_H


class Range {
    float lInf;
    float lSup;

public:

    Range();
    Range(float lInf, float lSup);

    float getLInf() const;

    float getLSup() const;

    /**
     * Comprueba si el numero ingresado como parametro esta contenido dentro
     * del rango.
     * @param num   - Numero que se quiere comprobar si está dentor del rango
     * @return      - Retorna True si está contenido, False en caso contrario
     */
    bool contiene(float num);

    /**
     * Establece un nuevo limite para el rango. En caso de que el nuevo
     * limite este por debajo del rango, se exapnde el limite infrerior, en
     * caso de que este contenido, no hace anda, y finalmente, en caso de que
     * el limite ingresado sea superior al lSup, se expande este ultimo.
     * @param limit - Nuevo limite
     */
    void setLimit(float limit);
};


#endif //MANTO_RANGE_H
