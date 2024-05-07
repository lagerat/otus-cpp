cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1.0" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(GraphicsEditor VERSION ${PROJECT_VESRION})

add_subdirectory(googletest EXCLUDE_FROM_ALL)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(GraphicsEditor main.cpp src/Models/Document.cpp src/Models/Document.h src/Models/GraphicPrimitive.cpp src/Models/GraphicPrimitive.h src/Models/Line.cpp src/Models/Line.h src/Models/Rectangle.cpp src/Models/Rectangle.h src/Controllers/DocumentController.cpp src/Controllers/DocumentController.h src/Controllers/PrimitiveController.cpp src/Controllers/PrimitiveController.h src/Views/DocumentView.cpp src/Views/DocumentView.h src/math/MathHelper.h)

add_executable(unitTests tests/tests.cpp)

set_target_properties(GraphicsEditor PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_link_libraries(unitTests
        gtest
        gtest_main
)

if (MSVC)
    target_compile_options(GraphicsEditor PRIVATE
        /W4
    )
    target_compile_options(unitTests PRIVATE
        /W4
    )
else ()
    target_compile_options(GraphicsEditor PRIVATE
        -Wall -Wextra -pedantic -Werror -Wno-error=unused-parameter
    )
    target_compile_options(unitTests PRIVATE
        -Wall -Wextra -pedantic -Werror -Wno-error=unused-parameter
    )
endif()



install(TARGETS GraphicsEditor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(unitTests unitTests)
