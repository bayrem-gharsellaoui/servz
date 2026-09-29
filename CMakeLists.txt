# Copyright (c) 2026 Bayrem Gharsellaoui
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_SERVZ)
  zephyr_library_named(servz)

  zephyr_library_sources(
    src/service.cpp
    src/event_manager.cpp
  )

  zephyr_include_directories(
    include
  )

  zephyr_iterable_section(
    NAME service_registration
    GROUP RODATA_REGION
  )

  zephyr_linker_sources(
    SECTIONS
    ${CMAKE_CURRENT_LIST_DIR}/sections-rom.ld
  )
endif()
