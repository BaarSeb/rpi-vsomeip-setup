project(serviceLights)

set (CMAKE_CXX_FLAGS "-g -std=c++0x -pthread")

add_executable(service-lights src/service-lights.cpp)
target_link_libraries(service-lights vsomeip ${Boost_LIBRARIES})
