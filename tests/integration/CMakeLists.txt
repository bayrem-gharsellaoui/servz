# Copyright (c) 2026 Bayrem Gharsellaoui
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.28.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(servz_integration_test)

list(APPEND EXTRA_ZEPHYR_MODULES
  ${CMAKE_CURRENT_LIST_DIR}/../..
)

target_include_directories(app PRIVATE
  include
)

target_sources(app PRIVATE
  src/test_services.cpp
  src/registration_test.cpp
  src/delivery_test.cpp
  src/overflow_test.cpp
  src/startup_test.cpp
)
