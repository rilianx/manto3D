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
     * Agrega puntos a lo largo de segmento, esto normalmente sirve para
     * hacer pruebas.
     * @param manto     - Manto donde se van a agregar los puntos
     * @param cantidad  - Cantidad de puntos que se van a agregar
     * @param segment3  - Segmento en donde se van a agregar
     */
    static void agregarPunto(Manto& manto, int cantidad, Segment3 segment3);

    /**
     * Entrega la parte decimal del numero ingresado como parametro.
     * @param d     - Numero al que se le quiere extraer la parte decimal.
     * @return      - Retorna la parte decimal del numero d
     */
    static unsigned p_fraccionaria(double d);
};



#endif //MANTO_TESTER_H
