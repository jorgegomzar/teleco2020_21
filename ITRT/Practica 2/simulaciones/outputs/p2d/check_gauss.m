clf;

% cargamos los ficheros con las muestras
mm1_10000 = load('p2d_mm1/output_Q.csv');
mg1_10000 = load('p2d_mg1/output_Q.csv');
%printf("Longitud fichero M/M/1: %d\n", length(mm1_10000));
%printf("Longitud fichero M/G/1: %d\n", length(mg1_10000));

% MUESTRAS x LONGITUD -> hallamos medias muestrales
% 10 x 50
index = randperm(10000);
mm1_10000_shuf = mm1_10000(index);
mg1_10000_shuf = mg1_10000(index);

mm1_10 = reshape(mm1_10000_shuf(1:500), 10, 50);
mm1_10_mean = mean(mm1_10);

mg1_10 = reshape(mg1_10000_shuf(1:500), 10, 50);
mg1_10_mean = mean(mg1_10);

% 50 x 50
index = randperm(10000);
mm1_10000_shuf = mm1_10000(index);
mg1_10000_shuf = mg1_10000(index);

mm1_50 = reshape(mm1_10000_shuf(1:2500), 50, 50);
mm1_50_mean = mean(mm1_50);

mg1_50 = reshape(mg1_10000_shuf(1:2500), 50, 50);
mg1_50_mean = mean(mg1_50);

% 100 x 50
index = randperm(10000);
mm1_10000_shuf = mm1_10000(index);
mg1_10000_shuf = mg1_10000(index);

mm1_100 = reshape(mm1_10000_shuf(1:5000), 100, 50);
mm1_100_mean = mean(mm1_100);

mg1_100 = reshape(mg1_10000_shuf(1:5000), 100, 50);
mg1_100_mean = mean(mg1_100);

% 200 x 50
index = randperm(10000);

mm1_200 = reshape(mm1_10000(index), 200, 50);
mm1_200_mean = mean(mm1_200);

mg1_200 = reshape(mg1_10000(index), 200, 50);
mg1_200_mean = mean(mg1_200);

% ahora que tenemos todas las medias muestrales para 10, 50, 100 y 200
% visualizamos las boxplot en busca de outliers y asimetrias
figure(1);
subplot(2,2,1);
boxplot(mm1_10_mean);
title("M/M/1 -> 10 simulaciones");

subplot(2,2,2);
boxplot(mm1_50_mean);
title("M/M/1 -> 50 simulaciones");

subplot(2,2,3);
boxplot(mm1_100_mean);
title("M/M/1 -> 100 simulaciones");

subplot(2,2,4);
boxplot(mm1_200_mean);
title("M/M/1 -> 200 simulaciones");

figure(2);
subplot(2,2,1);
boxplot(mg1_10_mean);
title("M/G/1 -> 10 simulaciones");

subplot(2,2,2);
boxplot(mg1_50_mean);
title("M/G/1 -> 50 simulaciones");

subplot(2,2,3);
boxplot(mg1_100_mean);
title("M/G/1 -> 100 simulaciones");

subplot(2,2,4);
boxplot(mg1_200_mean);
title("M/G/1 -> 200 simulaciones");
