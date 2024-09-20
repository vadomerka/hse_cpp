cmake_minimum_required(VERSION 3.0.0)
<<<<<<< HEAD
project(mainprj VERSION 0.1.0 LANGUAGES C CXX)

add_executable(mainprj main.cpp)

=======
project(main_tests VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(main_tests main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
>>>>>>> 1b7b029e89e72998979dedfa7b1b241b1a1d07e6
