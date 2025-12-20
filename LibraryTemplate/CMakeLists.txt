cmake_minimum_required(VERSION 3.13)



################################################################################
## PROJECT
## name and version
################################################################################
project(MyLib LANGUAGES CXX)



################################################################################
## SETTINGS
## basic project settings before use
################################################################################
# If this project is used as a submodule, the variable should be overridden
# to "OFF" in the top-level application (to disable forced cache rewriting)
option(${PARENT}_SUBMODULE_CACHE_OVERWRITE "Enable forced cache rewriting" ON)
if (${PARENT}_SUBMODULE_CACHE_OVERWRITE)
    SET(REWRITE_FORCE "FORCE")
else()
    SET(REWRITE_FORCE "")
endif()

# Set default Release mode if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type defaulting to Release" FORCE)
    message("Build type defaulting to Release")
endif()



################################################################################
## CONFIGURATION
## project configuration
################################################################################
SET(${PARENT}_MY_LIB                         ON  CACHE BOOL "" ${REWRITE_FORCE})
if(NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    SET(${PARENT}_MY_LIB_EXAMPLE             OFF CACHE BOOL "" ${REWRITE_FORCE})
    message("${PROJECT_NAME} included as subrepository")
else()
    SET(${PARENT}_MY_LIB_EXAMPLE             ON  CACHE BOOL "" ${REWRITE_FORCE})
    message("${PROJECT_NAME} is stand alone repository")
endif()



################################################################################
## CLANG-FORMAT
## code formatting support
################################################################################
# Find clang-format (optional, won't fail if not found)
find_program(CLANG_FORMAT_EXECUTABLE 
    NAMES clang-format clang-format-18 clang-format-17 clang-format-16 clang-format-15
    DOC "Path to clang-format executable"
)

if(CLANG_FORMAT_EXECUTABLE)
    message(STATUS "clang-format found: ${CLANG_FORMAT_EXECUTABLE}")

    # Collect all source files for formatting
    file(GLOB_RECURSE ALL_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/example/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/example/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/example/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/example/*.hpp
    )

    # Create format target
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXECUTABLE}
        -i
        -style=file
        ${ALL_SOURCE_FILES}
        COMMENT "Running clang-format on all source files"
    )
    
    # Create format-check target (doesn't modify files, just checks)
    add_custom_target(format-check
        COMMAND ${CLANG_FORMAT_EXECUTABLE}
        --dry-run
        --Werror
        -style=file
        ${ALL_SOURCE_FILES}
        COMMENT "Checking code formatting with clang-format"
    )
else()
    message(STATUS "clang-format not found - formatting targets will not be available")
endif()



################################################################################
## CLANG-TIDY
## static analysis support
################################################################################
# Option to enable/disable clang-tidy during build
option(ENABLE_CLANG_TIDY "Enable clang-tidy static analysis during build" ON)

# Find clang-tidy (optional, won't fail if not found)
find_program(CLANG_TIDY_EXECUTABLE
    NAMES clang-tidy clang-tidy-18 clang-tidy-17 clang-tidy-16 clang-tidy-15
    DOC "Path to clang-tidy executable"
)

if(CLANG_TIDY_EXECUTABLE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXECUTABLE}")
    # If enabled, set CMAKE_CXX_CLANG_TIDY to run clang-tidy automatically during compilation
    if(ENABLE_CLANG_TIDY)
        set(CMAKE_CXX_CLANG_TIDY
            ${CLANG_TIDY_EXECUTABLE}
            --config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy
        )
        message(STATUS "clang-tidy enabled for build")
    endif()
else()
    message(STATUS "clang-tidy not found - static analysis targets will not be available")
endif()



################################################################################
## INCLUDING SUBDIRECTORIES
################################################################################
if (${PARENT}_MY_LIB)
    add_subdirectory(3rdparty)
    add_subdirectory(src)
endif()

if (${PARENT}_MY_LIB_EXAMPLE)
    add_subdirectory(example)
endif()