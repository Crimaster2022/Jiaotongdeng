# CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(TrafficLight_8051 C)

# 指定源码
set(SOURCES
    main.c
)

# 设置目标输出
set(TARGET traffic_light)

# 自定义 Keil C51 编译器路径（根据实际安装路径修改）
set(C51_COMPILER "C:/Keil/ARM/UV4/C51.exe")
set(C51_OPTIONS "/I include /O2 /W3 /DDEBUG")  # 根据需要添加头文件路径和编译选项

# 添加自定义命令
add_custom_target(${TARGET} ALL
    COMMAND ${C51_COMPILER} ${C51_OPTIONS} ${SOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Compiling 8051 Traffic Light project with Keil C51"
)
