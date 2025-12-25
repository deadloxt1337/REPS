project(REPS)

file(GLOB_RECURSE INCLUDE_FILES
    *.h
)

file(GLOB_RECURSE SOURCE_FILES
    *.cpp
)

add_executable(${PROJECT_NAME}
    ${INCLUDE_FILES}
    ${SOURCE_FILES}
)

if (WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE /W0 /bigobj)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -w)
endif ()

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -fexceptions -pthread)
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    fmt::fmt
    enet
)

set_target_properties(REPS PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/data
)
