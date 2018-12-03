project(someipApp)

set (CMAKE_CXX_FLAGS "-g -std=c++0x -pthread")

add_executable(service-example src/service-akku.cpp)
target_link_libraries(service-example vsomeip ${Boost_LIBRARIES})
