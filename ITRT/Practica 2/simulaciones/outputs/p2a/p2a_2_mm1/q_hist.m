clear;
close all;

mq = load('mm1_q.csv');
gq = load('mg1_q.csv');
subplot(2,1,1);
plot(mq);
subplot(2,1,2);
plot(gq);