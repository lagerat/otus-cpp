cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1.0" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(bulkmt VERSION ${PROJECT_VESRION})

find_package(Threads)
find_package(Boost)

add_subdirectory(googletest EXCLUDE_FROM_ALL)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(bulkmt main.cpp src/Bulk.cpp src/Bulk.h src/FileWriter.cpp src/FileWriter.h src/LogWriter.cpp src/LogWriter.h src/IObserver.h async.cpp async.h src/ThreadPool.h)

add_library(async SHARED src/Bulk.cpp src/Bulk.h src/FileWriter.cpp src/FileWriter.h src/LogWriter.cpp src/LogWriter.h src/IObserver.h async.cpp async.h src/ThreadPool.h)

add_executable(unitTests tests/tests.cpp)

set_target_properties(bulkmt PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(unitTests
        gtest
        gtest_main
)

target_include_directories(async
        PRIVATE ${Boost_INCLUDE_DIR})

target_include_directories(async
        PRIVATE ${Boost_INCLUDE_DIR})

target_link_libraries(async
        PRIVATE ${Boost_LIBRARY_DIR})

if (MSVC)
    target_compile_options(bulkmt PRIVATE
        /W4
    )
    target_compile_options(unitTests PRIVATE
        /W4
    )
else ()
    target_compile_options(bulkmt PRIVATE
        -Wextra -pedantic -Werror
    )
    target_compile_options(unitTests PRIVATE
        -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulkmt RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(unitTests unitTests)
