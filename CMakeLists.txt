# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

project ("gengo")

# Включите подпроекты.
add_subdirectory ("gengo")

set_property (TARGET ${PROJECT_NAME}
  PROPERTY
    # Enable C++17 standard compliance
    CXX_STANDARD 17
)