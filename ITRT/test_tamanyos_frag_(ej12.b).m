clf;
clear;
close all;

N = 1000000;
lambda = 1/1000; % 1000 de tamaño medio
X = exprnd(1/lambda, N,1);

%hist(X,128);

% Probabilidad de fragmentacion (L > 1472 Bytes): 0.22
X_frag = sum(X > 1472)';
prob_frag = X_frag/N;

printf('[P_nofrag] - %f (Probabilidad de no fragmentación)\n', 1-prob_frag);
printf('[P_frag] - %f (Probabilidad de fragmentación)\n', prob_frag);


% Tamaño medio PDU que no se fragmentan
L_no_frag_medio = ((X <= 1472)'*X)/(N-X_frag);

% Tamaño medio PDU que se van a fragmentar
L_frag_medio = ((X > 1472)'*X)/X_frag;

printf('[L_nofrag] - %f (Tamaño promedio de UDP que no se fragmentan)\n', L_no_frag_medio);
printf('[L_frag] - %f (Tamaño promedio de UDP que se fragmentan)\n', L_frag_medio);

% Tamaño promedio de tramas con cabeceras: L? + 8 (UDP) + 20 (IP) + 18 (Ethernet)
% L1 -> Tamaño medio tramas no fragmentadas
L1 = ((X <= 1472)'*X)/(N - X_frag) + 8 + 20 + 18;

% L2 -> Tamaño medio tramas fragmentadas (max)
L2 = 1472 + 8 + 20 + 18;

% L3 -> Tamaño medio tramas fragmentadas (resto)
L3 = ((X > 1472)'*(X-1472))/X_frag + 20 + 18;

printf('[L1] - %f (Tamaño medio tramas no fragmentadas)\n', L1);
printf('[L2] - %f (Tamaño medio tramas fragmentadas (primer fragmento))\n', L2);
printf('[L3] - %f (Tamaño medio tramas no fragmentadas (segundo fragmento))\n', L3);