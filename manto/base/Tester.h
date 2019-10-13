//
// Created by Braulio Lobo on 9/19/19.
//

#ifndef MANTO_TESTER_H
#define MANTO_TESTER_H

#include <math.h>
#include <stdio.h>

class Tester {

public:
    // Variables debug
    static const bool DEBUG_DELET = false;

    static float fun1(float param);
    static float fun2(float param);
    static float fun3(float param);

    /**
     * Entrega la parte decimal del numero ingresado como parametro.
     * @param d     - Numero al que se le quiere extraer la parte decimal.
     * @return      - Retorna la parte decimal del numero d
     */
    static unsigned p_fraccionaria(double d);
};



#endif //MANTO_TESTER_H
