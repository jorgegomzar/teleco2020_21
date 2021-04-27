
mm1 = load('p2d_mm1/output_Q.csv');
mg1 = load('p2d_mg1/output_Q.csv');
mm1_teo_mean = load('mm1_teo_mean.csv');
mg1_teo_mean = load('mg1_teo_mean.csv');

mfallo = 0;
gfallo = 0;
for i=1:100;
  m10 = [];
  g10 = [];
  for j=1:1000;
    index = randperm(10000);
    mm1_shuf = mm1(index);
    mg1_shuf = mg1(index);
    m10 = [m10; mm1_shuf(1:10)];
    g10 = [g10; mg1_shuf(1:10)];
  endfor;
  m10 = reshape(m10, 10, 1000);
  g10 = reshape(g10, 10, 1000);

  m10_mean = sort(mean(m10));
  g10_mean = sort(mean(g10));

  m10_final = m10_mean(1:1000-25);
  m10_final = m10_final(25:end);
  mlim_inf = m10_final(1);
  mlim_sup = m10_final(end);

  g10_final = g10_mean(1:1000-25);
  g10_final = g10_final(25:end);
  glim_inf = g10_final(1);
  glim_sup = g10_final(end);

  if (mm1_teo_mean > mlim_inf && mm1_teo_mean < mlim_sup);
    printf(" [+] M/M/1 N=10 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mm1_teo_mean, mlim_inf, mlim_sup);
  else
    printf(" [-] M/M/1 N=10 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mm1_teo_mean, mlim_inf, mlim_sup);
    mfallo = mfallo +1;
  endif;

  if (mg1_teo_mean > glim_inf && mg1_teo_mean < glim_sup);
    printf(" [+] M/G/1 N=10 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mg1_teo_mean, glim_inf, glim_sup);
  else
    printf(" [-] M/G/1 N=10 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mg1_teo_mean, glim_inf, glim_sup);
    gfallo = gfallo +1;
  endif; 
endfor;

printf("\n\n\n");
printf("Acierto M/M/1 N=10: %f  \n", (100-mfallo));
printf("Acierto M/G/1 N=10: %f  \n", (100-gfallo));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% N = 50
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

mfallo = 0;
gfallo = 0;
for i=1:100;
  m50 = [];
  g50 = [];
  for j=1:1000;
    index = randperm(10000);
    mm1_shuf = mm1(index);
    mg1_shuf = mg1(index);
    m50 = [m50; mm1_shuf(1:50)];
    g50 = [g50; mg1_shuf(1:50)];
  endfor;
  
  m50 = reshape(m50, 50, 1000);
  g50 = reshape(g50, 50, 1000);

  m50_mean = sort(mean(m50));
  g50_mean = sort(mean(g50));

  m50_final = m50_mean(1:1000-25);
  m50_final = m50_final(25:end);
  mlim_inf = m50_final(1);
  mlim_sup = m50_final(end);

  g50_final = g50_mean(1:1000-25);
  g50_final = g50_final(25:end);
  glim_inf = g50_final(1);
  glim_sup = g50_final(end);

  if (mm1_teo_mean > mlim_inf && mm1_teo_mean < mlim_sup);
    printf(" [+] M/M/1 N=50 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mm1_teo_mean, mlim_inf, mlim_sup);
  else
    printf(" [-] M/M/1 N=50 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mm1_teo_mean, mlim_inf, mlim_sup);
    mfallo = mfallo +1;
  endif;

  if (mg1_teo_mean > glim_inf && mg1_teo_mean < glim_sup);
    printf(" [+] M/G/1 N=50 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mg1_teo_mean, glim_inf, glim_sup);
  else
    printf(" [-] M/G/1 N=50 -> teo: %f, lim_inf: %f, lim_sup: %f\n", mg1_teo_mean, glim_inf, glim_sup);
    gfallo = gfallo +1;
  endif; 
endfor;

printf("\n\n\n");
printf("Acierto M/M/1 N=50: %f  \n", (100-mfallo));
printf("Acierto M/G/1 N=50: %f  \n", (100-gfallo));