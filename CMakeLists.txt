## CMakeLists.txt
option(foo_build_tests "Build all of foo's unit tests." ON)

project(foo)
cmake_minimum_required(VERSION 2.6.2)

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

#include_directories("/home/wangj37/Software/googletest/shared/debug/include")
#include_directories("/home/wangj37/Software/googlemock/shared/debug/include")

include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")

#link_directories("/home/wangj37/Software/googletest/shared/debug/lib")
#link_directories("/home/wangj37/Software/googlemock/shared/debug/lib")

set(foo_SOURCES
    main.cc
    html_parser.h
    http_fetch.h)
add_executable(foo ${foo_SOURCES})

if (foo_build_tests)
    enable_testing()
    add_executable(html_parser_test
        html_parser_test.cc
        html_parser.h
        http_fetch.h)
    target_link_libraries(html_parser_test
        pthread)
    target_link_libraries(html_parser_test
        gmock
        gmock_main)
    target_link_libraries(html_parser_test
        gtest
        gtest_main)
    add_test(html-tests html_parser_test)
    set_target_properties(html_parser_test
      PROPERTIES
      COMPILE_DEFINITIONS "GTEST_LINKED_AS_SHARED_LIBRARY=1")
endif()
