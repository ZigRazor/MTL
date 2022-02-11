project(example_4)
cmake_minimum_required(VERSION 3.9)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
						  "${PROJECT_SOURCE_DIR}/include"
						  )
target_link_libraries(${PROJECT_NAME} MTL)