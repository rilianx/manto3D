# manto3D

## Pruebas
Para hacer pruebas sobre un manto, primero es necesario crear un objeto Manto. Luego, sobre este se pueden agregar objetos Figure3 como Point3 o Segment3:
```c
	...
	// Instancienado manto
    Manto manto;

    // Creanod nuevo punto
    Point3* p = new Point3(1.3f, 1.5f, 1.7f);

    // Agregando punto al manto
    manto.addFigure(p);

    // Creando nuevo segmento
    Vector3 p2 = {2,2,1};
    Vector3 p1 = {1,1,3};
    Segment3* segment = new Segment3(p1, p2);

    // Agregando segmento al manto
    manto.addFigure(segment);
	...
```

## Grapher
Para utilizar el graficador de instancias es necesario tener instalado plotly.

- Instalacion de plotly utilizando pip: 
```batch
	pip install plotly
```

Luego, para guardar las instancias de un manto se utiliza el metodo *saveInstance* de la clase Manto.
```c
	...	

	// Direccion donde se guardaran los archivos a graficar
	const char* path = "/User/Documents/manto3D/Instance/";

	// Guardando instancia del manto
    manto.saveInstance(path);

    ...
```

Finalmente para graficar la instancia se utiliza *grapher.py*. Este busca en su posicion relativa la carpeta *Instance* y grafica el contenido perteneciente a una instancia del manto.
```batch
	python grahper.py
```
El ejemplo anterior, tiene como resultado el siguiente gráfico.

![img](https://i.ibb.co/92smLt4/Captura-de-Pantalla-2020-01-01-a-la-s-20-40-56.png)