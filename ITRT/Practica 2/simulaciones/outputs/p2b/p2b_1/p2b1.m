close all;
clear;

% cargamos traza de llegadas
X = load('P2-ns-QueueingTheory-arrivals.trace');
% tasa de llegadas lambda=11 por defecto
lambda = 11;

% Histograma de los tamaños de los paquetes de llegada
subplot(1,2,1);
hist(X(:,2),100);
title('Histograma: Distribución tamaño de los paquetes');
xlabel('Frecuencia');
ylabel('Tamaño de paquetes a frecuencia X');

% Histograma de los tiempos de llegada entre paquetes
T = diff(X(:,1));
subplot(1,2,2);
hist(T,100);
title('Histograma: Distribución tiempo entre  llegadas de paquetes');
xlabel('Frecuencia');
ylabel('Tiempo entre llegadas a frecuencia X');

% Comparamos con exponencial de parametro 1/lambda
figure(2);
qqplot(T,'exp', 1/lambda);
title(sprintf('Comparación de cuantiles de los tiempos entre llegadas con la de una distribución exponencial de 1/lambda = %f', 1/lambda));


