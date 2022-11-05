cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(BASEPATH "${CMAKE_SOURCE_DIR}")

project(bayan VERSION ${PROJECT_VESRION})

ADD_DEFINITIONS(-DBoost_USE_STATIC_LIBS=ON)

configure_file(version.h.in version.h)

set(srcs
    main.cpp
    bayan.cpp)

find_package(Boost COMPONENTS program_options filesystem REQUIRED)

add_executable(bayan ${srcs})

target_link_libraries(bayan
    ${Boost_LIBRARIES}
)

set_target_properties(bayan PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_compile_options(bayan PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
