close all;
X_mm1 = load('P2-ns-QueueingTheory-outputs_MM1.trace');
X_mg1 = load('P2-ns-QueueingTheory-outputs_MG1.trace');
% Tiempos de llegada entre paquetes
T_mm1 = diff(X_mm1);
T_mg1 = diff(X_mg1);

% 1 - Graficamos las distribuciones de los tiempos de llegada
figure(1);
subplot(1,2,1);
hist(T_mm1, 128);
title('Modelo M/M/1');
subplot(1,2,2);
hist(T_mg1,128);
title('Modelo M/G/1');

% 2 - QQPLOT
% Hallamos las medias
T_mm1_mean = mean(T_mm1);
T_mg1_mean = mean(T_mg1);
% Calculamos las lambdas (tasa de llegadas)
lambda1 = 1/T_mm1_mean
lambda2 = 1/T_mg1_mean

% Graficamos los qqplot para ambos modelos
figure(2);
subplot(1,2,1);
qqplot(T_mm1, 'exp', lambda1);
title('Modelo M/M/1');
subplot(1,2,2);
qqplot(T_mg1, 'exp', lambda2);
title('Modelo M/G/1');
