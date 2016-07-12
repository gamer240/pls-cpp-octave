clear;
clc;
%TRAINING PHASE

%SENSOR DATA matrix x (same directory)

x=load ('sensor_data.txt');

%GAS CONCENTRATION matrix y

y=load ('gas_conc_data.txt');

pkg load all;
[xl,yl,xs,ys,coeff,fitted]=plsregress(x,y,columns(x));
y_predicted=x*coeff
y

plot(y_predicted,y,'LineWidth',1);
legend ('Gas 1','Gas 2');
xlabel('MEASURED CONC.');
ylabel('PREDICTED CONC.');


save training_gas_conc_predicted.txt y_predicted


% TESTING

%xnew=load('unknown_conc_data.txt');
%ynew=xnew*coeff

