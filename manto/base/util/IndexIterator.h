//
// Created by Braulio Lobo on 14-04-20.
//

#ifndef MANTO_INDEXITERATOR_H
#define MANTO_INDEXITERATOR_H


class IndexIterator {
    int index;
    int limitTop;
    int limitBottom;

public:
    IndexIterator(int index, int limitTop);
    IndexIterator(int index, int limitTop, int limitBottom);

    /**
     * Suma uno al index. Si se pasa del limite superior vuelve al limite
     * inferior
     */
    void next();

    /**
     * Resta uno al index. Si se pasa del limite inferior vuelve al limite
     * superior
     */
    void back();

    /**
     * Obtiene el valor actual del index
     * @return  - Retorna un entero correspondiente al valor actual del indice
     */
    int get();
};


#endif //MANTO_INDEXITERATOR_H
