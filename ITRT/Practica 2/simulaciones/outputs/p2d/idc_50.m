clf;

% media teorica para Q segun teoria de colas
mm1_teo_mean = load('mm1_teo_mean.csv');
mg1_teo_mean = load('mg1_teo_mean.csv');

% IdC PARA 50 SIMULACIONES M/M/1
printf("M/M/1 50 simulaciones\n");
m50 = load('50_mm1.csv');
n = length(m50);

% idc del 95% -> 100(1-alpha)
alpha = 0.05;

m50_mean = mean(m50);
m50_s = sqrt(var(m50));
m50_sigma_muestral = m50_s/sqrt(n);
m50_z = stdnormal_inv(alpha/2);

lim_inf = m50_mean + m50_z * m50_sigma_muestral;
lim_sup = m50_mean - m50_z * m50_sigma_muestral;

printf(" - Limite inferior: %f\n", lim_inf);
printf(" - Limite superior: %f\n", lim_sup);

if (mm1_teo_mean <= lim_sup && mm1_teo_mean >= lim_inf)
        printf(" [+] Q promedio teorica entra dentro del IdC calculado\n");
else
        printf(" [-] Q promedio teorica NO entra dentro del IdC calculado\n");
endif

%----------------------------------------------------------------------------------

clf;

% IdC PARA 50 SIMULACIONES M/G/1
printf("M/G/1 50 simulaciones\n");
m50 = load('50_mg1.csv');
n = length(g50);

% idc del 95% -> 100(1-alpha)
alpha = 0.05;

g50_mean = mean(g50);
g50_s = sqrt(var(g50));
g50_sigma_muestral = g50_s/sqrt(n);
g50_z = stdnormal_inv(alpha/2);

lim_inf = g50_mean + g50_z * g50_sigma_muestral;
lim_sup = g50_mean - g50_z * g50_sigma_muestral;

printf(" - Limite inferior: %f\n", lim_inf);
printf(" - Limite superior: %f\n", lim_sup);

if (mm1_teo_mean <= lim_sup && mm1_teo_mean >= lim_inf)
        printf(" [+] Q promedio teorica entra dentro del IdC calculado\n");
else
        printf(" [-] Q promedio teorica NO entra dentro del IdC calculado\n");
endif

