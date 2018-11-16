cmake_minimum_required(VERSION 3.9)
project(APR_time)

set(CMAKE_CXX_STANDARD 14)


# APR
set(APR_TESTS OFF CACHE BOOL "" FORCE)
set(APR_BUILD_STATIC_LIB ON CACHE BOOL "" FORCE)
set(APR_BUILD_SHARED_LIB OFF CACHE BOOL "" FORCE)
set(APR_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(APR_USE_CUDA OFF CACHE BOOL "" FORCE)
set(APR_BENCHMARK OFF CACHE BOOL "" FORCE)
set(APR_USE_OPENMP ON CACHE BOOL "" FORCE)

add_subdirectory("LibAPR")
add_subdirectory("libboard")
#add_subdirectory("eigen-git-mirror")
set(APR_LIB staticLib)

include_directories(LibAPR)
include_directories(LibAPR/src)
include_directories(LibAPR/build)
INCLUDE_DIRECTORIES(${CMAKE_BUILD_FILES_DIRECTORY}/LibAPR)


set(CMAKE_C_FLAGS "${CMAKE_CFLAGS} -DHAVE_LIBTIFF")
set(CMAKE_CXX_FLAGS "${CMAKE_CXXFLAGS} -DHAVE_LIBTIFF")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic ")
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS_RELEASE "-O4 -ffast-math")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O4")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Bdynamic -ldl ")
endif(CMAKE_COMPILER_IS_GNUCC)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math")
    set(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g")
endif()

find_package(OpenMP)
if(NOT OPENMP_FOUND OR DISABLE_OPENMP)
    message("OpenMP support not found with current compiler. While APR can compile like this, performance might not be optimal. Please see README.md for instructions.")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DHAVE_OPENMP ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_OPENMP ${OpenMP_CXX_FLAGS}")
endif()


find_package(HDF5 REQUIRED)
find_package(TIFF REQUIRED)

INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIRS} ${TIFF_INCLUDE_DIR} ${APR_LIB})
include_directories( ${ZLIB_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${BLOSC_INCLUDE_DIRS})


SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
# Configure and add submodule BLOSC

include_directories(LibAPR/external/c-blosc/blosc)
INCLUDE_DIRECTORIES(${CMAKE_BUILD_FILES_DIRECTORY}/LibAPR/external/c-blosc/blosc)

#APRBenchMarks

add_executable(MovingBlobs examples/Example_moving_blobs.cpp)
target_link_libraries(MovingBlobs  ${APR_LIB} ${GTEST_LIBRARIES} ${HDF5_LIBRARIES} ${TIFF_LIBRARIES} ${ArrayFire_OpenCL_LIBRARIES} ${OpenCL_LIBRARIES} ${BLOSC_LIBRARIES})

