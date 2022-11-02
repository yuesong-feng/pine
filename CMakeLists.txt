cmake_minimum_required(VERSION 3.10)
project(pine)
set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")

include_directories(src)
file(GLOB_RECURSE pine_src src/*.cpp)
add_library(pine SHARED ${pine_src})

# add_executable(SocketTest "test/SocketTest.cpp")
# target_link_libraries(SocketTest pine)
# add_executable(PollTest "test/PollTest.cpp")
# target_link_libraries(PollTest pine)
# add_executable(EventTest "test/EventTest.cpp")
# target_link_libraries(EventTest pine)

# enable_testing()
# add_test(NAME socket_test COMMAND SocketTest)
# add_test(NAME poll_test COMMAND PollTest)
# add_test(NAME event_test COMMAND EventTest)

add_executable(server "server.cpp")
target_link_libraries(server pine)

add_executable(client "client.cpp")
target_link_libraries(client pine)

# add_executable(main "main.cpp")