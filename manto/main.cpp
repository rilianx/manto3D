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
#include <util/Util.h>
#include "util/clipper/clipper.hpp"

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
    manto.saveInstance(Util::getInstancesPath());
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

    manto.saveInstance(Util::getInstancesPath());
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
    manto.saveInstance(Util::getInstancesPath());
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
    Polygon2 p1 = Polygon2(v1,3, Figure3::PROJECTION_XY);

    int v2[6] = {2,0,2,5,5,5};
    Polygon2 p2 = Polygon2(v2,3, Figure3::PROJECTION_XY);

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
    manto.saveInstance(Util::getInstancesPath());
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
    Vector3 p2 = {0.5, 6, 2};
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
        //Tester::agregarPunto(manto, i);
        // std::string path =
        //         "/Users/brauliolobo/Documents/manto3D/Instance/Instance" +
        //                    std::to_string((int)iteracion++) + "/";
        // manto.saveInstance(path);
    }

    // Agragando segmento
    Vector3 ps1 = {1, 3, 2.5};
    Vector3 ps2 = {4, 0.5, 5};
    Segment3* segment3 = new Segment3(ps1, ps2);
    // manto.addFigure(segment3);
    Tester::agregarPunto(manto, 100, *segment3);

    manto.addFigure(polygon3);


    // Tester::agregarPunto(manto, 1 + 0.3f*11);

    // Guardando instancias
    std::cout << "Guardando instancias" << std::endl;
    manto.saveInstance(Util::getInstancesPath());
    std::cout << "Listo" << std::endl;
}

/**
 * Genera un cubo de puntos de testeo para comprobar el espacio dominado por
 * un poligono
 */
void testDominatedSpace(){
    Manto manto;

    // Configuraciones
    const float margen = 1;       // Margen del cubo que encierra al poligono
    const int cPuntos = 6000;   // Cantidad de puntos contenidos en el cubo

    // Creando poligono
    Vector3 p1 = {3, 1, 2};
    Vector3 p2 = {0.5, 6, 2};
    Vector3 p3 = {2, 2, 4};
    Vector3 vectors[3] = {p1, p2, p3};
    Polygon3* polygon3 = new Polygon3(vectors, 3);

    // Agregando poligono al manto
    manto.addFigure(polygon3);

    float x1 = min(min(p1.getX(), p2.getX()), p3.getX()) - margen;
    float y1 = min(min(p1.getY(), p2.getY()), p3.getY()) - margen;
    float z1 = min(min(p1.getZ(), p2.getZ()), p3.getZ()) - margen;
    float x2 = max(max(p1.getX(), p2.getX()), p3.getX()) + margen;
    float y2 = max(max(p1.getY(), p2.getY()), p3.getY()) + margen;
    float z2 = max(max(p1.getZ(), p2.getZ()), p3.getZ()) + margen;

    // Agregando puntos para el testeo
    Tester::testDominatedSpace(manto, polygon3 , cPuntos,
            x1, y1, z1, x2, y2, z2);

    // Guardando instancias
    std::cout << "Guardando instancias" << std::endl;
    manto.saveInstance(Util::getInstancesPath());
    std::cout << "Listo" << std::endl;
}

void testCriticalSpace(Manto& manto, Polygon3* polygon3){
    // Configuraciones
    float min = 0;
    float max = 7;
    float precision = 0.15f;
    float precision_search = 0.001;
    Point3 preP = {0,0,0};
    Point3 p = {0,0,0};


    printf("Iniciando\n");
    for(float z = min; z < max; z += precision){
        preP = {0,0,0};
        printf("%c[2K", 27);
        printf("%.2f\n", z/max / 3);
        for(float y = min; y < max; y += precision){
            for(float x = min; x < max; x += precision_search){
                p = {x, y, z};
                if(polygon3->domina(&p)){
                    if(preP.getX() != 0 && preP.getY() != 0 &&
                       preP.getZ() != 0) {
                        manto.addFigureTestDominatedSpace(
                                new Point3(preP.getX(), preP.getY(),
                                           preP.getZ()), polygon3);
                    }
                    break;
                }
                preP = p;
            }
        }
    }

    for(float z = min; z < max; z += precision){
        preP = {0,0,0};
        printf("%c[2K", 27);
        printf("%.2f\n", (z/max)/3 + 1.0/3.0);
        for(float x = min; x < max; x += precision){
            for(float y = min; y < max; y += precision_search){
                p = {x, y, z};
                if(polygon3->domina(&p)){
                    if(preP.getX() != 0 && preP.getY() != 0 &&
                       preP.getZ() != 0) {
                        manto.addFigureTestDominatedSpace(
                                new Point3(preP.getX(), preP.getY(),
                                           preP.getZ()), polygon3);
                    }
                    break;
                }
                preP = p;
            }
        }
    }

    for(float y = min; y < max; y += precision){
        preP = {0,0,0};
        printf("%c[2K", 27);
        printf("%.2f\n", (y/max)/3 + 2.0/3.0);
        for(float x = min; x < max; x += precision){
            for(float z = min; z < max; z += precision_search){
                p = {x, y, z};
                if(polygon3->domina(&p)){
                    if(preP.getX() != 0 && preP.getY() != 0 &&
                       preP.getZ() != 0) {
                        manto.addFigureTestDominatedSpace(
                                new Point3(preP.getX(), preP.getY(),
                                           preP.getZ()), polygon3);
                    }
                    break;
                }
                preP = p;
            }
        }
    }
}

// Busca el espacio critico. Coloca puntos en los espacios donde se se genera
// un cambio entre espacio dominado y espacio no dominado.
void testPolygonCriticalSpace(){
    Manto manto;

    // Configuraciones
    const float margen = 0;       // Margen del cubo que encierra al poligono
    const int cPuntos = 3000;   // Cantidad de puntos contenidos en el cubo

    // Creando poligono
    Vector3 p1 = {3, 1, 2};
    Vector3 p2 = {0.5, 6, 2};
    Vector3 p3 = {2, 2, 4};
    Vector3 vectors[3] = {p1, p2, p3};
    Polygon3* polygon3 = new Polygon3(vectors, 3);

    manto.addFigure(polygon3);

    testCriticalSpace(manto, polygon3);

    std::cout << "Guardando instancias" << std::endl;
    manto.saveInstance(Util::getInstancesPath());
    std::cout << "Listo" << std::endl;
}

void testDominationPolygonSegment(bool showDominatedSpace){
    Manto manto;

    // Creando poligono
    Vector3 p1 = {3, 1, 2};
    Vector3 p2 = {0.5, 6, 2};
    Vector3 p3 = {2, 2, 4};
    Vector3 vectors[3] = {p1, p2, p3};
    Polygon3* polygon3 = new Polygon3(vectors, 3);
    manto.addFigure(polygon3);

    // Agregando segmento
    Vector3 ps1 = {5,0,4};
    Vector3 ps2 = {0,5,1};
    Segment3* segment3 = new Segment3(ps1, ps2);
    manto.addFigureTestDominatedSpace(segment3, polygon3);

    // Agregando segmento 2
    Vector3 ps3 = {5,0,7};
    Vector3 ps4 = {0,5,4};
    Segment3* segment32 = new Segment3(ps3, ps4);
    manto.addFigureTestDominatedSpace(segment32, polygon3);

    if(showDominatedSpace){
        testCriticalSpace(manto, polygon3);
    }

    manto.saveInstance(Util::getInstancesPath());
}

void testDominationPolygonPolygon(bool showDominatedSpace){
    Manto manto;

    // Creando primer poligono
    Vector3 p1 = {5, 1, 2};
    Vector3 p2 = {0.5, 6, 2};
    Vector3 p3 = {2, 2, 6};
    Vector3 vectors[3] = {p1, p2, p3};
    Polygon3* polygon3 = new Polygon3(vectors, 3);


    // Creando primer poligono
    Vector3 p4 = {3, 0.5, 2};
    Vector3 p5 = {2, 5, 5};
    Vector3 p6 = {1.5, 6, 4};
    Vector3 vectors2[3] = {p4, p5, p6};
    Polygon3* polygon32 = new Polygon3(vectors2, 3);

    // Test de dominacion bueno
    // manto.addFigure(polygon32);
    // manto.addFigureTestDominatedSpace(polygon3, polygon32);

    // Test de dominacion con proboemas
    manto.addFigure(polygon3);
    manto.addFigureTestDominatedSpace(polygon32, polygon3);

    // Guardando instancias
    manto.saveInstance(Util::getInstancesPath());

    // Llamando al graficador
    system("cd /Users/brauliolobo/Documents/manto3D/; python3 grapher.py");
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

void testDivision3D(){
    Manto manto;

    // Creando primer poligono
    Vector3 p1 = {5, 1, 2};
    Vector3 p2 = {0.5, 6, 2};
    Vector3 p3 = {2, 2, 6};
    Vector3 vectors[3] = {p1, p2, p3};
    Polygon3* pDominador = new Polygon3(vectors, 3);


    // Creando segundo poligono
    //Vector3 p4 = {3, 0.5, 2};
    //Vector3 p5 = {2, 5, 5};
    //Vector3 p6 = {1.5, 6, 4};
    Vector3 p4 = {3, 0.5, 2};
    Vector3 p5 = {0, 2, 9.5};
    Vector3 p6 = {1, 6, 8};
    Vector3 vectors2[3] = {p4, p5, p6};
    Polygon3* polygon32 = new Polygon3(vectors2, 3);

    // Test de dominacion con proboemas
    manto.addFigure(pDominador);

    auto fragments = polygon32->split(pDominador->getPlane());
    for (auto &fragment : fragments) {
        auto news_fragments = fragment->fragment(pDominador);

        for (auto &new_fragment : news_fragments) {
            // Comprobando dominancia del fragmento
            auto p3 = new_fragment->getAPoint();
            if (!manto.isCompleteDominated(&p3, pDominador))
                manto.addFigureTestDominatedSpace(new_fragment, nullptr);
        }
    }

    // Guardando instancias
    manto.saveInstance(Util::getInstancesPath());

    // Llamando al graficador
    system("cd /Users/brauliolobo/Documents/manto3D/; python3 grapher.py");
}

void testDivision(){
    int v1[6] = {1,1,2,3,1,5};
    Polygon2 polygon = Polygon2(v1, 3, Figure3::PROJECTION_XY);
    int MAX = 99999;

    int px1 = 0;
    int py1 = 0;
    int px2 = 3;
    int py2 = 8;
    int v2[8] = {px1, 0, px1, py1, px2, py2, px2, 0};
    Polygon2 p2 = Polygon2(v2, 4, Figure3::PROJECTION_XY);

    auto solution = polygon.difference(p2);

    std::cout << "Primer conjunto de soluciones" << std::endl;
    for (auto &p : solution) {
        std::cout << p->toString() << std::endl;
    }

    int v3[8] = {px1, MAX, px1, py1, px2, py2, px2, MAX};
    Polygon2 p3 = Polygon2(v3, 4, Figure3::PROJECTION_XY);

    auto solution2 = polygon.difference(p3);

    std::cout << "Segundo conjunto de soluciones" << std::endl;
    for (auto &p : solution2) {
        std::cout << p->toString() << std::endl;
    }
}

void testDivision2(){
    // Creando poligono
    int v1[6] = {1,1,2,3,1,5};
    Polygon2 polygon = Polygon2(v1, 3, Figure3::PROJECTION_XY);

    // Creando linea
    Line2 *line = new Line2({0, 0}, {3, 8});

    // Dividiendo poligono
    auto result = polygon.split(line);

    for (auto &p : result) {
        std::cout << p->toString() << std::endl;
    }

}

void testDivision3(){
    // Creando poligono
    int v1[12] = {2,2, 3,6, 6,5, 6,3, 4,5, 4,2};
    Polygon2 polygon = Polygon2(v1, 6, Figure3::PROJECTION_XY);

    // Creando linea
    Line2 *line = new Line2({0, 2}, {9, 6});

    // Dividiendo poligono
    auto result = polygon.split(line);

    // Imprimiendo resultado
    for (auto &p : result) {
        std::cout << p->toString() << std::endl;
    }

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
    // testDominacionesPoligonos();


    // testDominatedSpace();
    // testCriticalSpace();
    // testDominationPolygonSegment(false);
    //testDominationPolygonPolygon(false);
    testDivision3D();

    // testPolygonCriticalSpace();

    // testDivision();
    // testDivision2();
    // testDivision3();

    // testSimpleTriangulos();

    return 0;
}