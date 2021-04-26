clf;

% cargamos los ficheros con las muestras
mm1_10000 = load('p2d_mm1/output_Q.csv');
mg1_10000 = load('p2d_mg1/output_Q.csv');
printf("Longitud M/M/1: %d", length(mm1_10000));
printf("Longitud M/G/1: %d", length(mg1_10000));

