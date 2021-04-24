clf;

% media teorica para Q segun teoria de colas
mm1_teo_mean = load('mm1_teo_mean.csv');
mg1_teo_mean = load('mg1_teo_mean.csv');

% IdC PARA 200 SIMULACIONES M/M/1
printf("M/M/1 200 simulaciones\n");
m200 = load('200_mm1.csv');
n = length(m200);

% idc del 95% -> 100(1-alpha)
alpha = 0.05;

m200_mean = mean(m200);
m200_s = sqrt(var(m200));
m200_sigma_muestral = m200_s/sqrt(n);
m200_z = stdnormal_inv(alpha/2);

lim_inf = m200_mean + m200_z * m200_sigma_muestral;
lim_sup = m200_mean - m200_z * m200_sigma_muestral;

printf(" - Limite inferior: %f\n", lim_inf);
printf(" - Limite superior: %f\n", lim_sup);

if (mm1_teo_mean <= lim_sup && mm1_teo_mean >= lim_inf)
	printf(" [+] Q promedio teorica entra dentro del IdC calculado\n");
else
	printf(" [-] Q promedio teorica NO entra dentro del IdC calculado\n");
endif

% --------------------------------------------------------
