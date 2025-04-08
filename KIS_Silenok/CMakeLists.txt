cmake_minimum_required(VERSION 3.12)
project(KIS_Silenok)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GSL_INCLUDE_DIR "C:/Users/Tumbi/vcpkg/installed/x64-windows/include")
set(GSL_LIBRARY "C:/Users/Tumbi/vcpkg/installed/x64-windows/lib/gsl.lib")
set(GSL_CBLAS_LIBRARY "C:/Users/Tumbi/vcpkg/installed/x64-windows/lib/gslcblas.lib")
add_executable(task1 src/task1/task1.cpp)
include_directories(${GSL_INCLUDE_DIR})
target_link_libraries(task1 ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY})

find_package(GTKMM REQUIRED)
include_directories(${GTKMM_INCLUDE_DIRS})
add_executable(task2 src/task2/task2.cpp)
target_link_libraries(task2 ${GTKMM_LIBRARIES})

add_executable(task3 src/task3/task3.cpp)