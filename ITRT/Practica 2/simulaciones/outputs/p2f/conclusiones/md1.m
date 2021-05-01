% Comprobacion de M/D/1
clear;
close all;
% Llegadas con distrib exponencial
X = load('md1_arrivals.trace');
subplot(1,2,1);
hist(diff(X(:,1)),80);
title('Distribución tiempos entre llegadas');

% Salidas con distrib uniforme
% Teorema de Burke
subplot(1,2,2);
plot(X(:,2));
title('Distribución tamaños paquetes');
