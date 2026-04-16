# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lab6)

target_sources(app PRIVATE 
    src/app_thread.c
    src/data_mgr.c
    src/main.c
    src/shell_commands.c
    src/sensor_thread.c    
)
