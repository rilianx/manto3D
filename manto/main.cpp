#include <iostream>
#include "base/Manto.h"
#include "base/figures/figures3/Point3.h"
#include "base/Tester.h"
#include <sys/time.h>
#include <util/RangeContainer.h>

void testInfinito(){
    Manto manto;

    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    std::cout << "Iniciando " << std::endl;

    // Test de puntos semi-aleatorio aleatorio
    for(float i = 1; i < 15; i+=0.01f) {
        float param = i;
        float multipler = (float)(rand()%4)/4.0f + 2;
        manto.addFigure(new Point3(
                abs(Tester::fun1(param) * multipler + 3),
                abs(Tester::fun2(param) * multipler + 3),
                abs(Tester::fun3(param) * multipler + 4)));
    }

    std::cout << "\nFinalizado " << std::endl;

    gettimeofday(&tp, NULL);
    float delta = (float) (tp.tv_sec * 1000 + tp.tv_usec / 1000 - ms) / 1000.0f;
    std::cout << "Tiempo " << delta << "[s]" << std::endl;

    // Guardando instancias generadas
    manto.saveInstance("/Users/brauliolobo/Documents/Manto/Instance/");
}

void testRangos(){
    RangeContainer rc = RangeContainer();

    std::cout << "Agregando rango 15, 20" << std::endl;
    rc.agregarRango(15,20);

    std::cout << "\nAgregando rango 1,5" << std::endl;
    rc.agregarRango(1,5);

    std::cout << "\nAgregando rango 23,28" << std::endl;
    rc.agregarRango(23,28);

    std::cout << "\nAgregando rango 6,10" << std::endl;
    rc.agregarRango(6,10);

    // std::cout << "\nAgregando rango 4,7" << std::endl;
    // rc.agregarRango(4,7);

    std::cout << "\nAgregando rango 0,13" << std::endl;
    rc.agregarRango(0,13);

    std::cout << "Rangos agregados" << std::endl;

    rc.imprimirRangos();

}

int main() {
    // testInfinito();
    testRangos();

    return 0;
}
