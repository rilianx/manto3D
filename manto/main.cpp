#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include "base/Manto.h"
#include "base/Tester.h"
#include "base/figures/figures3/Point3.h"
#include "base/figures/figures3/Triangle3.h"
#include "base/figures/figures3/Polygon3.h"
#include "base/figures/figures2/Polygon2.h"
#include <sys/time.h>
#include <util/RangeContainer.h>
#include <set>
#include <iomanip>
#include "util/clipper/clipper.hpp"

#include "util/IndexIterator.h"

using namespace std;
using namespace ClipperLib;


void testPoligonos(){
    Paths subject;  // Poligonos primarios
    Paths clip;     // Poligonos secundarios de comparacion
    Paths solution; // Poligonos solucion
    Clipper clpr;

    float scale = 100;

    // Creando subject
    subject.resize(1);
    subject[0].resize(3);
    subject[0][0].X = 1.0 * scale;
    subject[0][0].Y = 1.0 * scale;
    subject[0][1].X = 1.0 * scale;
    subject[0][1].Y = 3.0 * scale;
    subject[0][2].X = 4.0 * scale;
    subject[0][2].Y = 1.0 * scale;

    // Creando clip
    clip.resize(1);
    clip[0].resize(3);
    clip[0][0].X = 2.0 * scale;
    clip[0][0].Y = 0.0 * scale;
    clip[0][1].X = 2.0 * scale;
    clip[0][1].Y = 5.0 * scale;
    clip[0][2].X = 5.0 * scale;
    clip[0][2].Y = 5.0 * scale;

    clpr.Clear();
    clpr.AddPaths(subject, ptSubject, true);
    clpr.AddPaths(clip, ptClip, true);
    clpr.Execute(ctDifference, solution, pftEvenOdd, pftEvenOdd);

    int countr = 0;
    for (auto &poly : solution) {
        std::cout << "Poligono " << countr++ << std::endl;
        for (auto &vector2 : poly) {
            std::cout << vector2.X << ", " << vector2.Y << std::endl;
        }
    }

}


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

void testClipper(){
    int v1[6] = {1,1,1,3,4,1};
    Polygon2 p1 = Polygon2(v1,3);

    int v2[6] = {2,0,2,5,5,5};
    Polygon2 p2 = Polygon2(v2,3);

    auto solution = p1.difference(p2);

    int countr = 0;
    for (auto &polygon : solution) {
        std::cout << polygon->toString() << std::endl;
    }
}

void testPoligonosEnManto(){
    // Creando manto
    Manto manto;

    // Creando vectores
    Vector3 p1 = {1, 1, 2};
    Vector3 p2 = {5, 5, 2};
    Vector3 p3 = {5, 1, 4};
    Vector3 vectors[3] = {p1, p2, p3};

    // Creando poligono
    Polygon3* polygon3 = new Polygon3(vectors, 3);

    // Creando punto
    Vector3 punto = {3, 2.2, 1};
    Vector3 punto2 = {2, 2.5, 1};
    Vector3 punto3 = {4, 1.3, 1};
    Vector3 punto4 = {3.5, 1.6, 1.5};

    // Agregando figuras
    std::cout << "Agregando figuras al manto" << std::endl;
    // manto.addFigure(new Point3(punto));
    // manto.addFigure(new Point3(punto2));
    // manto.addFigure(new Point3(punto3));
    //manto.addFigure(new Segment3(punto, punto3));
    manto.addFigure(new Polygon3({punto, punto3, punto4}, 3));
    manto.addFigure(polygon3);
    std::cout << "Figuras agregadas" << std::endl;

    // Guardando instancias
    std::cout << "Guardando instancias" << std::endl;
    manto.saveInstance("/Users/brauliolobo/Documents/manto3D/Instance/");
    std::cout << "Listo" << std::endl;
}

void testDominacionesPoligonos(){
    /*
     * Este test sirve para comprobar la dominancia de puntos y segmentos por
     * poligonos
     */

    // Creando el manto
    Manto manto;

    // Creando poligono
    Vector3 p1 = {3, 1, 2};
    Vector3 p2 = {2, 6, 2};
    Vector3 p3 = {2, 2, 4};
    Vector3 vectors[3] = {p1, p2, p3};
    Polygon3* polygon3 = new Polygon3(vectors, 3);

    // Agregando poligono al manto
    // manto.addFigure(new Point3(4.5, 2.44, 2.92));

    // Agregando puntos
    float precision = 0.05f; // Genera mas puntos
    int iteracion = 1;
    for (float i = 1; i < 17; i += precision) {
        std::cout << iteracion << std::endl;
        Tester::agregarPunto(manto, i);
        std::string path =
                "/Users/brauliolobo/Documents/manto3D/Instance/Instance" +
                           std::to_string((int)iteracion++) + "/";
        manto.saveInstance(path);
    }

    manto.addFigure(polygon3);


    // Tester::agregarPunto(manto, 1 + 0.3f*11);

    // Guardando instancias
    std::cout << "Guardando instancias" << std::endl;
    manto.saveInstance("/Users/brauliolobo/Documents/manto3D/Instance/");
    std::cout << "Listo" << std::endl;
}

void testProyecciones(){
    // Creando vectores
    Vector3 p1 = {1, 1, 2};
    Vector3 p2 = {5, 5, 2.1};
    Vector3 p3 = {5, 1, 4};
    Vector3 vectors[3] = {p1, p2, p3};

    // Creando poligono
    Polygon3* polygon3 = new Polygon3(vectors, 3);
    std::cout << "Poligono: " << polygon3->toString() << std::endl;

    // Proyecciones XY
    Polygon2* projXY = polygon3->getProjection(Figure3::PROJECTION_XY);
    std::cout << "Proyeccion XY: " << projXY->toString() << std::endl;
    Polygon3* polGenXY = projXY->toPolygon3(polygon3, Figure3::PROJECTION_XY);
    std::cout << "Poligono generado: " << polGenXY->toString() << std::endl;

    // Proyecciones XZ
    Polygon2* projXZ = polygon3->getProjection(Figure3::PROJECTION_XZ);
    std::cout << "Proyeccion XZ: " << projXZ->toString() << std::endl;
    Polygon3* polGenXZ = projXZ->toPolygon3(polygon3, Figure3::PROJECTION_XZ);
    std::cout << "Poligono generado: " << polGenXZ->toString() << std::endl;

    // Proyecciones YZ
    Polygon2* projYZ = polygon3->getProjection(Figure3::PROJECTION_YZ);
    std::cout << "Proyeccion YZ: " << projYZ->toString() << std::endl;
    Polygon3* polGenYZ = projYZ->toPolygon3(polygon3, Figure3::PROJECTION_YZ);
    std::cout << "Poligono generado: " << polGenYZ->toString() << std::endl;
}

int main() {
    // ---------------------- EL TO.DO PARA EL NUEVO DIA ----------------------
    // done: Implementar SPLIT POLYGON en los triangulos
    // TODO: Implementar dominacion de triangulos dominados

    // testInfinito();
    // testSegmentos();
    // testTriangulos();

    // testPoligonosEnManto();
    // testProyecciones();
    testDominacionesPoligonos();

    // testSimpleTriangulos();

    return 0;
}