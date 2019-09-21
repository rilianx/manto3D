//
// Created by Braulio Lobo on 9/19/19.
//

#include <cmath>
#include "Tester.h"

float Tester::fun1(float param) {
    return cos(param);
}
float Tester::fun2(float param) {
    return sin(param);
}
float Tester::fun3(float param) {
    return sin(param*2);
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
