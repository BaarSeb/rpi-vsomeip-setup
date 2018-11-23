cmake_minimum_required(VERSION 3.10)
project(someipApp)

set (CMAKE_CXX_FLAGS "-g -std=c++0x -pthread")

find_package (vsomeip 2.6.0 REQUIRED)
find_package( Boost COMPONENTS system thread log REQUIRED )

include_directories (
        ${Boost_INCLUDE_DIR}
        ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(client-akku src/client-akku.cpp)
target_link_libraries(client-akku vsomeip ${Boost_LIBRARIES})
