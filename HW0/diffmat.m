%%  Homework 0
%   Author: Corey Nelson
%   Due: 13-Sep-2017
%
%Function diffmat(x) computes a finite difference matrix which computes
%first derivatives. 
%   INPUTS: x = space over which to take differences assume monotonically
%   increasing values of x
%
%   OUTPUTS: D = matrix of finite differences computes the derivatives of
%   f(x) at each point in x to O(h^2) accuracy. 
function D = diffmat(x)

%allocate D
D = sparse(numel(x),numel(x));

%compute derivative at left end point via 2nd order forward difference
dx1 = x(2) - x(1);
dx2 = x(3) - x(1);
D(1,1) = (1/(dx2-dx1))*(dx1/dx2 - dx2/dx1);
D(1,2) = (1/(dx2-dx1))*(dx2/dx1);
D(1,3) = -(1/(dx2-dx1))*(dx1/dx2);

%compute derivative at right end point via 2nd order forward difference
dxm1 = x(end-1) - x(end);
dxm2 = x(end-2) - x(end);
D(end,end) = (1/(dxm2 - dxm1))*(dxm1/dxm2 - dxm2/dxm1);
D(end,end-1) = (1/(dxm2 - dxm1))*(dxm2/dxm1);
D(end,end-2) = -(1/(dxm2 - dxm1))*(dxm1/dxm2);

%compute the middle terms via 2nd order finite difference as derived in
%class
for i = 2:numel(x)-1
    dxm1 =  x(i-1) - x(i);
    dx1 =   x(i+1) - x(i);
    D(i,i-1) = (1/(dx1 - dxm1))*(dx1/dxm1);
    D(i,i) = (1/(dx1 - dxm1))*(dxm1/dx1 - dx1/dxm1);
    D(i,i+1) = (1/(dx1 - dxm1))*(-dxm1/dx1);
end 
end