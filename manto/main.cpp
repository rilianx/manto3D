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

    Vector3 p2 = {1.1,3.2f,4.2f};
    Vector3 p1 = {5,0.2f,0.2f};
    Segment3* segment = new Segment3(p1, p2);
    manto.addFigure(segment);

    float precision = 100; // Genera mas puntos
    // Test de puntos semi-aleatorio aleatorio
    for(float i = 1; i < 15; i+=1/precision) {
        Tester::agregarPunto(manto, i);
    }

    std::cout << "\nFinalizado " << std::endl;

    gettimeofday(&tp, NULL);
    float delta = (float) (tp.tv_sec * 1000 + tp.tv_usec / 1000 - ms) / 1000.0f;
    std::cout << "Tiempo " << delta << "[s]" << std::endl;

    // Guardando instancias generadas
    manto.saveInstance("/Users/brauliolobo/Documents/manto3D/Instance/");

    //manto.validateInstance();
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

    Vector3 p1 = {1,3,3};
    Vector3 p2 = {3,1,1}; // Probar con 3,1,3
    Segment3* segment1 = new Segment3(p1, p2);

    Vector3 p3 = {1.3f, 1.7f, 2};
    Vector3 p4 = {1.7f, 1.3f, 2};
    Segment3* segment2 = new Segment3(p3, p4);
    manto.addFigure(segment1);
    manto.addFigure(segment2);
    //manto.addFigure(point2);


    manto.printAllFigures3();

    manto.saveInstance("/Users/brauliolobo/Documents/manto3D/Instance/");
}

int main() {
    testInfinito();
    //testSegmentos();

    return 0;
}
