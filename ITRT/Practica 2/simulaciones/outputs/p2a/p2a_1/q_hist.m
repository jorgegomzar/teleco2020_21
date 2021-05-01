clf;

m10 = load('mm1_10.csv');
m100 = load('mm1_100.csv');

g10 = load('mg1_10.csv');
g100 = load('mg1_100.csv');

subplot(2,2,1);
hist(m10,100);
subplot(2,2,2);
hist(m100,100);

subplot(2,2,3);
hist(g10,100);
subplot(2,2,4);
hist(g100,100);
