# Ulang

[→ English Version](../README.md)

Ulang 是 Uranium 编程语言的语法解析库, 用于生成 token 流和语法树。

## 关于 U 语言

Uranium 编程语言简称 U 语言, 通用名称 ulang, 属于轮动开放软件 WROSS 计划的项目之一。关于 U 语言, 敬请期待 Uranium 语言设计文档, 或请参阅最新版 [U 编程语言语法规范文档](./standards/u26/syntax.zh.md)。

本仓库 Ulang 仅为 U 语言的语法解析库, 可以用来制作适用于 U 语言的编译器等。

## 构建和使用

Ulang 目前使用 C++20 写成。请确保您准备下列工具:

| 工具 | 版本要求 | 描述 |
| :--- | :--- | :--- |
| `CMake` | 3.17+ | 构建系统。 |
| `GCC` | 须支持 C++20 | 项目编译器。其它支持 C++20 的编译器, 如较新的 `MSVC`, `Clang` 也可。 |

然后通过下列命令克隆 Ulang 仓库:

```sh
git clone https://github.com/zirtian/Ulang.git
cd Ulang
```

接着, 通过下列命令配置 CMake 目标并构建:

```sh
cmake -S . -B build
cmake --build build
```

这会在生成目录 `build` 产出一个静态库文件 `libulang.a`。对于 Windows MSVC 构建, 则是 `ulang.lib`。如果要运行附带的可执行测试文件, 请使用下列命令重新配置:

```sh
cmake -S . -B build -DULANG_BUILD_TESTS=ON
cmake --build build
```

这会同时构建静态库和测试可执行文件。在 Linux 上使用单配置生成器时, 测试可执行文件位于 `build/tests/ulang_test`。构建后, 在 `build` 目录运行 CTest:

```sh
cd build
ctest --output-on-failure
```

如果使用 Visual Studio 等多配置生成器, 请用 `-C` 选择与构建一致的配置。例如, 用 `cmake --build build --config Debug` 构建后, 在 `build` 目录运行 `ctest -C Debug --output-on-failure`。使用 Visual Studio 生成器时, 此配置下的测试可执行文件通常位于 `build\tests\Debug\ulang_test.exe`。

不过, 当前开发进度不能真正让 Ulang 库完整工作, 且尚未分配版本。敬请期待后续开发! (\^\~\^)

## 贡献

Ulang 的制作和发行离不开多方贡献。下表是手动收录的部分贡献信息:

| 贡献者 | 贡献类型 | 贡献者页面 |
| :--- | :--- | :--- |
| ZirconiumTian | 设计、开发、维护、审查、发行、文档 | [→ GitHub](https://github.com/zirtian) |
| GPT-6.2 Sol | 翻译、审查、维护、调试 | [→ OpenAI](https://openai.com) |

## 许可证

Ulang 遵循 [Apache 2.0 许可证](../LICENSE)。
