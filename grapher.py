import plotly as py
import plotly.graph_objs as go
import numpy as np
import csv

# FIXME: si esto no es necesario hay que borrarlo
import plotly.figure_factory as ff

def readFile(file_name):
    xs = []
    ys = []
    zs = []
    with open(file_name) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=';')
        for row in csv_reader:
            xs.append(float(row[0].replace(',','.')))
            ys.append(float(row[1].replace(',','.')))
            zs.append(float(row[2].replace(',','.')))
    return (xs, ys, zs)

# Data del grafico
data = []

x, y, z = readFile("Instance/Figures.txt") 
tracel = go.Scatter3d(
    x=x,
    y=y,
    z=z,
    mode='markers', # Aqui se puede agregar +lines para generar lineas
    marker=dict(
        size=3,
        color='seagreen',
        opacity=1),
    name="No dominado")
data.append(tracel)

x, y, z = readFile("Instance/Pxy.txt") 
tracel = go.Scatter3d(
    x=x,
    y=y,
    z=z,
    mode='markers', 
    marker=dict(
        size=2,
        color='gray',
        opacity=1),
    name="Pxy")
data.append(tracel)

x, y, z = readFile("Instance/Pxz.txt") 
tracel = go.Scatter3d(
    x=x,
    y=y,
    z=z,
    mode='markers',
    marker=dict(
        size=2,
        color='gray',
        opacity=1),
    name="Pxz")
data.append(tracel)

x, y, z = readFile("Instance/Pyz.txt") 
tracel = go.Scatter3d(
    x=x,
    y=y,
    z=z,
    mode='markers',
    marker=dict(
        size=2,
        color='gray',
        opacity=1),
    name="Pyz")
data.append(tracel)

layout = go.Layout(
    margin=dict(
        l=0,
        r=0,
        b=0,
        t=0))

fig = go.Figure(data=data, layout=layout)
fig.show()