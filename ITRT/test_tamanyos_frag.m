%
% Demostracion ejercicio 11.b - Jorge
%

clc;
clear;
close all;
% si en Octave os dice que exprnd no puede usarse descomentad esta linea:
%pkg load statistics;

% Una muestra de longitud N, distribucion exponencial de media 1/lambda
N = 1000000;
lambda = 1/1000;
X = exprnd(1/lambda, N,1);

% Para visualizar la distribucion
% hist(X,128);

% Probabilidad de fragmentacion (L > 1472 Bytes): 0.23
X_frag = sum(X > 1472); % sumo nº de PDU superiores a 1472
P_frag = X_frag/N; % la probabilidad sera el ratio: PDU fragmentadas/PDU totales

fprintf('[P_nofrag] - %f (Probabilidad de no fragmentación)\n', 1-P_frag); % 1-P_frag = P_nofrag: 0.77
fprintf('[P_frag] - %f (Probabilidad de fragmentación)\n', P_frag);

% Ahora voy a calcular el tamaño promedio para las fragmentadas y las no fragmentadas
% Tamaño medio PDU que no se fragmentan
L_no_frag_medio = ((X <= 1472)'*X)/(N-X_frag); % sumo los tamaños de las PDU no fragmentadas y promedio

% Tamaño medio PDU que se van a fragmentar
L_frag_medio = ((X > 1472)'*X)/X_frag; % sumo los tamaños de las PDU fragmentadas y promedio

fprintf('[L_nofrag] - %f (Tamaño promedio de PDU que no se fragmentan)\n', L_no_frag_medio);
fprintf('[L_frag] - %f (Tamaño promedio de PDU que se fragmentan)\n', L_frag_medio);

% Tamaño promedio de tramas con cabeceras: L? + 8 (UDP) + 20 (IP) + 18 (Ethernet)
% L1 -> Tamaño medio tramas no fragmentadas: 606,31 Bytes
L1 = ((X <= 1472)'*X)/(N - X_frag) + 8 + 20 + 18; % tamaño promedio PDU que no se fragmentan + cabeceras UDP, IP y Ethernet

% L2 -> Tamaño medio tramas fragmentadas (primer fragmento): 1518 Bytes
L2 = 1472 + 8 + 20 + 18; % tamaño promedio del primer fragmento de las PDU que se fragmentan + cabeceras UDP, IP y Ethernet

% L3 -> Tamaño medio tramas fragmentadas (segundo fragmento): 1038 Bytes
L3 = ((X > 1472)'*(X-1472))/X_frag + 20 + 18; % tamaño promedio del segundo fragmento de las PDU que se fragmentan + cabeceras IP y Ethernet

fprintf('[L1] - %f (Tamaño medio tramas no fragmentadas)\n', L1);
fprintf('[L2] - %f (Tamaño medio tramas fragmentadas (primer fragmento))\n', L2);
fprintf('[L3] - %f (Tamaño medio tramas no fragmentadas (segundo fragmento))\n', L3);

% LO NUEVO: tamaño medio de las tramas
N_tramas = sum(X <= 1472) + 2*sum(X > 1472);
L_tramas = ((X <= 1472)'*X+sum(X <= 1472)*(8+20+18) + sum(X > 1472)*(1472+8+20+18) + (X > 1472)'*(X-1472)+sum(X > 1472)*(20+18))/N_tramas;
fprintf('[L_tramas] - %f (Tamaño medio tramas)\n', L_tramas);


