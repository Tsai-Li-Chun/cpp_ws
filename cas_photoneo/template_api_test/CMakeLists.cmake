cmake_minimum_required (VERSION 3.10)

if(POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

project(isPhoXiControlRunning)

set(CMAKE_RELEASE_POSTFIX "_Release")
set(CMAKE_DEBUG_POSTFIX "_Debug")

if (UNIX AND NOT APPLE)
    add_compile_options(-std=c++1y)
    add_compile_options(-pthread)
endif(UNIX AND NOT APPLE)

set(Files
    ${isPhoXiControlRunning_SOURCE_DIR}/main.cpp
)

add_executable(isPhoXiControlRunning
    ${Files}
)

find_package(PhoXi REQUIRED CONFIG PATHS "$ENV{PHOXI_CONTROL_PATH}")

if(UNIX AND NOT APPLE)
    target_link_libraries(isPhoXiControlRunning
        ${PHOXI_LIBRARY}
        rt
    )
else()
    target_link_libraries(isPhoXiControlRunning
        ${PHOXI_LIBRARY}
    )
endif()

if(MSVC)
    add_custom_command(TARGET isPhoXiControlRunning POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PHOXI_DLL_DEBUG}"
            $<TARGET_FILE_DIR:isPhoXiControlRunning>
    )

    add_custom_command(TARGET isPhoXiControlRunning POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PHOXI_DLL_RELEASE}"
            $<TARGET_FILE_DIR:isPhoXiControlRunning>
    )
endif()

target_include_directories(isPhoXiControlRunning PUBLIC 
    ${PHOXI_INCLUDE_DIRS}
)