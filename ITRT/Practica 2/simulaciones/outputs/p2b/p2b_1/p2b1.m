close all;
% cargamos traza de llegadas
X = load('P2-ns-QueueingTheory-arrivals.trace');
% tasa de llegadas lambda=11 por defecto
lambda = 11;

% Histograma de los tamaños de los paquetes de llegada
subplot(1,2,1);
hist(X(:,2),100);
title('Distribución tamaño de los paquetes');

% Histograma de los tiempos de llegada entre paquetes
T = diff(X(:,1));
subplot(1,2,2);
hist(T,100);
title('Densidad de tiempo de llegadas entre paquetes');

% Comparamos con exponencial de parametro 1/lambda
figure(2);
qqplot(T,'exp',1/lambda);
title(sprintf('Comparación de cuantiles de las llegadas con la de una distribución exponencial de 1/lambda = %f', 1/lambda));


