cmake_minimum_required(VERSION 3.20)
project(KIS_Silenok)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Boost
FetchContent_Declare(
  boost
  URL https://downloads.sourceforge.net/project/boost/boost/1.82.0/boost_1_82_0.tar.gz
  URL_HASH SHA256=66a469b6e608a51f8347236f4912e27dc5c60c60d7d53ae9bfe4683316c6f04c
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(boost)

# SFML
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.0
  GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

set(SFML_DLL_DIR "${CMAKE_BINARY_DIR}/_deps/sfml-build/lib")

function(copy_dlls target dll_dir)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${dll_dir}"
        $<TARGET_FILE_DIR:${target}>
    )
endfunction()

# task1
add_executable(task1 src/task1/task1.cpp)
target_include_directories(task1 PRIVATE
  ${boost_SOURCE_DIR}
)
target_link_libraries(task1 PRIVATE)

# task2
add_executable(task2 src/task2/task2.cpp)
target_include_directories(task2 PRIVATE
  ${boost_SOURCE_DIR}
)
target_link_libraries(task2 PRIVATE sfml-graphics sfml-window sfml-system)
copy_dlls(task2 "${SFML_DLL_DIR}")

# task3
add_executable(task3 src/task3/task3.cpp)

message(STATUS "CMake configuration complete.")
