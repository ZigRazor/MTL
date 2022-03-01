cmake_minimum_required(VERSION 3.9)

# set the project name and version
project(MTL VERSION 0.0.1)

configure_file(MTL.h.in ${PROJECT_SOURCE_DIR}/include/MTL.h)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES /usr/local/lib ${CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES})

option(DEBUG "Enable Debug" OFF)
if(DEBUG)
	add_compile_options(
		-O0  #no optimization
		-g   #generate debug info
	)

endif(DEBUG)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE)
	message( "Code Coverage Enabled" )
	add_compile_options(
		-O0  #no optimization
		-g   #generate debug info
		--coverage #set coverage flag
		-fprofile-arcs
		-ftest-coverage
		-fPIC
	)
	link_libraries(
		"gcov"
		"-fprofile-arcs"
		"--coverage"
	)

endif(CODE_COVERAGE)

# add the library

file (GLOB SOURCE_FILES "src/*.cpp")
file (GLOB HEADER_FILES "include/*.h")
file (GLOB TEST_FILES "test/*.cpp")

message( STATUS "MTL Source files: ${SOURCE_FILES}" )
message( STATUS "MTL Header files: ${HEADER_FILES}" )
message( STATUS "MTL Test files: ${TEST_FILES}" )

add_library(MTL SHARED 
			${SOURCE_FILES}
				)

target_include_directories(MTL PUBLIC
						  "${PROJECT_SOURCE_DIR}/include"
						  )

target_link_libraries(MTL
                          pthread)

add_executable(test_exe ${TEST_FILES})
target_include_directories(test_exe PUBLIC
						  "${PROJECT_SOURCE_DIR}/include"
						  )
target_link_libraries(test_exe
					   libgtest.a
					   libgtest_main.a
					   libgmock.a
					   MTL)


enable_testing()

add_test(MTLRunnableTest test_exe --gtest_filter=MTLRunnableTest*)
add_test(MTLThreadTest test_exe --gtest_filter=MTLThreadTest*)



# Install
install(TARGETS MTL DESTINATION /usr/local/lib)

# Install the headers
install(FILES ${HEADER_FILES} DESTINATION /usr/local/include/MTL)

add_subdirectory(example)