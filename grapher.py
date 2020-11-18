import plotly as py
import plotly.graph_objs as go
import numpy as np
import csv
import tripy
import os
from random import random

# FIXME: si esto no es necesario hay que borrarlo
import plotly.figure_factory as ff

nPuntos = 0
nSegmentos = 0


def read_file(file_name):
    xs = []
    ys = []
    zs = []
    with open(file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=';')
        for row in csv_reader:
            xs.append(float(row[0].replace(',', '.')))
            ys.append(float(row[1].replace(',', '.')))
            zs.append(float(row[2].replace(',', '.')))
    return xs, ys, zs


def read_file_segments(file_name):
    result = []
    xs = []
    ys = []
    zs = []
    with open(file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=';')
        for row in csv_reader:
            xs.append(float(row[0].replace(',', '.')))
            ys.append(float(row[1].replace(',', '.')))
            zs.append(float(row[2].replace(',', '.')))
            xs.append(float(row[3].replace(',', '.')))
            ys.append(float(row[4].replace(',', '.')))
            zs.append(float(row[5].replace(',', '.')))
            result.append((xs, ys, zs))
            xs = []
            ys = []
            zs = []
    return result


def read_file_triangles(file_name):
    result = []
    xs = []
    ys = []
    zs = []
    with open(file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=';')
        for row in csv_reader:
            xs.append(float(row[0].replace(',', '.')))
            ys.append(float(row[1].replace(',', '.')))
            zs.append(float(row[2].replace(',', '.')))
            xs.append(float(row[3].replace(',', '.')))
            ys.append(float(row[4].replace(',', '.')))
            zs.append(float(row[5].replace(',', '.')))
            xs.append(float(row[6].replace(',', '.')))
            ys.append(float(row[7].replace(',', '.')))
            zs.append(float(row[8].replace(',', '.')))
            result.append((xs, ys, zs))
            xs = []
            ys = []
            zs = []
    return result


def read_file_polygons(file_name):
    result = []
    with open(file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=';')
        for row in csv_reader:
            selector = 0
            coordenadas = [[], [], []]
            for i in row:
                coord = float(i.replace(",", "."))
                coordenadas[selector].append(coord)
                selector += 1
                if selector == 3:
                    selector = 0
            result.append(coordenadas)
    return result


def triangule(x, y, z):
    # Creando poligono
    polygon = []
    polygon3d = []
    for i in range(len(x)):
        polygon.append((x[i], y[i]))
        polygon3d.append([x[i], y[i], z[i]])

    # Triangulando
    triangles = tripy.earclip(polygon)
    triangles3D = []
    for triangle in triangles:
        ind0 = polygon.index(triangle[0])
        ind1 = polygon.index(triangle[1])
        ind2 = polygon.index(triangle[2])
        triangles3D.append([polygon3d[ind0],
                            polygon3d[ind1],
                            polygon3d[ind2]])
    # print("Triangulacion para\n {}\n {}\n {}\n".format(x,y,z))
    # print("\n", triangles3D)

    result = []
    for triangle in triangles3D:
        sub_result = [[], [], []]
        for coord in triangle:
            sub_result[0].append(coord[0])
            sub_result[1].append(coord[1])
            sub_result[2].append(coord[2])
        result.append(sub_result)
    return result

def graficar(sub_path="", show=True ,save_image=False, image_name="image"):
    # Data del grafico
    data = []
    path = "Instance/" + sub_path
    # Cargando segmentos dominados
    # Cargando segmentos no dominados
    lista = read_file_segments(path + "segmentosD.txt")
    nSegmentos = 0
    for x, y, z in lista:
        nSegmentos += 1
        tracel = go.Scatter3d(
            x=x,
            y=y,
            z=z,
            mode='lines',  # Aqui se puede agregar +lines para generar lineas
            line=dict(
                color='gray',
                width=1
            ),
        )
        data.append(tracel)
    numero_segmentos_dominados = len(lista)

    # Cargando segmentos no dominados
    lista = read_file_segments(path + "segmentos.txt")
    for x, y, z in lista:
        nSegmentos += 1
        tracel = go.Scatter3d(
            x=x,
            y=y,
            z=z,
            mode='markers+lines',
            # Aqui se puede agregar +lines para generar lineas
            marker=dict(
                size=3,
                color='darkred',
                opacity=1),

            line=dict(
                color='blue',
                width=2
            )
        )
        data.append(tracel)
    numero_segmentos = len(lista)
    numero_segmentos_dominados -= numero_segmentos

    x, y, z = read_file(path + "puntos.txt")
    tracel = go.Scatter3d(
        x=x,
        y=y,
        z=z,
        mode='markers',  # Aqui se puede agregar +lines para generar lineas
        marker=dict(
            size=3,
            color='rgb(100,100,255)',
            opacity=1),
        name="No dominado")
    data.append(tracel)
    numero_puntos = len(x)

    x, y, z = read_file(path + "puntosD.txt")
    tracel = go.Scatter3d(
        x=x,
        y=y,
        z=z,
        mode='markers',  # Aqui se puede agregar +lines para generar lineas
        marker=dict(
            size=1,
            color='gray',
            opacity=1),
        name="dominado")
    data.append(tracel)
    numero_puntos_dominados = len(x) - numero_puntos

    # Cargando triangulos dominados
    lista = read_file_triangles(path + "triangulosD.txt")
    for x, y, z in lista:
        tracel = go.Mesh3d(x=x,
                        y=y,
                        z=z,

                        # Forzando triangulacion ordenada
                        i=[0],
                        j=[1],
                        k=[2],
                        opacity=1,
                        color='gray')
    data.append(tracel)
    numero_triangulos_dominados = len(lista)

    # Cargando triangulos no dominados
    lista = read_file_triangles(path + "triangulos.txt")
    for x, y, z in lista:
        tracel = go.Mesh3d(x=x,
                        y=y,
                        z=z,

                        # Forzando triangulacion ordenada
                        i=[0],
                        j=[1],
                        k=[2],
                        opacity=1,
                        color='rgb(255,100,100)')
    data.append(tracel)
    numero_triangulos = len(lista)
    numero_triangulos_dominados -= numero_triangulos

    # print(numero_puntos, " puntos graficados")
    # print(numero_puntos_dominados, " puntos dominados graficados\n")
    # print(numero_segmentos, " segmentos graficados")
    # print(numero_segmentos_dominados, " segmentos dominados graficados\n")
    # print(numero_triangulos, " triangulos graficados")
    # print(numero_triangulos_dominados, " triangulos dominados graficados\n")

    lista = read_file_polygons(path + "poligonosD.txt")
    for x, y, z in lista:
        tracel = go.Mesh3d(x=x,
                        y=y,
                        z=z,
                        opacity=0.5,
                        color='gray')
    data.append(tracel)
    numero_poligonos_dominados = len(lista)

    # Cargando triangulos no dominados
    lista = read_file_polygons(path + "poligonos.txt")
    for x, y, z in lista:
        color = f'rgb({int(150 * random()) + 100},{int(150 * random()) + 100},100)'
        for triangle in triangule(x, y, z):
            # print(triangle)
            x2 = triangle[0]
            y2 = triangle[1]
            z2 = triangle[2]
            tracel = go.Mesh3d(x=x2,
                            y=y2,
                            z=z2,
                            opacity=1,
                            color=color)
            data.append(tracel)

    numero_poligonos = len(lista)
    numero_poligonos_dominados -= numero_poligonos

    # print(numero_poligonos, " poligonos graficados")
    # print(numero_poligonos_dominados, " poligonos dominados graficados")

    layout = go.Layout(
        margin=dict(
            l=0,
            r=0,
            b=0,
            t=0))

    fig = go.Figure(data=data, layout=layout)

    fig.update_layout(scene=dict(
        xaxis=dict(nticks=14, range=[0, 7], ),
        yaxis=dict(nticks=14, range=[0, 7], ),
        zaxis=dict(nticks=14, range=[0, 7], ),
        xaxis_showspikes=False,
        yaxis_showspikes=False,
        ),
    )

    if show:
        fig.show()

    if save_image:
        if not os.path.exists("images"):
            os.mkdir("images")
        fig.write_image("images/" + image_name + ".png")

def generar_imagenes(desde=1, hasta=1):
    for i in range(desde, hasta+1, 1):
        print("Generando imagen de la instancia ({}/{})".format(i, hasta))
        graficar("Instance{}/".format(i), show=False, save_image=True,
            image_name="{}".format(i))

from sys import argv
if len(argv) == 2 and argv[1] == "-save": 
    generar_imagenes(desde=1, hasta=54)
else:
    graficar()
#graficar(show=False, save_image=True, image_name="Final")
# graficar()
