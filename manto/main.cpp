#include <iostream>
#include "base/Manto.h"
#include "base/figures/figures3/Point3.h"
#include "base/Tester.h"
#include <sys/time.h>
#include <util/RangeContainer.h>
#include <set>

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

void agregarRango(RangeContainer &rc, float lInf, float lSup){
    std::cout << "Agregando rango " << lInf << ", " << lSup << std::endl;
    rc.agregarRango(lInf, lSup);
}

void testRangos(){
    RangeContainer rc = RangeContainer();

    agregarRango(rc, 1, 2);
    agregarRango(rc, 1, 2);
    agregarRango(rc, 1, 3);
    agregarRango(rc, 1, 2);
    agregarRango(rc, 0.5f, 3);
    agregarRango(rc, 4, 5);

    std::cout << "Rangos agregados" << std::endl;

    rc.imprimirRangos();
}

void testSegmentos(){
    Manto manto;

    Point3* point3 = new Point3(1.5f, 1.7f, 1.3f);

    Vector3 p2 = {2,2,1};
    Vector3 p1 = {1,1,3};
    Segment3* segment3 = new Segment3(p1, p2);

    manto.addFigure(segment3);
    manto.addFigure(point3);

    manto.printAllFigures3();
}

int main() {
    // testInfinito();
    // testRangos();
    testSegmentos();


    return 0;
}
