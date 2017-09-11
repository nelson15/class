%%  Homework 0
%   Author: Corey Nelson
%   Due: 13-Sep-2017
%
%Function diff2mat(x) computes a finite difference matrix which computes
%second derivatives. 
%   INPUTS: x = space over which to take differences assume monotonically
%   increasing values of x
%
%   OUTPUTS: D2 = matrix of finite differences computes the 2nd derivatives of
%   f(x) at each point in x to O(h^2) accuracy. 
function D2 = diff2mat(x)

%allocate D
D2 = sparse(numel(x),numel(x));

%compute derivative at left end point via 2nd order forward difference
h2 = 1/mean(x(2:5)-x(1:4))^2;
D2(1,1) = 2*h2;
D2(1,2) = -5*h2;
D2(1,3) = 4*h2;
D2(1,4) = -h2;

%compute derivative at right end point via 2nd order forward difference
hm2 = 1/mean(x(end-4:end)-x(end-5:end-1))^2;
D2(end,end) = 2*hm2;
D2(end,end-1) = -5*hm2;
D2(end,end-2) = 4*hm2;
D2(end,end-3) = -h2;

%compute the middle terms via 2nd order finite difference as derived in
%class
for i = 2:numel(x)-1
    dxm1 =  x(i-1) - x(i);
    dx1 =   x(i+1) - x(i);
    D2(i,i-1)   = (2/(dx1 - dxm1))*(-1/dxm1);
    D2(i,i)     = (2/(dx1 - dxm1))*(1/dxm1 - 1/dx1);
    D2(i,i+1)   = (2/(dx1 - dxm1))*(1/dx1);
end 
end