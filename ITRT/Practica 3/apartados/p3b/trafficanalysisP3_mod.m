% ITRT, P3
% Visualization of generated traffic (s1), received traffic (s2) and dropped
% traffic at r1 as regulated by the policing strategy employed (e.g. tocket bucket)
% NOTE: only dropped packets are considered (i.e. if the policy is marking the
% packets with a different traffic class, these packets are not displayed)
%
% Author: Juan I. Asensio-Perez
% ETSIT Telecomununicacion, Universidad de Valladolid, Spain
% 29-april-2014
% Last updated 17-may-2018


clf;


%How many plots will be displayed?
global plotx;
global ploty;


%Function that generates a bitrate/time plot from a trace of (time, packet_size)
%	resolution: is the time columns in the trace file in seconds, miliseconds, ...? (e.g.: resolution=1e9 => nanoseconds)
%	step: size of the time slot in which the traffic is aggregated
function plottraffic(data, plotposition, mytitle, mycolor, resolution, step)

	global plotx;
	global ploty;

	l=length(data);
	tmax=data(l,1);
	steps=(tmax/resolution)/step;

	traffic=0;
	traffictime=0;
	index=1;
	indexprev=1;
	for i=1:steps
   	    index=lookup(data(:,1),i*step*resolution);
		if(index==0) 
			dropstraffic(i)=0;
			indexprev=1;
		else 
      aggr = sum(data(indexprev+1:index,2)); %indexprev+1 in order not to sum the same datagran twice...
			if(i==1) %first "step" (time interval from t=0)
				timeaggr = (data(index,1))/resolution;
			else
				timeaggr = (data(index,1)-data(indexprev,1))/resolution;
			endif
			if(timeaggr!=0)
				dropstraffic(i)=(aggr*8)/timeaggr/1000; %Kbps
			else
				dropstraffic(i)=0; %when there are no data points in that step (e.g., for traces of dropped packets)
			endif
			indexprev=index;
		endif
        dropstime(i)=i*step;
	end

	bytessent = sum(data(:,2));
	averagetraffic = ((bytessent*8)/(tmax/resolution))/1000; %Kbits per second
	subplot(plotx,ploty,plotposition);
	plot(dropstime,dropstraffic,"color",mycolor);
	title(sprintf("%s\n Average bitrate: %f Kbps", mytitle, averagetraffic));
	xlabel("Time (sec.)");
	ylabel("Kbps");


endfunction


plotx=2;
ploty=4;
step=10; %sec (integration interval)
resolution=1e9; %times in traces are in nanoseconds...


%GENERATED TRAFFIC AT s1
try
	s1data=load('P3-DiffServ-s1-arrivals.trace');
	plottraffic(s1data, 1, "TRAFFIC GENERATED AT s1", "black", resolution, step);
catch
        warning(lasterr());
end_try_catch

%RECEIVED TRAFFIC AT sPlus
try
	sPlusdata=load('P3-DiffServ-sPlus-arrivals.trace');
	plottraffic(sPlusdata, 2, "TRAFFIC GENERATED AT sPlus", "black", resolution, step);
catch
        warning(lasterr());
end_try_catch

%RECEIVED TRAFFIC AT s2 port 9
try
	s2data=load('P3-DiffServ-s2-arrivals_9.trace');
	plottraffic(s2data, 3, "TRAFFIC RECEIVED AT s2 port 9", "black", resolution, step);
catch
        warning(lasterr());
end_try_catch

%RECEIVED TRAFFIC AT s2
try
	s2data2=load('P3-DiffServ-s2-arrivals_10.trace');
	plottraffic(s2data2, 4, "TRAFFIC RECEIVED AT s2 port 10", "black", resolution, step);
catch
        warning(lasterr());
end_try_catch

%DROPPED NON-CONFORMANT PACKETS AT THE POLICING POINT (before enqueueing)
try
	r1DropNonConformantAFBE=load('r1.DropNonConformantAFBE.trace');
	plottraffic(r1DropNonConformantAFBE, 5, "DropNonConformantAFBE AT r1", "red", resolution, step);
catch
	warning(lasterr());
end_try_catch

% NEW plots
try
	r1DropNonConformantAFBE=load('r1.AQMDropAF1.trace');
	plottraffic(r1DropNonConformantAFBE, 6, "AQMDropAF1 (WRED, umbral sobrepasado) AT r1 AF1", "red", resolution, step);
catch
	warning(lasterr());
end_try_catch

try
	r1DropNonConformantAFBE=load('r1.DropTailAF1.trace');
	plottraffic(r1DropNonConformantAFBE, 7, "DropTailAF1 (Colas llenas) AT r1 AF1", "red", resolution, step);
catch
	warning(lasterr());
end_try_catch

try
	r1DropNonConformantAFBE=load('r1.DropTailBE.trace');
	plottraffic(r1DropNonConformantAFBE, 8, "DropTailBE (Colas llenas) AT r1", "red", resolution, step);
catch
	warning(lasterr());
end_try_catch


