import plotly as py
import plotly.graph_objs as go
import numpy as np
import csv

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


# Data del grafico
data = []

# Cargando segmentos dominados
# Cargando segmentos no dominados
lista = read_file_segments("Instance/segmentosD.txt")
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
lista = read_file_segments("Instance/segmentos.txt")
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

x, y, z = read_file("Instance/puntos.txt")
tracel = go.Scatter3d(
    x=x,
    y=y,
    z=z,
    mode='markers',  # Aqui se puede agregar +lines para generar lineas
    marker=dict(
        size=3,
        color='seagreen',
        opacity=1),
    name="No dominado")
data.append(tracel)
numero_puntos = len(x)

x, y, z = read_file("Instance/puntosD.txt")
tracel = go.Scatter3d(
    x=x,
    y=y,
    z=z,
    mode='markers',  # Aqui se puede agregar +lines para generar lineas
    marker=dict(
        size=2,
        color='gray',
        opacity=1),
    name="dominado")
data.append(tracel)
numero_puntos_dominados = len(x) - numero_puntos

# Cargando triangulos dominados
lista = read_file_triangles("Instance/triangulosD.txt")
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
lista = read_file_triangles("Instance/triangulos.txt")
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

print(numero_puntos, " puntos graficados")
print(numero_puntos_dominados, " puntos dominados graficados\n")
print(numero_segmentos, " segmentos graficados")
print(numero_segmentos_dominados, " segmentos dominados graficados\n")
print(numero_triangulos, " triangulos graficados")
print(numero_triangulos_dominados, " triangulos dominados graficados")

lista = read_file_polygons("Instance/poligonosD.txt")
for x, y, z in lista:
    tracel = go.Mesh3d(x=x,
                       y=y,
                       z=z,
                       opacity=1,
                       color='gray')
data.append(tracel)

# Cargando triangulos no dominados
lista = read_file_polygons("Instance/poligonos.txt")
for x, y, z in lista:
    tracel = go.Mesh3d(x=x,
                       y=y,
                       z=z,
                       opacity=1,
                       color='rgb(255,100,100)')

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
    yaxis_showspikes=False)
)

fig.show()
