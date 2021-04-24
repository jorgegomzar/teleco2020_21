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
	printf(" [+] Q promedio teorica entra dentro del IdC calculado (%f)\n", mm1_teo_mean);
else
	printf(" [-] Q promedio teorica NO entra dentro del IdC calculado (%f)\n", mg1_teo_mean);
endif

% --------------------------------------------------------

% IdC PARA 200 SIMULACIONES M/M/1
printf("M/G/1 200 simulaciones\n");
g200 = load('200_mg1.csv');
n = length(g200);

% idc del 95% -> 100(1-alpha)
alpha = 0.05;

g200_mean = mean(g200);
g200_s = sqrt(var(g200));
g200_sigma_muestral = g200_s/sqrt(n);
g200_z = stdnormal_inv(alpha/2);

lim_inf = g200_mean + g200_z * g200_sigma_muestral;
lim_sup = g200_mean - g200_z * g200_sigma_muestral;

printf(" - Limite inferior: %f\n", lim_inf);
printf(" - Limite superior: %f\n", lim_sup);

if (mg1_teo_mean <= lim_sup && mg1_teo_mean >= lim_inf)
        printf(" [+] Q promedio teorica entra dentro del IdC calculado (%f)\n", mg1_teo_mean);
else
        printf(" [-] Q promedio teorica NO entra dentro del IdC calculado (%f)\n", mg1_teo_mean);
endif

