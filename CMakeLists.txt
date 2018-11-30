cmake_minimum_required(VERSION 3.0)
project(someip-pi-setup)

option(CLIENT_SETUP "Set up the client" OFF)
option(SERVICE_SETUP "Set up the service" OFF)

find_package (vsomeip 2.6.0 REQUIRED) 
	find_package( Boost COMPONENTS system thread log REQUIRED ) 
	 
	include_directories ( 
	        ${Boost_INCLUDE_DIR} 
	        ${VSOMEIP_INCLUDE_DIRS} 
	) 

if(CLIENT_SETUP)
    add_subdirectory(source/clientAkku)
    add_subdirectory(source/clientLights)
    	 
	add_custom_target(client_setup
		COMMENT "Client setup target"
	)
	
	add_custom_command(TARGET client_setup
    	PRE_BUILD
    	COMMAND ${PROJECT_SOURCE_DIR}/installscript.sh
    )
elseif(SERVICE_SETUP)
    add_subdirectory(source/serviceAkku)
    add_subdirectory(source/serviceLights)

	add_custom_target(service_setup
		COMMENT "Service setup target"
	)

	add_custom_command(TARGET service_setup
    	PRE_BUILD
    	COMMAND ${PROJECT_SOURCE_DIR}/installscript.sh
    )
endif(CLIENT_SETUP)
unset(CLIENT_SETUP CACHE)
unset(SERVICE_SETUP CACHE)