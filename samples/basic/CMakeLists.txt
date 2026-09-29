# Copyright (c) 2026 Bayrem Gharsellaoui
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(app)

list(APPEND EXTRA_ZEPHYR_MODULES
  ${CMAKE_CURRENT_LIST_DIR}/../..
)

target_include_directories(app PRIVATE
  include
)

target_sources(app PRIVATE
  src/main.cpp
  src/service_a.cpp
  src/service_b.cpp
  src/heap_trap.cpp
)
