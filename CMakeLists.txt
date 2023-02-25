cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1.0" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(helloworld_cli VERSION ${PROJECT_VESRION})

add_subdirectory(googletest EXCLUDE_FROM_ALL)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(helloworld_cli main.cpp  limited_allocator.h allocator.h)

add_executable(unitTests tests/tests.cpp  limited_allocator.h allocator.h)

set_target_properties(helloworld_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(unitTests
        gtest
        gtest_main
)

#if (MSVC)
#    target_compile_options(helloworld_cli PRIVATE
#        /W4
#    )
#    target_compile_options(unitTests PRIVATE
#        /W4
#    )
#else ()
#    target_compile_options(helloworld_cli PRIVATE
#        -Wall -Wextra -pedantic -Werror
#    )
#    target_compile_options(unitTests PRIVATE
#        -Wall -Wextra -pedantic -Werror
#    )
#endif()



install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(unitTests unitTests)
