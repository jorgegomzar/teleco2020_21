clf;
% media teorica para Q segun teoria de colas
mm1_teo_mean = load('mm1_teo_mean.csv');
mg1_teo_mean = load('mg1_teo_mean.csv');
% idc del 95% -> 100(1-alpha)
alpha = 0.05;

mm1 = load('p2d_mm1/output_Q.csv');
mg1 = load('p2d_mg1/output_Q.csv');

printf("#######################################################\n");
printf("N = 200\n");
printf("#######################################################\n");

mfallo200 = 0
gfallo200 = 0
% IdC PARA 200 SIMULACIONES -> Tma del lim central
for i=1:50;
  index = randperm(10000);
  mm1_shuf = mm1(index);
  mg1_shuf = mg1(index);

  m200 = mm1_shuf(1:200);
  m200_mean = mean(m200);
  m200_s = sqrt(var(m200));
  m200_sigma_muestral = m200_s/sqrt(200);
  m200_z = stdnormal_inv(alpha/2);

  g200 = mg1_shuf(1:200);
  g200_mean = mean(g200);
  g200_s = sqrt(var(g200));
  g200_sigma_muestral = g200_s/sqrt(200);
  g200_z = stdnormal_inv(alpha/2);

  % limites M/M/1
  lim_inf = m200_mean + m200_z * m200_sigma_muestral;
  lim_sup = m200_mean - m200_z * m200_sigma_muestral;

  if (mm1_teo_mean <= lim_sup && mm1_teo_mean >= lim_inf)
    printf(" [+] M/M/1 teo: %f, inf: %f, sup: %f\n", mm1_teo_mean, lim_inf, lim_sup);
  else
    printf(" [-] M/M/1 teo: %f, inf: %f, sup: %f\n", mm1_teo_mean, lim_inf, lim_sup);
    mfallo200 = mfallo200 + 1;
  endif

  % limites M/G/1
  lim_inf = g200_mean + g200_z * g200_sigma_muestral;
  lim_sup = g200_mean - g200_z * g200_sigma_muestral;

  if (mg1_teo_mean <= lim_sup && mg1_teo_mean >= lim_inf)
    printf(" [+] M/G/1 teo: %f, inf: %f, sup: %f\n", mg1_teo_mean, lim_inf, lim_sup);
  else
    printf(" [-] M/G/1 teo: %f, inf: %f, sup: %f\n", mg1_teo_mean, lim_inf, lim_sup);
    mfallo200 = mfallo200 + 1;
  endif
endfor;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% IdC PARA 100 SIMULACIONES -> Tma del lim central
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

printf("#######################################################\n");
printf("N = 100\n");
printf("#######################################################\n");

mfallo100 = 0;
gfallo100 = 0;
for i=1:50;
  index = randperm(10000);
  mm1_shuf = mm1(index);
  mg1_shuf = mg1(index);

  m100 = mm1_shuf(1:100);
  m100_mean = mean(m100);
  m100_s = sqrt(var(m100));
  m100_sigma_muestral = m100_s/sqrt(100);
  m100_z = stdnormal_inv(alpha/2);

  g100 = mg1_shuf(1:100);
  g100_mean = mean(g100);
  g100_s = sqrt(var(g100));
  g100_sigma_muestral = g100_s/sqrt(100);
  g100_z = stdnormal_inv(alpha/2);

  % limites M/M/1
  lim_inf = m100_mean + m100_z * m100_sigma_muestral;
  lim_sup = m100_mean - m100_z * m100_sigma_muestral;

  if (mm1_teo_mean <= lim_sup && mm1_teo_mean >= lim_inf)
    printf(" [+] M/M/1 teo: %f, inf: %f, sup: %f\n", mm1_teo_mean, lim_inf, lim_sup);
  else
    printf(" [-] M/M/1 teo: %f, inf: %f, sup: %f\n", mm1_teo_mean, lim_inf, lim_sup);
    mfallo100 = mfallo100 +1;
  endif

  % limites M/G/1
  lim_inf = g100_mean + g100_z * g100_sigma_muestral;
  lim_sup = g100_mean - g100_z * g100_sigma_muestral;

  if (mg1_teo_mean <= lim_sup && mg1_teo_mean >= lim_inf)
    printf(" [+] M/G/1 teo: %f, inf: %f, sup: %f\n", mg1_teo_mean, lim_inf, lim_sup);
  else
    printf(" [-] M/G/1 teo: %f, inf: %f, sup: %f\n", mg1_teo_mean, lim_inf, lim_sup);
    gfallo100 = gfallo100 +1;
  endif
endfor;

printf("\n\n");
printf("Acierto M/M/1 N=200: %f\n", (50-mfallo200)/50*100);
printf("Acierto M/M/1 N=100: %f\n", (50-mfallo100)/50*100);
printf("Acierto M/G/1 N=200: %f\n", (50-gfallo200)/50*100);
printf("Acierto M/G/1 N=100: %f\n", (50-gfallo100)/50*100);