# Ulang

[→ 简体中文版](docs/README.zh.md)

Ulang is a parsing library for the Uranium programming language, designed to produce token streams and syntax trees.

## About the U Language

Uranium, or U for short, is also known as `ulang`. It is part of the WROSS open-source initiative. The Uranium language design documentation is forthcoming. For the language syntax, see the latest [Syntax Specification for the Uranium Programming Language](docs/standards/u26/syntax.md).

This repository contains Ulang, the parsing library for U. You can use it to build compilers and other tools for the language.

## Building and Using Ulang

Ulang is written in C++20. Make sure you have the following tools installed.

| Tool | Version Requirement | Description |
| :--- | :--- | :--- |
| `CMake` | 3.17+ | Build system. |
| `GCC` | Must Support C++20 | C++ compiler. Other compilers with C++20 support, such as `Clang` and `MSVC`, also work. |

Clone the Ulang repository.

```sh
git clone https://github.com/zirtian/Ulang.git
cd Ulang
```

Configure and build the project with CMake.

```sh
cmake -S . -B build
cmake --build build
```

On Linux with a single-configuration generator, this produces `build/libulang.a`. With MSVC on Windows, the static library is named `ulang.lib`. To build the bundled test executable, reconfigure with tests enabled and build again.

```sh
cmake -S . -B build -DULANG_BUILD_TESTS=ON
cmake --build build
```

This builds both the static library and the test executable. On Linux with a single-configuration generator, the executable is at `build/tests/ulang_test`. After building, run CTest from the `build` directory.

```sh
cd build
ctest --output-on-failure
```

With a multi-configuration generator such as Visual Studio, use `-C` to select the same configuration you built. For example, build with `cmake --build build --config Debug`, then run `ctest -C Debug --output-on-failure` from the `build` directory. With the Visual Studio generator, the Debug test executable is typically at `build\tests\Debug\ulang_test.exe`.

Ulang is still in early development. The lexer and parser are yet to be implemented, and the project has no version number yet. Stay tuned for further development! (\^\~\^)

## Contributions

Many people have helped develop and release Ulang. The table below lists some of their contributions.

| Contributor | Contributions | Profile |
| :--- | :--- | :--- |
| ZirconiumTian | Design, development, maintenance, review, releases, documentation | [→ GitHub](https://github.com/zirtian) |
| GPT-6.2 Sol | Translation, review, maintenance, debugging | [→ OpenAI](https://openai.com) |

## License

Ulang is licensed under the [Apache License 2.0](LICENSE).
