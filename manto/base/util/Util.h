//
// Created by Braulio Lobo on 13-06-20.
//

#ifndef MANTO_UTIL_H
#define MANTO_UTIL_H


#include <string>

class Util {

public:
    /**
     * Obtiene la ruta en que se esta ejecutando el programa. Nota, el
     * programa debe estar contenido en al carpeta manto3D para que esto
     * funcione, en caso contrario arrojará un error
     * @return  - Retorna un string con la ruta en que se esta ejecutando el
     *            programa.
     */
    static std::string getCurrentPath();

    /**
     * Obtiene la ruta en que se deben guardar las intancias generadas por el
     * programa
     * @return  - Retorna un string con la ruta en que se está ejecutando el
     *            programa.
     */
    static std::string getInstancesPath();
};


#endif //MANTO_UTIL_H
