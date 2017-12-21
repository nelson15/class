![alt text](https://raw.githubusercontent.com/CMGLab/Nelson/master/ImmersiveSims/ApplicationCode/Shoreline/github/Shoreline.png?token=AOW0sWH1MNHt3fAVPP6XCpBRqr61uxFXks5aPa1ZwA%3D%3D "Shoreline")
### A CMG Lab Production
__Author__: Corey Wetterer-Nelson

## Installation
### MacOS:
1. install Homebrew: https://brew.sh
- install CMake (need it for metis AND for __Shoreline__): ```brew install CMake```
- install gcc (gcc is probably already installed, but Homebrew has an easier time if it has its own copy): ```brew install gcc```
- install metis: ```brew install metis```
- install scalapack: ```brew install scalapack```
- install openmpi: ```brew install openmpi```
- install petsc: ```brew install petsc```
- Install CBLAS and LAPACKE
    1. download the latest lapack from netlib website (you need gfortran installed too)
    - unarchive
    - rename the file ```make.inc.example``` to ```make.inc```
    - Within ```make.inc```, change the line ```OPTS = -O2 -frecursive``` to ```OPTS = -O3 -frecursive -pipe```
    - at command line, run the following from the lapack directory (the directory with the make.inc file)
        1. ```make blaslib``` -> to get Reference BLAS librefblas.a
        - ```make cblaslib``` -> to get CBLAS libcblas.a
        - ```make cblas_example``` -> To complie CBLAS example
        - ```make lapacklib``` -> To get LAPACK liblapack.a and libtmglib.a
        - ```make lapacke``` --> to get LAPACKE liblapacke.a
- Move ```cblas.a``` and ```lapacke.a``` to ```/usr/local/lib```
- Move ```cblas.h``` and ```lapacke.h``` from the downloaded lapack ```file/include``` to ```/usr/local/include```
- go to __Shoreline__ folder and run the shell script (for instance): ```bash construct.sh```. This will build __Shoreline__ and all of its unit tests.

You're done! Now __Shoreline__ is built on your machine!
Hopefully that wasn't so bad. Report all installation issues to Corey.

### Linux
Probably similar to MacOS without all the Homebrew steps.

### Windows
Good luck...

## Test Installation
To test your installation of __Shoreline__, run ```bash testShoreline.sh```. This will generate a test log ```build/Testing/Test.log``` detailing the results of all unit tests.  

## Usage

## Bored?
Maybe take a crack at some of these [to-do list](github/todo.md) items!

## Credits
- Corey Wetterer-Nelson: Lead developer of __Shoreline__.
  corey.nelson@colorado.edu
- John A. Evans: PhD advisor. john.a.evans@colorado.edu
