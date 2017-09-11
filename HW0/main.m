%%  Homework 0
%   Author: Corey Nelson
%   Due: 13-Sep-2017

%% 1: 
%   Write a function diffmat(x) that returns a matrix  D that 
%   computes first derivatives.
close all

%test diffmat(x) convergence characteristic
a = fliplr(3:15); %2^a nodes per mesh
error = zeros(size(a)); %stores the error for each mesh

for i = 1:numel(a)%loop over all the meshes
    x = linspace(0,pi,2^a(i))';
    D = diffmat(x);
    y = sin(x);
    yprime_true = cos(x);
    yprime_approx = D*y;
    error(i) = norm(yprime_true - yprime_approx,inf);
end

%plot error
figure
loglog((2.^a), error,'o','LineWidth',2)
hold on
loglog((2.^a),1./(2.^a-1).^2,'LineWidth',2)
legend('inf-norm', '1/h^2')
axis tight
title('Convergence of 2nd order finite difference scheme for f(x)=sin(x)'...
       ,'fontsize',16,'interpreter','latex')
xlabel('n','fontsize',16,'interpreter','latex')
ylabel('Derivative Error','fontsize',16,'interpreter','latex')

%%
for i = 1:numel(a)%loop over all the meshes
    x = logspace(-16,log10(pi),2^a(i))';
    D = diffmat(x);
    y = sin(x);
    yprime_true = cos(x);
    yprime_approx = D*y;
    error(i) = norm(yprime_true - yprime_approx,inf);
end

%plot error
figure
loglog((2.^a), error,'o','LineWidth',2)
hold on
loglog((2.^a),1./(2.^a-1).^2,'LineWidth',2)
legend('inf-norm', '1/h^2')
axis tight
title('Convergence of 2nd order finite difference scheme for f(x)=sin(x) with logarithmically space points'...
       ,'fontsize',12,'interpreter','latex')
xlabel('n','fontsize',16,'interpreter','latex')
ylabel('Derivative Error','fontsize',16,'interpreter','latex')

%% error for e^x
for i = 1:numel(a)%loop over all the meshes
    x = linspace(0,pi,2^a(i))';
    D = diffmat(x);
    y = exp(x);
    yprime_true = exp(x);
    yprime_approx = D*y;
    error(i) = norm(yprime_true - yprime_approx,inf);
end

%plot error
figure
loglog((2.^a), error,'o','LineWidth',2)
hold on
loglog((2.^a),1./(2.^a-1).^2,'LineWidth',2)
legend('inf-norm', '1/h^2')
axis tight
title('Convergence of 2nd order finite difference scheme for f(x)=exp(x)'...
       ,'fontsize',16,'interpreter','latex')
xlabel('n','fontsize',16,'interpreter','latex')
ylabel('Derivative Error','fontsize',16,'interpreter','latex')

%%
%% 2: diff2mat(x)
close all
a = 3:10;
error = zeros(size(a));
%% error for e^x
for i = 1:numel(a)%loop over all the meshes
    x = linspace(0,1,2^a(i))';
    D2 = diff2mat(x);
    y = exp(x);
    yprime_true = exp(x);
    yprime_approx = D2*y;
    error(i) = norm(yprime_true - yprime_approx,inf);
end

%plot error
figure
loglog((2.^a), error,'o','LineWidth',2)
hold on
loglog((2.^a),1./(2.^a-1).^2,'LineWidth',2)
legend('inf-norm', '1/h^2')
axis tight
title('Convergence of 2nd Derivative via finite differences for f(x)=exp(x)'...
       ,'fontsize',16,'interpreter','latex')
xlabel('n','fontsize',16,'interpreter','latex')
ylabel('Derivative Error','fontsize',16,'interpreter','latex')
%% error for sin(x)
for i = 1:numel(a)%loop over all the meshes
    x = linspace(0,pi,2^a(i))';
    D2 = diff2mat(x);
    y = sin(x);
    yprime_true = -sin(x);
    yprime_approx = D2*y;
    error(i) = norm(yprime_true - yprime_approx,inf);
end

%plot error
figure
loglog((2.^a), error,'o','LineWidth',2)
hold on
loglog((2.^a),1./(2.^a-1).^2,'LineWidth',2)
legend('inf-norm', '1/h^2')
axis tight
title('Convergence of 2nd Derivative via finite differences for f(x)=sin(x)'...
       ,'fontsize',16,'interpreter','latex')
xlabel('n','fontsize',16,'interpreter','latex')
ylabel('Derivative Error','fontsize',16,'interpreter','latex')

%% error for sin(x) on randomly gittered mesh
for i = 1:numel(a)%loop over all the meshes
    x = linspace(0,pi,2^a(i))';
    h = x(2) - x(1);
    x(2:end-1) = x(2:end-1) + h/8*rand(size(x(2:end-1)));
    D2 = diff2mat(x);
    y = exp(x);
    yprime_true = exp(x);
    yprime_approx = D2*y;
    error(i) = norm(yprime_true - yprime_approx,inf);
end

%plot error
figure
loglog((2.^a), error,'o','LineWidth',2)
hold on
loglog((2.^a),1./(2.^a-1).^2,'LineWidth',2)
loglog((2.^a),1./(2.^a-1),'LineWidth',2)
legend('inf-norm', '1/h^2','1/h')
axis tight
title('Convergence of 2nd Derivative via finite differences for f(x)=sin(x)'...
       ,'fontsize',16,'interpreter','latex')
xlabel('n','fontsize',16,'interpreter','latex')
ylabel('Derivative Error','fontsize',16,'interpreter','latex')
