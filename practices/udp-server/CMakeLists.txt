cmake_minimum_required(VERSION 2.8.9)

#
# Server exec
#
project(server)
add_executable(${CMAKE_PROJECT_NAME} "server.c")
target_link_libraries(${CMAKE_PROJECT_NAME} progbase)
#
# Client exec
#
project(client)
add_executable(${CMAKE_PROJECT_NAME} "client.c")
target_link_libraries(${CMAKE_PROJECT_NAME} progbase)
