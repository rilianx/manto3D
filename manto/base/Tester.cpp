//
// Created by Braulio Lobo on 9/19/19.
//

#include <cmath>
#include "Tester.h"

float Tester::fun1(float param) {
    return abs(cos(param) * 2 + 3);
}
float Tester::fun2(float param) {
    return abs(sin(param) * 2 + 3);
}
float Tester::fun3(float param) {
    return abs(sin(param*2) * 2 + 4);
}

void Tester::agregarPunto(Manto& manto, float param) {
    manto.addFigure(new Point3(fun1(param), fun2(param), fun3(param)));
}

unsigned Tester::p_fraccionaria(double d) {
    unsigned retvalue;

    d = fabs(d);
    d -= (unsigned long)d;
    d *= 1000000; // <-- 6 decimales ya es bastante precision

    retvalue = d;

    if(retvalue < d)        // <-- por si en la conversion ha habido
        ++retvalue;         // <-- perdida de precision
    else if(retvalue > d)   //
        --retvalue;         //

    if(retvalue)                // <-- Si no es 0, intentamos
        while(!(retvalue % 10)) // <-- quitar 0 por la derecha
            retvalue /= 10;     //

    return retvalue;
}


