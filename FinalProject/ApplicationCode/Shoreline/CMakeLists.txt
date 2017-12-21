cmake_minimum_required(VERSION 3.9.0)

################################ Compiler Flags ################################
set(CMAKE_C_COMPILER mpicc)
set(CMAKE_CXX_COMPILER mpicxx)
set(CMAKE_FORTRAN_COMPILER gfortran-7)
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

############################### Define Shoreline ###############################
project(Shoreline)

include_directories(include)

file(GLOB MAIN source/*.cpp)
file(GLOB SURFACE source/Surface/*.cpp)
file(GLOB SOLVER source/Solver/*.cpp)
file(GLOB PROBLEM source/Problem/*.cpp)

add_executable(Shoreline.exe "${MAIN}" "${SURFACE}" "${PROBLEM}" "${SOLVER}")

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeFiles")

########################### Add External Libraries #############################
FIND_PACKAGE(PETSc REQUIRED)
INCLUDE_DIRECTORIES(${PETSC_INCLUDES})
ADD_DEFINITIONS(${PETSC_DEFINITIONS})

TARGET_LINK_LIBRARIES(Shoreline.exe ${PETSC_LIBRARIES})

################################################################################
#                               start test suite
################################################################################

#ENABLE_TESTING()

find_package(CxxTest)
if(CXXTEST_FOUND)
    #file(GLOB SOURCES source/*.cpp)

    #include_directories(${CXXTEST_INCLUDE_DIR})

    ################################## A Test ##################################

    ############################################################################
endif()
