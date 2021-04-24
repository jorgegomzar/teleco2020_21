close all;
X = load('P2-ns-QueueingTheory-arrivals.trace');
N = length(X);

% Distribución exponencial de los tamaños de los paquetes
subplot(1,2,1);
hist(X(:,2),100);
title('Distribución tamaño de los paquetes');

% Calculamos la diferencia entre los tiempos de llegada de los paquetes
T = diff(X(:,1));
subplot(1,2,2);
hist(T,100);
title('Densidad de tiempo de llegadas entre paquetes');

% Calculamos la media del tiempo de llegadas y la tasa de llegadas lambda
T_mean = mean(T);
lambda = 1/T_mean;

% Comparamos con exponencial de parametro lambda = 1.093 * 10^-8
figure(2);
qqplot(T,'exp',lambda);
%plot(ones(100), ones(100));
title(sprintf('Comparación de cuantiles de las llegadas con la de una distribución exponencial de lambda = %f', lambda));
