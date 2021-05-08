% Comprobacion de M/M/1
clear;
close all;
% Llegadas con distrib exponencial
X = load('mm1_arrivals.trace');
subplot(1,2,1);
hist(diff(X(:,1)),80);
title('Distribución tiempos entre llegadas');

% Salidas con distrib exponencial
% Teorema de Burke
subplot(1,2,2);
hist(X(:,2),80);
title('Distribución tamaños paquetes');
