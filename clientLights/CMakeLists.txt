project(clientLights) 
 
set (CMAKE_CXX_FLAGS "-g -std=c++0x -pthread") 
 
find_package (vsomeip 2.6.0 REQUIRED) 
find_package( Boost COMPONENTS system thread log REQUIRED ) 
 
include_directories ( 
        ${Boost_INCLUDE_DIR} 
        ${VSOMEIP_INCLUDE_DIRS} 
) 
 
add_executable(client-lights src/client-lights.cpp) 
target_link_libraries(client-lights vsomeip ${Boost_LIBRARIES})
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
~                                                                              
-- VISUELL --                                      15        15,62       Alles

