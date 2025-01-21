# ESP-IDF Project Configuration for Blinky System
cmake_minimum_required(VERSION 3.16)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

set(PROJECT_NAME "multi_led_controller")
set(PROJECT_VERSION "1.1.0")

project(${PROJECT_NAME})