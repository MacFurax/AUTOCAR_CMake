cmake_minimum_required(VERSION 3.5)

project(AUTOCAR_CMake)

set (CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include .)
link_directories(/usr/local/lib)

set(EXECUTABLE_OUTPUT_PATH bin)

add_executable( mcastSend src/mcastSend.cpp src/mcastSend.hpp )
add_executable( mcastEchoServer src/mcastEchoServer.cpp src/mcastEchoServer.hpp )


target_link_libraries(

        mcastSend

        PocoFoundation
        PocoNet

)


target_link_libraries(

        mcastEchoServer

        PocoFoundation
        PocoNet

)