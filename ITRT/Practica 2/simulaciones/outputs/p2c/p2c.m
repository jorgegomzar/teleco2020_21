clear;

m = load('mm1/output_Q.csv');
g = load('mg1/output_Q.csv');
m = reshape(m,20,100);
g = reshape(g,20,100);

m_mean = mean(m,2);
g_mean = mean(g,2);

subplot(2,2,1);
hist(m_mean, 16);
title('M/M/1 - Histograma - M = 20 N = 100');
subplot(2,2,2);
hist(g_mean, 16);
title('M/G/1 - Histograma - M = 20 N = 100');

subplot(2,2,3);
qqplot(m_mean);
title('M/M/1 - QQPLOT - M = 20 N = 100');
subplot(2,2,4);
qqplot(g_mean);
title('M/G/1 - QQPLOT - M = 20 N = 100');

m = load('mm1/output_Q.csv');
g = load('mg1/output_Q.csv');
m = reshape(m,100,20);
g = reshape(g,100,20);

m_mean = mean(m,2);
g_mean = mean(g,2);

figure(2);
subplot(2,2,1);
hist(m_mean, 16);
title('M/M/1 - Histograma - M = 100 N = 20');
subplot(2,2,2);
hist(g_mean, 16);
title('M/G/1 - Histograma - M = 100 N = 20');

subplot(2,2,3);
qqplot(m_mean);
title('M/M/1 - QQPLOT - M = 100 N = 20');
subplot(2,2,4);
qqplot(g_mean);
title('M/G/1 - QQPLOT - M = 100 N = 20');


% compromiso MxN