# Copyright (c) 2026 Bayrem Gharsellaoui
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.28.0)
project(servz_unit_test)
find_package(Zephyr COMPONENTS unittest REQUIRED HINTS $ENV{ZEPHYR_BASE})

target_sources(testbinary PRIVATE
  src/main.cpp
)
