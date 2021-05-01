close all;
clear;
% cargamos trazas de salidas
X_mm1 = load('P2-ns-QueueingTheory-outputs_MM1.trace');
X_mg1 = load('P2-ns-QueueingTheory-outputs_MG1.trace');
% tasa de llegadas lambda=11 por defecto
lambda = 11
% Tiempos entre salidas
T_mm1 = diff(X_mm1);
T_mg1 = diff(X_mg1);

% Histogramas de los tiempos entre salidas
% M/M/1
subplot(1,2,1);
hist(T_mm1, 100);
title('Histograma: Distribución tiempos entre salidas - M/M/1');
xlabel('Frecuencia');
ylabel('Tiempo entre salidas a frecuencia X');
% M/G/1
subplot(1,2,2);
hist(T_mg1,100);
title('Histograma: Distribución tiempos entre salidas - M/G/1');
xlabel('Frecuencia');
ylabel('Tiempo entre salidas a frecuencia X');

% Comparamos con exponencial de parametro 1/lambda
figure(2);
subplot(1,2,1);
qqplot(T_mm1, 'exp', 1/lambda);
title('Modelo M/M/1');
subplot(1,2,2);
qqplot(T_mg1, 'exp', 1/lambda);
title('Modelo M/G/1');


