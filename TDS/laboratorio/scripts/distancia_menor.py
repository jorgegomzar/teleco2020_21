import math

def min_dist(arr):
	''' Calcula la minima de la distancias entre 2 puntos '''
	dist = 0
	for el1 in arr:
		for el2 in arr:
			if dist == 0 or (abs(el1 - el2) < dist and abs(el1 - el2) > 0):
				dist = abs(el1 - el2)
				print(dist)

	print('[-] Candidato a freq: {}'.format(dist))
	return dist
    
def check_freq(arr, freq):
	''' Comprueba si la freq es correcta para todas las muestras '''
	print('[-] Comprobando freq: {}'.format(freq))
	n_muestras = math.ceil(arr[-1] / freq)
	muestras = [0]
	for n in range(n_muestras):
		muestras.append(muestras[-1] + freq)
	bad = False
	for i in arr:
		if i not in muestras:
			print('Para la freq {} no se incluye la muestra ({})'.format(freq, i))
			bad = True
			break
	if not bad:
		print('[+] Frecuencia adecuada: {}'.format(freq))
	return bad
	
	
def main():
	arr = []
	while True:
		inp = input('Número: ')
		if inp == '':
			break
		arr.append(float(inp))
	print(arr)
	# Primero obtenemos el primer candidato a freq: la distancia minima entre dos deltas
	pos_freq = min_dist(arr)
	bad = False
	# Comprobamos freq
	if pos_freq > arr[0]:
		pos_freq = arr[0]
	bad = check_freq(arr, pos_freq)
	while bad:
		if bad:
			pos_freq /= 2
			bad = check_freq(arr, pos_freq)
			

if __name__ == '__main__':
	main()
