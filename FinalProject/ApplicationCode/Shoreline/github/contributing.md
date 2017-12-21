# Contributing to Shoreline

⭐️ 🎉 Thanks for taking the time to contribute! 🎉 ⭐️

The following is a set of guidelines for contributing to __Shoreline__, which is hosted by the CMG Lab at the University of Colorado Boulder on GitHub. These are mostly guidelines, not rules. Use your best judgment, and feel free to propose changes to this document.
* This document is largely based on the [contributing guide](https://github.com/atom/atom/blob/master/CONTRIBUTING.md) used by [Atom.io](https://atom.io) (the preferred editor used by the Shoreline team).

## CxxTest
All functions written for Shoreline need to be unit tested via CxxTest. The users guide for CxxTest is given [here](http://cxxtest.com/guide.pdf). Tests are written in header files that live in the ```tests/``` folder.

## Styleguides

### Code
- Ensure all code contributions are limited to 80 characters per line.
- break up code blocks with lines of slashes to improve readability. ie:

```Cpp
//////////////////////////////////////////////////////////////////////////////
//Form left-hand-side stiffness matrix include BC's
if (rank == 0){cout << "Begin LHS assembly..." << endl << endl;}

// TODO: may need to change this step to get gen-alpha going
slvr.diffusion_insert(Global_LHS_Mat, true);
//slvr.diagonal_insert(Global_LHS_Mat); DEPRICATED

MatAssemblyBegin(Global_LHS_Mat,MAT_FINAL_ASSEMBLY);
MatAssemblyEnd(Global_LHS_Mat,MAT_FINAL_ASSEMBLY);

if (rank == 0){cout << "LHS stiffness matrix formed" << endl << endl;}

//////////////////////////////////////////////////////////////////////////////
//Form left-hand-side stiffness matrix dont include BC's
if (rank == 0){cout << "Begin RHS assembly..." << endl << endl;}

slvr.diffusion_insert(Global_RHS_Mat, false);
MatAssemblyBegin(Global_RHS_Mat,MAT_FINAL_ASSEMBLY);
MatAssemblyEnd(Global_RHS_Mat,MAT_FINAL_ASSEMBLY);

if (rank == 0){cout << "RHS stiffness matrix formed" << endl << endl;}

//////////////////////////////////////////////////////////////////////////////
//setup Krylov solver and Jacobi preconditioner
...
```
- keep function parameters to a minimum. i.e. With the exception of initializing an object, it is preferable to have no parameters passed to a function, though this is frequently difficult to accomplish.
- writing progress messages to stdout is advised when it is logical to do so (see above).

### Git Commit Messages
- Use the present tense ("Add feature" not "Added feature")
- Use the imperative mood ("Insert diffusion term..." not "Inserts diffusion term...")
- Limit the first line to 72 characters or less
- Reference issues and pull requests liberally after the first line
- Consider starting the commit message with an applicable emoji:
  - ⭐️ ```:white_medium_star:``` when adding a new feature
  - 🎨 ```:art:``` when improving the format/structure of the code
  - 🐎 ```:racehorse:``` when improving performance
  - 🚱 ```:non-potable_water:``` when plugging memory leaks
  - 📝 ```:memo:``` when writing documentation
  - 🐧 ```:penguin:``` when fixing something on Linux
  - 🍎 ```:apple:``` when fixing something on macOS
  - 🏁 ```:checkered_flag:``` when fixing something on Windows
  - 🐛 ```:bug:``` when fixing a bug
  - 🔥 ```:fire:``` when removing code or files
  - ✅ ```:white_check_mark:``` when adding tests
  - ⬆️ ```:arrow_up:``` when upgrading dependencies
  - ⬇️ ```:arrow_down:``` when downgrading dependencies
