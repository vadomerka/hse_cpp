cmake_minimum_required(VERSION 3.0.0)
project(a_rational VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(a_rational
	rational.cpp
	main.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
