# barrido lambda 0 - 0.5 - 12.5
import os

def gen_sims(lambda_arr, n_f):
	sim_cli = ''
	os.system('echo "" > ' + n_f)
	for i in lambda_arr:
		print("Lambda: " + str(i) )
		seed = i*2
		sim_cli = '../queue-mm1-mg1 --tmax=10000 --rep=' + str(seed) + ' --lambda='+ str(i) +' >> ' + n_f
#		print(sim_cli)
		os.system(sim_cli)

lambda_i = 0.5
lambda_f = 12.5
step = 0.1

lambda_arr = []
n_f = 'mm1_barrido_lambda.csv'

# genero el vector de lambdas
for i in range(int((lambda_f-lambda_i)/step)+1):
	lambda_arr.append(round((i+lambda_i)*step,2))
# generar las simulaciones
gen_sims(lambda_arr, n_f)

