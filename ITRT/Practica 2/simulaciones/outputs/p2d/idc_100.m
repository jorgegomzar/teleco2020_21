clf;

% media teorica para Q segun teoria de colas
mm1_teo_mean = load('mm1_teo_mean.csv');
mg1_teo_mean = load('mg1_teo_mean.csv');

% IdC PARA 200 SIMULACIONES M/M/1
printf("M/M/1 100 simulaciones\n");
m100 = load('100_mm1.csv');
n = length(m100);

% idc del 95% -> 100(1-alpha)
alpha = 0.05;

m100_mean = mean(m100);
m100_s = sqrt(var(m100));
m100_sigma_muestral = m100_s/sqrt(n);
m100_z = stdnormal_inv(alpha/2);

lim_inf = m100_mean + m100_z * m100_sigma_muestral;
lim_sup = m100_mean - m100_z * m100_sigma_muestral;

printf(" - Limite inferior: %f\n", lim_inf);
printf(" - Limite superior: %f\n", lim_sup);

if (mm1_teo_mean <= lim_sup && mm1_teo_mean >= lim_inf)
        printf(" [+] Q promedio teorica entra dentro del IdC calculado\n");
else
        printf(" [-] Q promedio teorica NO entra dentro del IdC calculado\n");
endif

%--------------------------------------------------------------------------------

% IdC PARA 100 SIMULACIONES M/G/1
printf("M/G/1 100 simulaciones\n");
g100 = load('100_mg1.csv');
n = length(g100);

% idc del 95% -> 100(1-alpha)
alpha = 0.05;

g100_mean = mean(g100);
g100_s = sqrt(var(g100));
g100_sigma_muestral = g100_s/sqrt(n);
g100_z = stdnormal_inv(alpha/2);

lim_inf = g100_mean + g100_z * g100_sigma_muestral;
lim_sup = g100_mean - g100_z * g100_sigma_muestral;

printf(" - Limite inferior: %f\n", lim_inf);
printf(" - Limite superior: %f\n", lim_sup);

if (mm1_teo_mean <= lim_sup && mm1_teo_mean >= lim_inf)
        printf(" [+] Q promedio teorica entra dentro del IdC calculado\n");
else
        printf(" [-] Q promedio teorica NO entra dentro del IdC calculado\n");
endif

