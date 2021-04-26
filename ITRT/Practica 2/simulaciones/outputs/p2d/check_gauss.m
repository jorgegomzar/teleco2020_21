clf;

% cargamos los ficheros con las muestras
mm1_10000 = load('p2d_mm1/output_Q.csv');
mg1_10000 = load('p2d_mg1/output_Q.csv');
printf("Longitud fichero M/M/1: %d\n", length(mm1_10000));
printf("Longitud fichero M/G/1: %d\n", length(mg1_10000));

% MUESTRAS x LONGITUD
% 10 x 50
index = randperm(10000);
mm1_10000_shuf = mm1_10000(index);
mm1_10 = reshape(mm1_10000(:500), 10, 50);
size(mm1_10)

% 50 x 50


% 100 x 50


% 200 x 50

