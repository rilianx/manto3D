//
// Created by Braulio Lobo on 9/19/19.
//

#ifndef MANTO_TESTER_H
#define MANTO_TESTER_H

#include <math.h>
#include <stdio.h>
#include "Manto.h"

class Tester {

public:
    // Variables debug
    static const bool DEBUG_DELET = false;

    static float fun1(float param);
    static float fun2(float param);
    static float fun3(float param);

    /**
     * Agrega puntos al mento utilizando las funciones fun1, fun2 y fun3
     * @param manto     - Manto al que se le van a agregar los puntos.
     * @param param     - Parametro que se va a usar en las tres funciones.
     */
    static void agregarPunto(Manto& manto, float param);

    /**
     * Entrega la parte decimal del numero ingresado como parametro.
     * @param d     - Numero al que se le quiere extraer la parte decimal.
     * @return      - Retorna la parte decimal del numero d
     */
    static unsigned p_fraccionaria(double d);
};



#endif //MANTO_TESTER_H
