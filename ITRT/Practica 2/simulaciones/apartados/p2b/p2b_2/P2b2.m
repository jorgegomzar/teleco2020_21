X_mm1 = load('P2-ns-QueueingTheory-outputs_MM1.trace');
X_mg1 = load('P2-ns-QueueingTheory-outputs_MG1.trace');
mu = (8*1000)/100000;
T_mm1 = diff(X_mm1); T_mg1 = diff(X_mg1);
% Histogramas de los tiempos entre salidas
figure(1);
hist(T_mm1, 100); % M/M/1
title('Histograma: Distribución tiempos entre salidas - M/M/1');
xlabel('Frecuencia'); ylabel('Tiempo entre salidas a frecuencia X');
figure(2);
hist(T_mg1,100); % M/G/1
title('Histograma: Distribución tiempos entre salidas - M/G/1');
xlabel('Frecuencia'); ylabel('Tiempo entre salidas a frecuencia X');
% Comparamos con exponencial de parametro mu
figure(3); qqplot(T_mm1, 'exp', mu); % M/M/1
title('Modelo M/M/1');
figure(4); qqplot(T_mg1, 'exp', mu); % M/G/1
title('Modelo M/G/1');


