q = load('output_Q.csv');
q = reshape(q,200,10);

for i=1:size(q)(1);
	q_mean = mean(q(i,:));
	q_means(i) = q_mean;
endfor;

subplot(1,2,1);
hist(q_means, 100);

subplot(1,2,2);
qqplot(q_means);
