{\rtf1\ansi\ansicpg1252\cocoartf1504\cocoasubrtf830
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww10800\viewh15580\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 Corey Nelson\
HW0\
Due: 13-Sep-2017\
\
1: Write a function diffmat(x) which computes a finite difference matrix for the first derivative:\
\
My diffmat(x) function computes the 3 point finite difference through the middle of the domain as we derived in class. At the left end point, I used a 3 point forward difference which is also a O(h^2) stencil. I derived this via taylor series one point and 2 points forward. Take f0 = f(0), dx1=(x1-x0) etc:\
\
f1 = f0 + f\'920*dx1 + f\'92\'920 dx1^2 + O(h^3)\
f2 = f0 + f\'920*dx2 + f\'92\'920 dx2^2 + O(h^3)\
\
f\'920*dx1 = f1 - f0 - f\'92\'920 dx1^2 + O(h^3)\
f\'920*dx2 = f2 - f0 - f\'92\'920 dx2^2 + O(h^3)\
\
f\'920 = 1/dx1(f1-f0) - f\'92\'920dx1 + O(h^2)\
f\'920 = 1/dx2(f2-f1) - f\'92\'920dx2 + O(h^2)\
\
f\'920*dx2 = dx2/dx1(f1-f0) - f\'92\'920dx1dx2 + O(h^2)\
f\'920*dx1 = dx1/dx2(f2-f0) - f\'92\'920dx1dx2 + O(h^2)\
subtract the two\
f\'920(dx2-dx1) = dx2/dx1(f1-f0) - dx1/dx2(f2-f0) + O(h^2)\
\
f\'920 = 1/(dx2-dx1) * [(dx1/dx2-dx2/dx1)f0 + (dx2/dx1)f1 - (dx1/dx2)f2]  [] \
\
The exact same derivation holds for the backward difference at the right end point, though the sign switches on all the terms.\
\
I utilized the inf norm to compare the computed solutions with exact solutions. As shown in the plots exp_convergence_plot.eps, sin_convergence_plot.eps and exp_convergence_LogSpaced.eps, the method produces a finite difference stencil which does indeed converge as O(h^2). For the dramatically stretched logspace mesh, the method takes a few refinements to match the slope 1/h^2, but does reach it though with a larger coefficient of convergence than on the linearly spaced meshes. \
\
2: write a function diff2mat which computes the 2nd derivative finite difference matrix D2.\
\
I utilized the inf norm to compare the computed solutions with exact solutions. I utilized a the standard second order accurate central difference scheme throughout the middle of the domain that we used in class. At the end points, I assumed evenly spaced points and used a well known forward (and backward) difference stencil at the two end points. This works great for evenly spaced grids, but jittering the grid even a little cripples the convergence rate (see 2ndDeriv_sin_Jittered_withEnds). Removing the endpoints from the error computation brings the convergence to approximately O(h), which is still worse than expected with the 3 point finite difference (see 2ndDeriv_sin_Jittered). \
}