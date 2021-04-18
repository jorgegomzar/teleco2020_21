close all;
XM=load('P3-ns-QueueingTheory-outputs_MM1.trace');
XG=load('P3-ns-QueueingTheory-outputs_MG1.trace');
TG=diff(XG);
TM=diff(XM);
figure(1)
subplot(1,2,1)
hist(TM,100);
title('densidad de las salidas del modeo MM1');
subplot(1,2,2);
hist(TG,100);
title('densidad de las salidas del modelo MG1');