cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(print_ip_main VERSION ${PROJECT_VESRION})

file(GLOB CPP_SOURCES "src/*.cpp")

# Указываем, что требуется библиотека Boost
find_package(Boost 1.86.0 REQUIRED)
#Подключаем директивы для использования Boost
include_directories(${Boost_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)


option(WITH_BOOST_TEST "Whether to build Boost test" ON)

add_executable(${PROJECT_NAME} ${CPP_SOURCES})
set_target_properties(print_ip_main PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


target_include_directories(print_ip_main
    PRIVATE "${CMAKE_BINARY_DIR}"
)

install(TARGETS print_ip_main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
