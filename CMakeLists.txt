cmake_minimum_required(VERSION 3.0)
project(someip-pi-setup)

set (CMAKE_CXX_FLAGS "-g -std=c++11 -pthread") 

find_package (vsomeip 2.6.0 REQUIRED)
find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )

include_directories (
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

option(CLIENT_SETUP "Set up the client" OFF)
option(SERVICE_SETUP "Set up the service" OFF)

if(CLIENT_SETUP)
	add_custom_target(client_setup
		COMMENT "Client setup target"
	)
	
	add_custom_command(TARGET client_setup
    	PRE_BUILD
    	COMMAND ${PROJECT_SOURCE_DIR}/installscript.sh
    )
    
    add_custom_command(TARGET client_setup
    	POST_BUILD
    	COMMAND ${CMAKE_COMMAND} -E copy
    			${CMAKE_SOURCE_DIR}/client/dhcpcd.conf
    			/etc/dhcpcd.conf
	)
	
	add_custom_command(TARGET client_setup
    	POST_BUILD
    	COMMAND ${CMAKE_COMMAND} -E copy
    			${CMAKE_SOURCE_DIR}/client/vsomeip.json
    			/etc/vsomeip.json
	)
	
	add_executable(client-lights ${CMAKE_SOURCE_DIR}/source/client/clientLights/src/client-lights.cpp) 
	target_link_libraries(client-lights vsomeip ${Boost_LIBRARIES})
	
	add_executable(client-akku ${CMAKE_SOURCE_DIR}/source/client/clientAkku/src/client-akku.cpp) 
	target_link_libraries(client-akku vsomeip ${Boost_LIBRARIES})
    
elseif(SERVICE_SETUP)
	add_custom_target(service_setup
		COMMENT "Service setup target"
	)

	add_custom_command(TARGET service_setup
    	PRE_BUILD
    	COMMAND ${PROJECT_SOURCE_DIR}/installscript.sh
    )
    
	add_custom_command(TARGET service_setup
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/service/dhcpcd.conf
		/etc/dhcpcd.conf
	)
	
	add_custom_command(TARGET service_setup
    	POST_BUILD
    	COMMAND ${CMAKE_COMMAND} -E copy
    			${CMAKE_SOURCE_DIR}/service/vsomeip.json
    			/etc/vsomeip.json
	)
	add_executable(service-lights ${CMAKE_SOURCE_DIR}/source/service/serviceLights/src/service-lights.cpp) 
	target_link_libraries(service-lights vsomeip ${Boost_LIBRARIES})
	
	add_executable(service-akku ${CMAKE_SOURCE_DIR}/source/service/serviceAkku/src/service-akku.cpp) 
	target_link_libraries(service-akku vsomeip ${Boost_LIBRARIES})
endif(CLIENT_SETUP)
unset(CLIENT_SETUP CACHE)
unset(SERVICE_SETUP CACHE)
