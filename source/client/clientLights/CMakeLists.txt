project(clientLights) 
 
set (CMAKE_CXX_FLAGS "-g -std=c++0x -pthread") 

add_executable(client-lights src/client-lights.cpp) 
target_link_libraries(client-lights vsomeip ${Boost_LIBRARIES})
add_custom_command(TARGET client-lights
    PRE_BUILD
    COMMAND ${PROJECT_SOURCE_DIR}/installscript.sh
    )
