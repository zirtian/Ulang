# Ulang

[→ 简体中文版](docs/README.zh.md)

Ulang is a parsing library for the Uranium programming language. It produces token streams and syntax trees.

## About the U Language

Uranium, or U for short, is also known as `ulang`. It is part of the WROSS open-source initiative. The Uranium language design documentation is forthcoming. For the language syntax, see the latest [Uranium Syntax Specification](docs/syntax-u26.md).

This repository contains Ulang, the parsing library for U. You can use it to build compilers and other tools for the language.

## Building and Using Ulang

Ulang is written in C++20. Make sure you have the following tools installed.

| Tool | Version Requirement | Description |
| :--- | :--- | :--- |
| `CMake` | 3.17+ | Build system. |
| `GCC` | Must Support C++20 | C++ compiler. Other compilers with C++20 support, such as `Clang` and `MSVC`, also work. |

Build instructions will be added when the Ulang library source code is available.

## Contributions

Many people have helped develop and release Ulang. The table below lists some of their contributions.

| Contributor | Contributions | Profile |
| :--- | :--- | :--- |
| ZirconiumTian | Design, development, maintenance, review, releases, documentation | [→ GitHub](https://github.com/zirtian) |
| GPT-6.2 Sol | Translation, review, maintenance, debugging | [→ OpenAI](https://openai.com) |

## License

Ulang is licensed under the [Apache License 2.0](LICENSE).
