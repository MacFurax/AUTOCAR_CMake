cmake_minimum_required(VERSION 3.5)

project(AUTOCAR_CMake)

set (CMAKE_CXX_STANDARD 14)

#include_directories(/usr/local/include .)
include_directories( 
	"D:/Constant Dupuis/Dev/cpp/libs/poco-1.7.8p3/Foundation/include" 
	"D:/Constant Dupuis/Dev/cpp/libs/poco-1.7.8p3/Net/include" 
	"D:/Constant Dupuis/Dev/cpp/AUTOCAR_CMake/src/oscpack_1_1_0" 
	. 
	)
#link_directories(/usr/local/lib)
link_directories("D:/Constant Dupuis/Dev/cpp/libs/poco-1.7.8p3/lib64" )

set(EXECUTABLE_OUTPUT_PATH bin)

add_executable( mcastSend src/mcastSend.cpp src/mcastSend.hpp )
add_executable( mcastEchoServer src/mcastEchoServer.cpp src/mcastEchoServer.hpp )
add_executable( OKARTestNode src/OKARTestNode.cpp src/OKAR/node.hpp )


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