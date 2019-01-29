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
	
	add_executable(client-lights ${CMAKE_SOURCE_DIR}/source/client/clientLights/src/client-lights.cpp) 
	target_link_libraries(client-lights vsomeip ${Boost_LIBRARIES})
	
	add_executable(client-akku ${CMAKE_SOURCE_DIR}/source/client/clientAkku/src/client-akku.cpp) 
	target_link_libraries(client-akku vsomeip ${Boost_LIBRARIES})
	
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/client-package/usr/local/bin)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/client-package/etc/systemd/system)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/client-package/DEBIAN)
	
	install(FILES ${CMAKE_SOURCE_DIR}/source/client/control DESTINATION ${CMAKE_BINARY_DIR}/client-package/DEBIAN)
	install(FILES ${CMAKE_SOURCE_DIR}/source/client/postinst PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION ${CMAKE_BINARY_DIR}/client-package/DEBIAN)
	
	install(FILES ${CMAKE_BINARY_DIR}/client-lights PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION ${CMAKE_BINARY_DIR}/client-package/usr/local/bin)
	install(FILES ${CMAKE_BINARY_DIR}/client-akku PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION ${CMAKE_BINARY_DIR}/client-package/usr/local/bin)    
	
	install(FILES ${CMAKE_SOURCE_DIR}/source/client/vsomeip.json DESTINATION ${CMAKE_BINARY_DIR}/client-package/etc)
	install(FILES ${CMAKE_SOURCE_DIR}/source/client/dhcpcd.conf DESTINATION ${CMAKE_BINARY_DIR}/client-package/etc/dhcpcd_tmp)
	
	install(FILES ${CMAKE_SOURCE_DIR}/source/client/clientAkku/client_akku.service DESTINATION ${CMAKE_BINARY_DIR}/client-package/etc/systemd/system)
	install(FILES ${CMAKE_SOURCE_DIR}/source/client/clientLights/client_lights.service DESTINATION ${CMAKE_BINARY_DIR}/client-package/etc/systemd/system)	
elseif(SERVICE_SETUP)

	add_executable(service-lights ${CMAKE_SOURCE_DIR}/source/service/serviceLights/src/service-lights.cpp) 
	target_link_libraries(service-lights vsomeip ${Boost_LIBRARIES})
	
	add_executable(service-akku ${CMAKE_SOURCE_DIR}/source/service/serviceAkku/src/service-akku.cpp) 
	target_link_libraries(service-akku vsomeip ${Boost_LIBRARIES})

	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/service-package/usr/local/bin)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/service-package/etc/systemd/system)
	install(DIRECTORY DESTINATION ${CMAKE_BINARY_DIR}/service-package/DEBIAN)
	
	install(FILES ${CMAKE_SOURCE_DIR}/source/service/control DESTINATION ${CMAKE_BINARY_DIR}/service-package/DEBIAN)
	install(FILES ${CMAKE_SOURCE_DIR}/source/service/postinst PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION ${CMAKE_BINARY_DIR}/service-package/DEBIAN)
	
	install(FILES ${CMAKE_BINARY_DIR}/service-lights PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION ${CMAKE_BINARY_DIR}/service-package/usr/local/bin)
	install(FILES ${CMAKE_BINARY_DIR}/service-akku PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE DESTINATION ${CMAKE_BINARY_DIR}/service-package/usr/local/bin)    
	
	install(FILES ${CMAKE_SOURCE_DIR}/source/service/vsomeip.json DESTINATION ${CMAKE_BINARY_DIR}/service-package/etc)
	install(FILES ${CMAKE_SOURCE_DIR}/source/service/dhcpcd.conf DESTINATION ${CMAKE_BINARY_DIR}/service-package/etc/dhcpcd_tmp)

	install(FILES ${CMAKE_SOURCE_DIR}/source/service/serviceAkku/service_akku_msg.json DESTINATION ${CMAKE_BINARY_DIR}/service-package/etc)
	install(FILES ${CMAKE_SOURCE_DIR}/source/service/serviceLights/service_lights_msg.json DESTINATION ${CMAKE_BINARY_DIR}/service-package/etc)
	
	install(FILES ${CMAKE_SOURCE_DIR}/source/service/serviceAkku/service_akku.service DESTINATION ${CMAKE_BINARY_DIR}/service-package/etc/systemd/system)
	install(FILES ${CMAKE_SOURCE_DIR}/source/service/serviceLights/service_lights.service DESTINATION ${CMAKE_BINARY_DIR}/service-package/etc/systemd/system)	

endif(CLIENT_SETUP)
unset(CLIENT_SETUP CACHE)
unset(SERVICE_SETUP CACHE)
