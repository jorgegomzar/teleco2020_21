clf;

q = load('lambda/output_Q.csv')';
lambda = load('lambda/lambda.csv')';
R = load('lambda/bitRate.csv')';
L = load('lambda/meanPacketSize.csv')';

nu = (R)./(L*8);
rho = lambda./nu;

plot(rho, q);
