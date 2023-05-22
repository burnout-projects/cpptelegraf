include(GNUInstallDirs)

set(hdrs
    ${PROJECT_SOURCE_DIR}/include/protocol.h
    ${PROJECT_SOURCE_DIR}/include/telegrafclient.h
)

set(srcs
    protocol.cpp
    clientbase.cpp
    telegrafclient.cpp)

# Define the library target
add_library(${PROJECT_NAME} ${srcs} ${hdrs})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME}
    PROPERTIES PUBLIC_HEADER "${hdrs}"
)
# Force PIC
set_target_properties(${PROJECT_NAME}
    PROPERTIES POSITION_INDEPENDENT_CODE ON)
# And enable IPO/LTO/LTCG only in non-Debug mode builds
if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND __ipo_ok)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
endif()

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Config
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

export(
    TARGETS ${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
)
install(
    EXPORT ${PROJECT_NAME}Config
    DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake"
    NAMESPACE ${PROJECT_NAME}::
)
