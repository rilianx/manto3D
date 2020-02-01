import plotly as py
import plotly.graph_objs as go
import numpy as np
import csv

# FIXME: si esto no es necesario hay que borrarlo
import plotly.figure_factory as ff

nPuntos = 0
nSegmentos = 0

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

def readFileSegments(file_name):
	lista = []
	xs = []
	ys = []
	zs = []
	with open(file_name) as csv_file:
		csv_reader = csv.reader(csv_file, delimiter=';')
		for row in csv_reader:
			xs.append(float(row[0].replace(',','.')))
			ys.append(float(row[1].replace(',','.')))
			zs.append(float(row[2].replace(',','.')))
			xs.append(float(row[3].replace(',','.')))
			ys.append(float(row[4].replace(',','.')))
			zs.append(float(row[5].replace(',','.')))
			lista.append((xs, ys, zs))
			xs = []
			ys = []
			zs = []
	return lista

def readFileTriangles(file_name):
	lista = []
	xs = []
	ys = []
	zs = []
	with open(file_name) as csv_file:
		csv_reader = csv.reader(csv_file, delimiter=';')
		for row in csv_reader:
			xs.append(float(row[0].replace(',','.')))
			ys.append(float(row[1].replace(',','.')))
			zs.append(float(row[2].replace(',','.')))
			xs.append(float(row[3].replace(',','.')))
			ys.append(float(row[4].replace(',','.')))
			zs.append(float(row[5].replace(',','.')))
			xs.append(float(row[6].replace(',','.')))
			ys.append(float(row[7].replace(',','.')))
			zs.append(float(row[8].replace(',','.')))
			lista.append((xs, ys, zs))
			xs = []
			ys = []
			zs = []
	return lista

# Data del grafico
data = []


# Cargando segmentos dominados
# Cargando segmentos no dominados
lista = readFileSegments("Instance/segmentosD.txt")
for x,y,z in lista:
	nSegmentos += 1
	tracel = go.Scatter3d(
		x=x,
		y=y,
		z=z,
		mode='lines', # Aqui se puede agregar +lines para generar lineas
		line=dict(
			color='gray',
			width=1
		),
	)
	data.append(tracel)


# Cargando segmentos no dominados
lista = readFileSegments("Instance/segmentos.txt")
for x,y,z in lista:
	nSegmentos += 1
	tracel = go.Scatter3d(
		x=x,
		y=y,
		z=z,
		mode='markers+lines', # Aqui se puede agregar +lines para generar lineas
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

x, y, z = readFile("Instance/puntos.txt") 
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
nPuntos += len(x)

x, y, z = readFile("Instance/puntosD.txt") 
tracel = go.Scatter3d(
	x=x,
	y=y,
	z=z,
	mode='markers', # Aqui se puede agregar +lines para generar lineas
	marker=dict(
		size=2,
		color='gray',
		opacity=1),
	name="dominado")
data.append(tracel)
nPuntos += len(x)

# Cargando triangulos dominados
lista = readFileTriangles("Instance/triangulosD.txt")
for x,y,z in lista:
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

# Cargando triangulos no dominados
lista = readFileTriangles("Instance/triangulos.txt")
for x,y,z in lista:
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

print(nPuntos, " puntos graficados")
print(nSegmentos, " segmentos graficados")

layout = go.Layout(
	margin=dict(
		l=0,
		r=0,
		b=0,
		t=0))

fig = go.Figure(data=data, layout=layout)

fig.update_layout(scene = dict(
		 xaxis = dict(nticks=14, range=[0,7],),
		 yaxis = dict(nticks=14, range=[0,7],),
		 zaxis = dict(nticks=14, range=[0,7],),
		 xaxis_showspikes=False,
		 yaxis_showspikes=False)
		)


fig.show()
