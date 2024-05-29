cmake_minimum_required(VERSION 3.0.0)
project(contest_5 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(contest_5
	src/IShape.cpp
	src/segment.cpp
	src/ray.cpp
	src/line.cpp
	src/point.cpp
	src/vector.cpp
	src/polygon.cpp
	src/circle.cpp
	main.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
