Для сборки проекта необходимо:
В CMakePresets.json у переменной CMAKE_TOOLCHAIN_FILE указать актуальный путь к vcpkg.cmake

cmake --preset=default
cmake --build build
