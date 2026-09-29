# Copyright (c) 2026 Bayrem Gharsellaoui
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_SERVZ)
  zephyr_include_directories(include src)
  add_subdirectory(src)
endif()
