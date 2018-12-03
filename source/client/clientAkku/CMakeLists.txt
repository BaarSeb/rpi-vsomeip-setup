project(clientAkku)

set (CMAKE_CXX_FLAGS "-g -std=c++0x -pthread")

add_executable(client-akku src/client-akku.cpp)
target_link_libraries(client-akku vsomeip ${Boost_LIBRARIES})
