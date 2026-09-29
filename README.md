# servz

[![Build](https://github.com/bayrem-gharsellaoui/servz/actions/workflows/build.yml/badge.svg)](https://github.com/bayrem-gharsellaoui/servz/actions/workflows/build.yml)
[![Test](https://github.com/bayrem-gharsellaoui/servz/actions/workflows/test.yml/badge.svg)](https://github.com/bayrem-gharsellaoui/servz/actions/workflows/test.yml)
[![Zephyr](https://img.shields.io/badge/Zephyr-main-blue)](https://github.com/zephyrproject-rtos/zephyr)
[![Zephyr SDK](https://img.shields.io/badge/Zephyr%20SDK-1.0.1-blue)](https://github.com/zephyrproject-rtos/sdk-ng/releases/tag/v1.0.1)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://en.cppreference.com/w/cpp/17)
[![Release](https://img.shields.io/github/v/release/bayrem-gharsellaoui/servz)](https://github.com/bayrem-gharsellaoui/servz/releases)

**servz** is a tiny C++ service framework for Zephyr using static services, bounded event queues, compile-time subscriptions, and no heap required.

Think small active objects with just enough structure to stay tidy without turning your firmware into framework soup.

## Build instructions

Format code:

```bash
clang-format --style=file:${ZEPHYR_BASE}/.clang-format -i src/*.cpp include/*.hpp
```

Remove the old build:

```bash
rm -rf build/
```

Build the application:

```bash
west build -b native_sim -p -S cpp -- -DSNIPPET_ROOT="$PWD"
```

Run the application executable:

```bash
./build/zephyr/zephyr.exe
```

Run integration tests:

```bash
west twister -T tests/integration/
```

Run unit tests:

```bash
west twister -T tests/unit/
```
