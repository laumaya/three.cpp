cmake_minimum_required(VERSION 3.7)
project(three_quick)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Quick REQUIRED)
find_package(Qt5Core REQUIRED)

set(CMAKE_CXX_STANDARD 11)

set(THREEQ_HDRDIRS
        cameras
        elements
        interact
        materials
        objects
        scene
        textures)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

add_library(threeppq SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(threeppq PUBLIC
        $<BUILD_INTERFACE:${THREE_ROOT}>
        $<INSTALL_INTERFACE:include>)
target_link_libraries(threeppq PUBLIC threepp Qt5::Core Qt5::Gui Qt5::Quick)

set_target_properties(threeppq PROPERTIES SOVERSION ${THREE_VERSION})

install(TARGETS threeppq
        EXPORT threeppq
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        COMPONENT quick)

install(EXPORT threeppq
        DESTINATION lib/cmake/threepp
        FILE threeppq-config.cmake
        COMPONENT quick)

foreach(DIR in ${THREEQ_HDRDIRS})
    file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${DIR}/*.h)
    install(FILES ${HEADERS}
            DESTINATION include/threepp/quick/${DIR}
            COMPONENT quick)
endforeach(DIR in ${THREE_HDRDIRS})

file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
install(FILES ${HEADERS}
        DESTINATION include/threepp/quick
        COMPONENT quick)
