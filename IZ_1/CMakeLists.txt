cmake_minimum_required(VERSION 3.0.0)
project(IZ_1)

add_executable(prog main.cpp)
add_executable(tests_cppunit tests/test.cpp)

add_subdirectory(IZ_1)

message("IZ_1_INCLUDE_DIRS = ${IZ_1_INCLUDE_DIRS}")
message("IZ_1_LIBRARIES = ${IZ_1_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${IZ_1_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${IZ_1_LIBRARIES})

add_subdirectory(tests)