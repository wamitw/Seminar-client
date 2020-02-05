cmake_minimum_required(VERSION 3.10)

# set the project name
project(client)

set(SOURCES
	client.cpp
	MySocket.cpp
	MySSLSocket.cpp
)

set(HEADERS
	MySocket.h
	MySSLSocket.h
)

find_package(OpenSSL REQUIRED)

#Compile Flags
set(GCC_COMPILE_FLAGS "-g -std=c++11 -Wall -Werror -Wextra -pedantic -Wconversion -Wcast-align -Wunused -Wold-style-cast -Wpointer-arith -Wcast-qual -Wno-missing-braces -Wformat-security -Wno-deprecated-declarations -Wno-unused-function")
add_definitions(${GCC_COMPILE_FLAGS})

# add the executable
add_executable(client ${SOURCES} ${HEADERS})
target_link_libraries(client OpenSSL::SSL)
