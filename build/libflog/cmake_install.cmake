# Install script for directory: /home/faculty/asutton/Code/onf/onfc/libflog

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/faculty/asutton/opt")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/faculty/asutton/Code/onf/onfc/build/libflog/libflog.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/flog/flog.cmake")
    FILE(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/flog/flog.cmake"
         "/home/faculty/asutton/Code/onf/onfc/build/libflog/CMakeFiles/Export/lib/flog/flog.cmake")
    IF(EXPORT_FILE_CHANGED)
      FILE(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/flog/flog-*.cmake")
      IF(OLD_CONFIG_FILES)
        MESSAGE(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/flog/flog.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        FILE(REMOVE ${OLD_CONFIG_FILES})
      ENDIF(OLD_CONFIG_FILES)
    ENDIF(EXPORT_FILE_CHANGED)
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/flog" TYPE FILE FILES "/home/faculty/asutton/Code/onf/onfc/build/libflog/CMakeFiles/Export/lib/flog/flog.cmake")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/flog" TYPE FILE FILES "/home/faculty/asutton/Code/onf/onfc/build/libflog/CMakeFiles/Export/lib/flog/flog-debug.cmake")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog" TYPE FILE FILES
    "/home/faculty/asutton/Code/onf/onfc/libflog/utilities.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/string.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/error.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/buffer.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/sequence.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/message.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/connection.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/connection.ipp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto" TYPE FILE FILES "/home/faculty/asutton/Code/onf/onfc/libflog/proto/internet.hpp")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/ofp" TYPE FILE FILES
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/ofp.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/application.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/xid_gen.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/fsm_config.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/fsm_negotiation.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/fsm_negotiation.ipp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/fsm_adaptor.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/fsm_adaptor.ipp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/ofp/v1_0" TYPE FILE FILES
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_0/message.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_0/message.ipp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_0/state.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_0/application.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_0/factory.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/ofp/v1_1" TYPE FILE FILES
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_1/message.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_1/message.ipp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_1/state.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_1/application.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_1/factory.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/ofp/v1_2" TYPE FILE FILES
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_2/message.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_2/message.ipp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_2/state.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_2/application.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_2/factory.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/ofp/v1_3" TYPE FILE FILES
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3/message.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3/message.ipp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3/state.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3/application.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3/factory.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/ofp/v1_3_1" TYPE FILE FILES
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3_1/message.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3_1/message.ipp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3_1/state.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3_1/application.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ofp/v1_3_1/factory.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/ethernet" TYPE FILE FILES "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ethernet/ethernet.hpp")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/ipv4" TYPE FILE FILES "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ipv4/ipv4.hpp")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/ipv6" TYPE FILE FILES "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ipv6/ipv6.hpp")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/proto/mpls" TYPE FILE FILES "/home/faculty/asutton/Code/onf/onfc/libflog/proto/mpls/mpls.hpp")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libflog/system" TYPE FILE FILES
    "/home/faculty/asutton/Code/onf/onfc/libflog/proto/ipv6/ipv6.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/time.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/plugin.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/plugin.ipp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/exporter.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/logger.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/config.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/socket.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/ssl_wrapper.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/selector.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/reactor.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/manager.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/acceptor.hpp"
    "/home/faculty/asutton/Code/onf/onfc/libflog/system/connection.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/faculty/asutton/Code/onf/onfc/build/libflog/utilities.test/cmake_install.cmake")
  INCLUDE("/home/faculty/asutton/Code/onf/onfc/build/libflog/buffer.test/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

