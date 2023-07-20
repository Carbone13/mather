add_subdirectory(glfw)

if (APPLE)
    list(APPEND OS_DEPENDANT "-framework OpenGL")
elseif (WIN32)
    list(APPEND OS_DEPENDANT "-lglu32 -lopengl32")
    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
else ()
    list(APPEND OS_DEPENDANT "-lGL -lGLU -lX11")
endif ()

add_executable(mather-demo main.cpp main.hpp)
target_link_libraries(mather-demo mather glfw ${OS_DEPENDANT})