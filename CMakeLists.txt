cmake_minimum_required(VERSION 3.0)
project(someip-pi-setup)

option(CLIENT_SETUP "Set up the client" OFF)
option(SERVICE_SETUP "Set up the service" OFF)

if(CLIENT_SETUP)
    add_subdirectory(source/client/clientAkku)
    add_subdirectory(source/client/clientLights)
    	 
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
    
elseif(SERVICE_SETUP)
    add_subdirectory(source/service/serviceAkku)
    add_subdirectory(source/service/serviceLights)

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
endif(CLIENT_SETUP)
unset(CLIENT_SETUP CACHE)
unset(SERVICE_SETUP CACHE)