clear;
close all;
clf;

% cargamos los ficheros con las muestras
mm1_10000 = load('p2d_mm1/output_Q.csv');
mg1_10000 = load('p2d_mg1/output_Q.csv');

% N = 10
index = randperm(10000);
mm1_10000_shuf = mm1_10000(index);
mg1_10000_shuf = mg1_10000(index);
mm1_10 = mm1_10000_shuf(1:10);
mg1_10 = mg1_10000_shuf(1:10);

% N = 50
index = randperm(10000);
mm1_10000_shuf = mm1_10000(index);
mg1_10000_shuf = mg1_10000(index);
mm1_50 = mm1_10000_shuf(1:50);
mg1_50 = mg1_10000_shuf(1:50);

% N = 100
index = randperm(10000);
mm1_10000_shuf = mm1_10000(index);
mg1_10000_shuf = mg1_10000(index);
mm1_100 = mm1_10000_shuf(1:100);
mg1_100 = mg1_10000_shuf(1:100);

% N = 200
index = randperm(10000);
mm1_10000_shuf = mm1_10000(index);
mg1_10000_shuf = mg1_10000(index);
mm1_200 = mm1_10000_shuf(1:200);
mg1_200 = mg1_10000_shuf(1:200);
% ahora que tenemos todas las medias muestrales para 10, 50, 100 y 200
% visualizamos las boxplot en busca de outliers y asimetrias
figure(1);
subplot(2,1,1);
boxplot(mm1_10);
title("M/M/1 -> 10 simulaciones");

subplot(2,1,2);
boxplot(mm1_50);
title("M/M/1 -> 50 simulaciones");

figure(2);
subplot(2,1,1);
boxplot(mg1_10);
title("M/G/1 -> 10 simulaciones");

subplot(2,1,2);
boxplot(mg1_50);
title("M/G/1 -> 50 simulaciones");