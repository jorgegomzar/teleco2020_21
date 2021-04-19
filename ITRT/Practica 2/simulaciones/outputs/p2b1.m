close all;
X=load('P3-ns-QueueingTheory-arrivals.trace');
figure(1)
%Comprobamos que los tama�os de los paquetes estan distribuidos exponencialmente
hist(X(:,2),100);
title('Densidad del tama�o de los paquetes');
%calculamos la diferencia entre los tiempos de llegada de llos paquetes
T=diff(X(:,1));
figure(2)
hist(T,100);
title('Densidad de la diferencia del tiempo de llegada entre paquetes');
%Comparamos la funcion de densidad con la exponencial de valor lambda 9
figure(3)
qqplot(T,'exp',9);