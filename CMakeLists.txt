cmake_minimum_required(VERSION 3.10)

# set the project name
project(client)

set(SOURCES
	client.cpp
	MySocket.cpp
)

set(HEADERS
	MySocket.h
)

# add the executable
add_executable(client ${SOURCES} ${HEADERS})
