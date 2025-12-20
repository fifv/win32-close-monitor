cmake_minimum_required(VERSION 3.30.0)
project(CloseMonitor VERSION 0.1.0)

include(CTest)
enable_testing()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    enable_language("RC")
endif()

add_executable(CloseMonitor WIN32 src/CloseMonitor.cpp src/assets/app.rc)
target_precompile_headers(CloseMonitor PUBLIC
    <windows.h>
)
target_compile_definitions(CloseMonitor PRIVATE UNICODE WIN32_LEAN_AND_MEAN)


include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)
add_executable(CloseMonitorOnUnplugged src/CloseMonitorOnUnplugged.cpp src/assets/app.rc)
target_precompile_headers(CloseMonitorOnUnplugged PUBLIC
    <windows.h>
)
target_compile_features(CloseMonitorOnUnplugged PUBLIC cxx_std_23)
target_link_libraries(CloseMonitorOnUnplugged fmt::fmt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
