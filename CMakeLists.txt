# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

list(APPEND SNIPPET_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(zephyt-cpp-arch)

target_include_directories(app PRIVATE
  include
)

target_sources(app PRIVATE
  src/main.cpp
  src/heap_trap.cpp
  src/event_manager.cpp
  src/service.cpp
  src/service_a.cpp
  src/service_b.cpp
)

zephyr_iterable_section(
  NAME service_registration
  GROUP RODATA_REGION
)

zephyr_linker_sources(
  SECTIONS
  sections-rom.ld
)
