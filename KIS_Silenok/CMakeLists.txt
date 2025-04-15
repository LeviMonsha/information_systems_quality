cmake_minimum_required(VERSION 3.14)
project(KIS_Silenok)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# GSL
FetchContent_Declare(
  GSL
  GIT_REPOSITORY https://github.com/microsoft/GSL.git
  GIT_TAG v4.2.0
  GIT_SHALLOW ON
)
FetchContent_MakeAvailable(GSL)

# SFML
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.5.1
  GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

set(GSL_DLL_DIR "${CMAKE_BINARY_DIR}/_deps/gsl-build/bin/Debug")
set(SFML_DLL_DIR "${CMAKE_BINARY_DIR}/_deps/sfml-build/lib/Debug")

function(copy_sfml_dll target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_DLL_DIR}"
        $<TARGET_FILE_DIR:${target}>
    )
endfunction()

function(copy_dlls target dll_dir)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${dll_dir}"
        $<TARGET_FILE_DIR:${target}>
    )
endfunction()

# task1
add_executable(task1 src/task1/task1.cpp)
target_link_libraries(task1 PRIVATE Microsoft.GSL::GSL)
set_target_properties(task1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Debug/task1"
)
copy_dlls(task1 "${GSL_DLL_DIR}")

# task2
add_executable(task2 src/task2/task2.cpp)
target_link_libraries(task2 PRIVATE sfml-graphics sfml-window sfml-system)
set_target_properties(task2 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Debug/task2"
)
copy_dlls(task2 "${SFML_DLL_DIR}")

# task3
add_executable(task3 src/task3/task3.cpp)
target_link_libraries(task3 PRIVATE sfml-graphics sfml-window sfml-system)
set_target_properties(task3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Debug/task3"
)
copy_dlls(task3 "${SFML_DLL_DIR}")

message(STATUS "CMake configuration complete.")