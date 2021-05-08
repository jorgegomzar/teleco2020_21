# M/M/1 mPS -> --fixedlength=0 --tracing=1 --tmax=10000
a200  = load('200_arrivals.trace');
a500  = load('500_arrivals.trace');
a1000 = load('1000_arrivals.trace');
a1200 = load('1200_arrivals.trace');
a1400 = load('1400_arrivals.trace');

x = [200 500 1000 1200 1400];
y = sum(a200(:,2) > 1472);
y = [y sum(a500(:,2) > 1472)];
y = [y sum(a1000(:,2) > 1472)];
y = [y sum(a1200(:,2) > 1472)];
y = [y sum(a1400(:,2) > 1472)];

figure(1);
stairs(x,y);
title('Fragmentación');
xlabel('MeanPacketSize');
ylabel('Paquetes fragmentados');

# Calculo de probabilidad
t = length(a200(:,2));
t = [t length(a500(:,2))];
t = [t length(a1000(:,2))];
t = [t length(a1200(:,2))];
t = [t length(a1400(:,2))];
p = y./t;
figure(2);
plot(x,p, "*", "markersize", 20);
title('Probabilidad de fragmentación');
xlabel('MeanPacketSize');
ylabel('Probabilidad');