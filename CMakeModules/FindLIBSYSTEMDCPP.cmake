if(SYSTEMDCPP_LIBRARIES AND SYSTEMDCPP_INCLUDE_DIRS)
    set(SYSTEMDCPP_FOUND TRUE)
else()
    find_path(
        SYSTEMDCPP_INCLUDE_DIR
        NAMES sdbus-c++/sdbus-c++.h
        PATHS /usr/include /usr/local/include /opt/local/include /sw/include ${CMAKE_INCLUDE_PATH} ${CMAKE_INSTALL_PREFIX}/include
    )

    find_library(
        SYSTEMDCPP_LIBRARY
        NAMES sdbus-c++
        PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 /opt/local/lib /sw/lib ${CMAKE_LIBRARY_PATH} ${CMAKE_INSTALL_PREFIX}/lib
    )

    if(SYSTEMDCPP_INCLUDE_DIR AND SYSTEMDCPP_LIBRARY)
        set(SYSTEMDCPP_FOUND TRUE)
    else(SYSTEMDCPP_INCLUDE_DIR AND SYSTEMDCPP_LIBRARY)
        set(SYSTEMDCPP_FOUND FALSE)
    endif(SYSTEMDCPP_INCLUDE_DIR AND SYSTEMDCPP_LIBRARY)

    set(SYSTEMDCPP_INCLUDE_DIRS ${SYSTEMD_INCLUDE_DIR})
    set(SYSTEMDCPP_LIBRARIES ${SYSTEMD_LIBRARY})
endif()
