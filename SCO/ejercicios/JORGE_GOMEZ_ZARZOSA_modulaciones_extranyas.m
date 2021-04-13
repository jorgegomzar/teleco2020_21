% Formato grafica y ejes
hold on
x = linspace(-2.5,2.5);
plot(x, zeros(100), 'b--')
plot(zeros(100), x, 'b--')
title('Generación de constelaciones “extrañas” con un transmisor QPSK')
xlabel('FASE - cos(wt)') 
ylabel('CUADRATURA - sin(wt)')

% Lo importante
volts = [ 0 pi/2 pi ];
cons = []; % la constelacion
senos = []; % contribuciones en cuadratura
cosenos = []; % contribuciones en fase

% calculo en el plano complejo los posibles desfases para el coseno y el
% seno
for V = volts
    cosenos = [cosenos exp(1i*V)];
    senos = [senos exp(1i*(V+pi/2))];
end

% formo la constelacion
for seno = senos
    for coseno = cosenos
        cons = [cons coseno + seno];
    end
end

% grafico
plot(real(cons), imag(cons), 'r*')   % plot simbolos
for simb = cons
    plot(real([0 simb]), imag([0 simb]), 'g')   % plot vectores
end

