cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_printer VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

add_executable(ip_printer printer.h
			  main.cpp)

set_target_properties(ip_printer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_printer
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(ip_printer PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS ip_printer RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
