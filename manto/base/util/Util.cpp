//
// Created by Braulio Lobo on 13-06-20.
//

#include <unistd.h>
#include <iostream>
#include <sstream>
#include "Util.h"

std::string Util::getCurrentPath() {

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    // Limpiando path
    std::string path = cwd;
    std::size_t found = path.find("manto3D");
    if(found == std::string::npos){
       perror("Error: No se encuentra la ruta de manto3D, es necesario que el"
              " programa este contenido en esta carpeta para generar las "
              "instancias y almacenar resultados");
    }
    std::string realPath = path.substr(0,found+8);
    return realPath;
}

std::string Util::getInstancesPath() {
    std::ostringstream ss;

    // Obteniendo ruta de instancias
    std::string base_path = getCurrentPath();
    ss << base_path << "Instance/";

    return ss.str();
}
