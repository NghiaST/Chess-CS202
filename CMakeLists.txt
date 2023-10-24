cmake_minimum_required(VERSION 3.16)

set(NAME Chess)
set(SFMLDIR ${CMAKE_BINARY_DIR}/include)
set(SRCDIR src)
set(HEADERDIR ${SRCDIR}/header)
set(SOURCEDIR ${SRCDIR}/source)
set(OTHERDIR ${SRCDIR}/other)
project(${NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE SOURCES ${SOURCEDIR}/main.cpp)
file(GLOB_RECURSE HEADERS ${HEADERDIR}/main.hpp)
file(GLOB_RECURSE RESOURCES ${OTHERDIR}/resource.rc)

include_directories(${HEADERDIR} ${SFMLDIR})
add_executable(${NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${NAME} PRIVATE sfml-graphics)
target_include_directories(${NAME} PRIVATE ${HEADERDIR} ${SFMLDIR})

if(WIN32)
    add_custom_command(
        TARGET ${NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${NAME}>
        VERBATIM)
endif()

install(TARGETS ${NAME})