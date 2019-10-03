#include <iostream>
#include "base/Manto.h"
#include "base/figures/figures3/Point3.h"
#include "base/Tester.h"

int main() {
    Manto manto;

    std::cout << "Iniciando" << std::endl;

    // Test de puntos semi-aleatorio aleatorio
    for(float i = 1; i < 15; i+=0.01f) {
        float param = i;
        float multipler = (float)(rand()%4)/4.0f + 2;
        manto.addFigure(new Point3(
                abs(Tester::fun1(param) * multipler + 3),
                abs(Tester::fun2(param) * multipler + 3),
                abs(Tester::fun3(param) * multipler + 4)));
    }

    //manto.addFigure(new Point3(1,1,1));
    //manto.addFigure(new Point3(2,0.9f,2));


    std::cout << "\nFinalizado " << std::endl;
    //manto.printAllFigures3();

    manto.saveInstance("/Users/brauliolobo/Desktop/Instance/");

    return 0;
}
