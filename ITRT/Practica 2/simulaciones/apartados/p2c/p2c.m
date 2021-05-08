close all;
clear;

mtot = load('mm1/output_Q.csv');
gtot = load('mg1/output_Q.csv');
ms = size(mtot);
gs = size(gtot);
res = 50;

% N = 10
m10 = reshape(mtot(1:500),50,10);
g10 = reshape(gtot(1:500),50,10);

m10_mean = mean(m10,2);
g10_mean = mean(g10,2);

% N = 30 -> Navidi
m30 = reshape(mtot(1:1500),50,30);
g30 = reshape(gtot(1:1500),50,30);

m30_mean = mean(m30,2);
g30_mean = mean(g30,2);

% N = 50 -> Pazos
m50 = reshape(mtot(1:2500),50,50);
g50 = reshape(gtot(1:2500),50,50);

m50_mean = mean(m50,2);
g50_mean = mean(g50,2);

% N = 200 -> Rosner
m200 = reshape(mtot,50,200);
g200 = reshape(gtot,50,200);

m200_mean = mean(m200,2);
g200_mean = mean(g200,2);

% PLOTS
% N = 10
figure(1);
subplot(2,2,1);
hist(m10_mean, res);
title('M/M/1 - Histograma - M = 50 N = 10');
subplot(2,2,2);
hist(g10_mean, res);
title('M/G/1 - Histograma - M = 50 N = 10');
subplot(2,2,3);
qqplot(m10_mean);
title('M/M/1 - QQPLOT - M = 50 N = 10');
subplot(2,2,4);
qqplot(g10_mean);
title('M/G/1 - QQPLOT - M = 50 N = 10');

% N = 30
figure(2);
subplot(2,2,1);
hist(m30_mean, res);
title('M/M/1 - Histograma - M = 50 N = 30');
subplot(2,2,2);
hist(g30_mean, res);
title('M/G/1 - Histograma - M = 50 N = 30');
subplot(2,2,3);
qqplot(m30_mean);
title('M/M/1 - QQPLOT - M = 50 N = 30');
subplot(2,2,4);
qqplot(g30_mean);
title('M/G/1 - QQPLOT - M = 50 N = 30');

% N = 50
figure(3);
subplot(2,2,1);
hist(m50_mean, res);
title('M/M/1 - Histograma - M = 50 N = 50');
subplot(2,2,2);
hist(g50_mean, res);
title('M/G/1 - Histograma - M = 50 N = 50');
subplot(2,2,3);
qqplot(m50_mean);
title('M/M/1 - QQPLOT - M = 50 N = 50');
subplot(2,2,4);
qqplot(g50_mean);
title('M/G/1 - QQPLOT - M = 50 N = 50');

% N = 200
figure(4);
subplot(2,2,1);
hist(m200_mean, res);
title('M/M/1 - Histograma - M = 50 N = 200');
subplot(2,2,2);
hist(g200_mean, res);
title('M/G/1 - Histograma - M = 50 N = 200');
subplot(2,2,3);
qqplot(m200_mean);
title('M/M/1 - QQPLOT - M = 50 N = 200');
subplot(2,2,4);
qqplot(g200_mean);
title('M/G/1 - QQPLOT - M = 50 N = 200');
figure(5);
hist(m200, res);
title('Histograma: Distribución del tiempo de espera en la cola');