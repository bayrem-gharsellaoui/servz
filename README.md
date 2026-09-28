# zephyr-cpp-arch

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
