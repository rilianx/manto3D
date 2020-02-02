#include <iostream>
#include "base/Manto.h"
#include "base/figures/figures3/Point3.h"
#include "base/Tester.h"
#include <sys/time.h>
#include <util/RangeContainer.h>
#include <set>
#include <figures/figures3/Triangle3.h>

void testInfinito() {
    Manto manto;

    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    std::cout << "Iniciando " << std::endl;

    float precision = 100; // Genera mas puntos
    // Test de puntos semi-aleatorio aleatorio
    for (float i = 1; i < 15; i += 1 / precision) {
        Tester::agregarPunto(manto, i);
    }

    Vector3 p5 = {1.1, 3.2f, 4.2f};
    Vector3 p6 = {5, 0.2f, 0.2f};
    Segment3 *segment = new Segment3(p6, p5);
    manto.addFigure(segment);

    Vector3 p1 = {1, 3, 3};
    Vector3 p2 = {3, 1, 1}; // Probar con 3,1,3
    Segment3 *segment1 = new Segment3(p1, p2);
    manto.addFigure(segment1);

    Vector3 p3 = {1.3f, 1.7f, 2};
    Vector3 p4 = {1.7f, 1.3f, 2};
    Segment3 *segment2 = new Segment3(p3, p4);
    manto.addFigure(segment2);


    std::cout << "\nFinalizado " << std::endl;

    gettimeofday(&tp, NULL);
    float delta = (float) (tp.tv_sec * 1000 + tp.tv_usec / 1000 - ms) / 1000.0f;
    std::cout << "Tiempo " << delta << "[s]" << std::endl;

    // Guardando instancias generadas
    std::cout << "Guardando instancias" << std::endl;
    manto.saveInstance("/Users/brauliolobo/Documents/manto3D/Instance/");
    std::cout << "Instancias guardadas" << std::endl;

    //manto.validateInstance();
}

void agregarRango(RangeContainer &rc, float lInf, float lSup) {
    std::cout << "Agregando rango " << lInf << ", " << lSup << std::endl;
    rc.agregarRango(lInf, lSup);
}

void testRangos() {
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

void testSegmentos() {
    Manto manto;

    Point3 *p = new Point3(1.00021, 3.02931, 3.94138);

    Vector3 p5 = {1.1, 3.2, 4.2};
    Vector3 p6 = {5, 0.2, 0.2};
    Segment3 *segment = new Segment3(p6, p5);


    manto.addFigure(p);
    manto.addFigure(segment);

    manto.printAllFigures3();

    manto.saveInstance("/Users/brauliolobo/Documents/manto3D/Instance/");
}

void testTriangulos() {
    Manto manto;

    Vector3 p1 = {1, 1, 2};
    Vector3 p2 = {5, 5, 2};
    Vector3 p3 = {5, 1, 4};

    Triangle3 *triangle3 = new Triangle3(p1, p2, p3);

    Vector3 punto = {3, 2, 1};

    std::cout << "Agregando figuras" << std::endl;
    manto.addFigure(triangle3);
    manto.addFigure(new Point3(punto));

    std::cout << "Guardando instancias" << std::endl;
    manto.saveInstance("/Users/brauliolobo/Documents/manto3D/Instance/");
    std::cout << "Listo" << std::endl;

}

void testSimpleTriangulos(){
    Triangle2 triangle2 = {{1,1},{4,1},{1,4}};
    Point2* point2 = new Point2(2,2);
    std::list<Figure2*> fragments;
    triangle2.fragmentedBy(point2, fragments);
    for (auto &fragment : fragments) {
        std::cout << fragment->toString() << std::endl;
    }
}

int main() {
    // ---------------------- EL TO.DO PARA EL NUEVO DIA ----------------------
    // done: Implementar SPLIT POLYGON en los triangulos
    // TODO: Implementar dominacion de triangulos dominados

    // testInfinito();
    // testSegmentos();
    testTriangulos();

    // testSimpleTriangulos();

    return 0;
}
