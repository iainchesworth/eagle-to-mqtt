if(CPACK_GENERATOR MATCHES "DEB")
	set(CPACK_PACKAGE_NAME "eagle-to-mqtt")
    set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
	set(CPACK_PACKAGE_CONTACT "")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Listens for Rainforest Automation EAGLE-200 messages and forwards them to an MQTT broker.")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER " <>")
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_PACKAGE_VERSION ${PACKAGE_VERSION})
    set(CPACK_DEBIAN_PACKAGE_SECTION "net")
endif()
