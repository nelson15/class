# Isogeometric Finite Elements on a Manifold
### Corey Nelson
### CSCI - 5636 Numerical Solutions to PDE's
### Final Project

## Introduction:

The goal of this project is to model the Laplace-Beltrami equation (and potentially Advection-Diffusion) over a 2D manifold in 3-space. The manifold will be defined by a NURBS (NonUniform Rational B-spline) geometry, and those same NURBS defining the geometry will be employed as the basis functions in the finite element method. This discretization method, known popularly as Isogeometric Analysis (IGA) provides exact representation of the geometry along with a high order finite element method.

## Impetus for the Project:
My phd research is moving into optimal geometric parametrization. Essentially, the goal is to enable the user of a high performance simulation to manipulate and deform the computational domain in a natural way as the simulation is running. This will enable the user to gain insight into how those changes affect the simulation in real time. In order to accomplish this, the first step is to develop the tools to optimally parametrize the deformable surfaces of the computational domain such that they preserve certain qualities as they are being deformed. This means diving into the world of differential geometry! Here, we would like to be able to compute and manipulate quantities such as metric tensors. The first step in this effort is to develop a method for solving the [Laplace-Beltrami equation](https://en.wikipedia.org/wiki/Laplace–Beltrami_operator) over a surface living in 3-space. Like the ordinary Laplace equation, The Laplace-Beltrami equation is the divergence of the gradient of a function, but this function is defined over a manifold.

Isogeometric Analysis is perfectly suited to solving this problem, as the geometry of the manifolds to be investigated can (and will be) represented exactly as NURBS surfaces.

## Road Map:
1. Build method for defining and importing manifolds into solver framework ✅ (Blender is a cool program)
2. Compute NURBS basis functions from the imported geometric parametrization ✅
3. Compute mapping from parametric gradients to gradients tangent to the manifold (harder part, involves mapping gradient vectors in R2 to gradient vectors in R3 tangent to the surface via covariant vectors on the manifold).
4. Solve the weak form of the Laplace-Beltrami equation over the manifold via IGA
5. Assuming this all goes well and goes quickly, I would like to chase solving the Advection-Diffusion equation over the surface in an unsteady manner. This will involve implementing a time stepping scheme as well as stabilization due to the advection operator.

## Cool Stuff Pertaining to Class:
1. Isogeometric Analysis is a new and exciting method of discretization. Because we have spent much of the class studying discretization techniques, this is relevant. 
2. We have looked at Laplace's equation in class, and the Laplace-Beltrami is related enough to look at through the lens of the things we've done in class.
3. If Advection-Diffusion happens, this will be a great place to look at how the discretization will play with the (probably explicit) time stepping algorithm to be implemented.
