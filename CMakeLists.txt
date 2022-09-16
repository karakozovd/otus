cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(BASEPATH "${CMAKE_SOURCE_DIR}")

project(simpleeditor VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

set(srcs
    consolebackend.cpp
    view.cpp
    model.cpp
    main.cpp)

add_executable(simpleeditor ${srcs})

set_target_properties(simpleeditor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(simpleeditor
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(simpleeditor PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS simpleeditor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
