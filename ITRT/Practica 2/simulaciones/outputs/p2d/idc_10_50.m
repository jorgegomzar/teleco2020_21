mm1 = load('p2d_mm1/output_Q.csv');
mm1_teo_mean = load('mm1_teo_mean.csv');
mfallo = 0;
for i=1:100;
  % creacion muestras bootstrap
  m10 = empirical_rnd(mm1,1000,10);
  % medias muestrales en orden ascendente
  m10_mean = sort(mean(m10,2));
  %limites del intervalo de confianza
  mlim_inf = m10_mean(26); mlim_sup = m10_mean(974);
  
  if (mm1_teo_mean > mlim_inf && mm1_teo_mean < mlim_sup);
    printf(" [+] M/M/1 N=10 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mm1_teo_mean, mlim_inf, mlim_sup);
  else
    printf(" [-] M/M/1 N=10 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mm1_teo_mean, mlim_inf, mlim_sup);
    mfallo = mfallo+1;
  endif;
endfor;

printf("\n\n\nFallos M/M/1 N=10: %f  \n", (mfallo));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% N = 50
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mfallo = 0;
gfallo = 0;
for i=1:100;
  m50 = empirical_rnd(mm1, 1000, 50);
  m50_mean = sort(mean(m50,2));
  mlim_inf = m50_mean(26);
  mlim_sup = m50_mean(974);
  
  if (mm1_teo_mean > mlim_inf && mm1_teo_mean < mlim_sup);
    printf(" [+] M/M/1 N=50 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mm1_teo_mean, mlim_inf, mlim_sup);
  else
    printf(" [-] M/M/1 N=50 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mm1_teo_mean, mlim_inf, mlim_sup);
    mfallo = mfallo+1;
  endif;
  
  g50 = empirical_rnd(mg1, 1000, 50);
  g50_mean = sort(mean(g50,2));
  glim_inf = g50_mean(26);
  glim_sup = g50_mean(974);
  
  if (mg1_teo_mean > glim_inf && mg1_teo_mean < glim_sup);
    printf(" [+] M/G/1 N=50 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mg1_teo_mean, glim_inf, glim_sup);
  else
    printf(" [-] M/G/1 N=50 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mg1_teo_mean, glim_inf, glim_sup);
    gfallo = gfallo+1;
  endif; 
endfor;

printf("\n\n\n");
printf("Fallos M/M/1 N=10: %f  \n", (mfallo));
printf("Fallos M/G/1 N=10: %f  \n", (gfallo));