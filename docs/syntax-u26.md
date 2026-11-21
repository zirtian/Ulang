# About the U26 Syntax Specification

[→ 简体中文版](syntax-u26.zh.md)

U26 is the 2026 standard for the Uranium programming language. It defines the language's syntax and semantics and specifies how conforming compilers process U programs.

## Contributors

The following contributors prepared the U26 Syntax Specification:

| Contributor | Contributions | Profile |
| :--- | :--- | :--- |
| ZirconiumTian | Drafting, review, release | [→ GitHub](https://github.com/zirtian) |
| 甘城maomao | Review | [→ GitHub](https://github.com/vanitas-NEKO) |
| GPT-6.2 Sol | Translation, proofreading | [→ OpenAI](https://openai.com) |

## License

This specification, including `docs/syntax-u26.md` and its other language versions (`docs/syntax-u26.*.md`), is licensed under [Creative Commons Attribution-NonCommercial 4.0 International](https://creativecommons.org/licenses/by-nc/4.0/).

<br>

# Syntax Specification for the Uranium Programming Language (U26 Standard)

ZirconiumTian, November 21, 2026

## Lexical Structure

### I. Identifiers

An **identifier**, abbreviated **Id**, is a lexical element used to name variables, functions, members, methods, structures, and other entities in Uranium source code. In the ASCII range, an identifier may contain uppercase and lowercase letters (`A`–`Z` and `a`–`z`), digits (`0`–`9`), and underscores (`_`). It must start with a character other than a digit.

The following are valid identifiers.

- `function_name`
- `Tokenizer`
- `decodeUTF32`

U26 also permits certain fullwidth and halfwidth Unicode characters in identifiers. The following Unicode spaces and punctuation marks are excluded.

| Character | Unicode code point | Character | Unicode code point |
| :--- | :--- | :--- | :--- |
| `　` | U+3000 | `、` | U+3001 |
| `‘` | U+2018 | `’` | U+2019 |
| `“` | U+201C | `”` | U+201D |
| `：` | U+FF1A | `；` | U+FF1B |
| `，` | U+FF0C | `。` | U+3002 |

The following examples illustrate the use of non-ASCII characters.

| Identifier | Valid | Identifier | Valid |
| :--- | :--- | :--- | :--- |
| `甲乙` | Yes | `甲，乙` | No |
| `“”` | No | `你好U语言` | Yes |
| `→here` | Yes | `Software：Installer` | No |

Source file encodings may vary across platforms and locale settings. For this reason, extensive use of non-ASCII characters in identifiers is discouraged.

> **Compiler rule.** The compiler should accept identifiers made up of valid ASCII and Unicode characters without an error or warning, provided they do not match a keyword or type name.<br>
> Diagnostic for an invalid character: `Unexpected character in identifiers.`

An identifier cannot have the same spelling as a keyword or type name.

### II. Keywords

**Keywords**, abbreviated **Kwd**, are a special category of identifiers at the lexical level.

| Keyword | Meaning |
| :--- | :--- |
| `and` | Logical AND. |
| `break` | Exits a `while` or `for` loop. |
| `case` | Used in a `switch` statement. |
| `continue` | Ends the current iteration of a `while` or `for` loop and returns control to the start of the loop. |
| `else` | Introduces an alternative branch. |
| `failed` | Introduces a recovery block for error handling. |
| `false` | Boolean literal for the false value. |
| `fn` | Declares a function. |
| `for` | Introduces a `for` loop. |
| `if` | Introduces a conditional branch. |
| `in` | Used in `for` statements, in tests for whether an integer or floating-point value lies within a range, and in out-of-line implementations of structure members. |
| `or` | Logical OR. |
| `none` | Represents the absence of a value or the return type of a function that returns no value. |
| `not` | Logical negation. |
| `report` | Reports an error that can be caught by a `failed` statement. |
| `return` | Returns from a function or method. |
| `struct` | Declares a structure. |
| `switch` | Introduces a `switch` statement. |
| `true` | Boolean literal for the true value. |
| `using` | Imports a module. It is allowed only at global scope or in an `if` or `else` branch directly within global scope. |
| `while` | Introduces a `while` loop. |

**Built-in methods** follow separate rules. See **Syntax and Semantics, Section III**. The keywords listed above are reserved and cannot be used as identifier names.

> **Compiler rule.** If a keyword is used as an identifier, the compiler should report an error and stop compilation.<br>
> Diagnostic: `Should not be used here as an identifier`

### III. Type Names

A **type name**, abbreviated **Type** and also called **TypeName**, is a special identifier that names a data type.

| Type name | Meaning |
| :--- | :--- |
| `int8` | Signed integer with 7 data bits. |
| `int16` | Signed integer with 15 data bits. |
| `int32` | Signed integer with 31 data bits. |
| `int64` | Signed integer with 63 data bits. |
| `uint8` | 8-bit unsigned integer. |
| `uint16` | 16-bit unsigned integer. |
| `uint32` | 32-bit unsigned integer. |
| `uint64` | 64-bit unsigned integer. |
| `char` | 8-bit character value and the element type of `string`.<br>With `ch: char = 65`, U treats `ch` as `'A'` by default. |
| `rune` | 32-bit character value and the element type of `string32`. It follows the character behavior described above. |
| `string` | UTF-8 string. |
| `string32` | UTF-32 string. |
| `float32` | Floating-point number with 31 data bits. |
| `float64` | Floating-point number with 63 data bits. |
| `bool` | Boolean value. |

The type names listed above are reserved and cannot be used as identifier names.

> **Compiler rule.** If a type name is used as an identifier, the compiler should report an error and stop compilation.<br>
> Diagnostic: `Should not be used here as an identifier`

### IV. Operators

An **operator**, abbreviated **Op**, is a symbol that denotes an operation or a relation between values. Operators are classified as **unary**, **binary**, or **ternary**. Some operators are written as keywords.

| Arity | General form | Common operations |
| :--- | :--- | :--- |
| 1 | `[Op][Id]` | Pointer, reference, and view operations, logical negation, increment, decrement, and subscripting. |
| 2 | `[Id][Op][Id]` | Arithmetic and comparisons. |
| 3 | `[Id][Op][Id][Op][Id]` | The `?:` conditional operator and the `in` range test. |

Unary operators in U

| Operator | Meaning |
| :--- | :--- |
| `not a` | Logically negates the value or expression a. |
| `&a` | Takes a reference to a. |
| `@a` | Returns a read-only view of a. |
| `->a` | Denotes the pointer target or address of a. |
| `~a` | Inverts the bits of the integer or floating-point value or expression a. |
| `++a` | Increments the integer a by 1. |
| `--a` | Decrements the integer a by 1. |
| `-a` | Negates a, which must have an integer or floating-point type. |

Binary operators in U

| Operator | Meaning |
| :--- | :--- |
| `a + b` | Adds the integer or floating-point operands a and b. |
| `a - b` | Subtracts the integer or floating-point operand b from a. |
| `a * b` | Multiplies the integer or floating-point operands a and b. |
| `a / b` | Divides the integer or floating-point operand a by b. The divisor must be nonzero. |
| `a[b]` | Accesses the element at index b of the slice or array a. The index must have a signed or unsigned integer type. |
| `a.b` | Accesses member or method b of structure a, or accesses built-in method b on a value a that provides it. |
| `a = b` | Assigns b to a. The type determines whether the assignment copies the value, points to it, or creates a view. |
| `a > b` | Tests whether a is greater than b. |
| `a < b` | Tests whether a is less than b. |
| `a == b` | Tests whether a is equal to b. |
| `a != b` | Tests whether a is unequal to b. |
| `a >= b` | Tests whether a is greater than or equal to b. |
| `a <= b` | Tests whether a is less than or equal to b. |
| `a and b` | Tests whether both Boolean operands are true. |
| `a or b` | Tests whether at least one Boolean operand is true. |

All six comparison operators return a `bool`.

Ternary operators in U

| Operator | Meaning |
| :--- | :--- |
| `a ? b : c` | The condition a is a Boolean value or expression. When a is `true`, only b is evaluated or executed. When a is `false`, only c is evaluated or executed. |
| `a in b, c` | Tests whether the integer or floating-point value a lies in the interval with lower bound b and upper bound c. The result is a `bool`. Both endpoints are inclusive. A bound written as `none` omits the comparison on that side. |

For example, `age in 0, 18` is equivalent to `(age >= 0) and (age <= 18)`, and `age in none, -1` is equivalent to `age <= -1`.

### V. Delimiters

**Delimiters**, abbreviated **Spt**, separate statements and mark scope boundaries. U has the following delimiters.

`;` `(` `)` `[` `]` `{` `}` `,`

A semicolon (`;`) terminates a statement. Parentheses (`()`) group an expression to control precedence. Square brackets (`[]`) are used for subscripting. Braces (`{}`) mark scope boundaries. A comma (`,`) separates expressions.

### VI. Literals

A **literal**, abbreviated **Lit**, represents a primitive value that can be determined at compile time. U has the following forms of literals.

#### i. Integers

| Notation | Example | Decimal value | Rule |
| :--- | :--- | :--- | :--- |
| Decimal | 42 | 42 | A sequence of decimal digits with no decimal point. The first digit is nonzero, except for `0` itself. |
| Octal | 033 | 27 | Begins with `0` followed by digits from `0` through `7`. |
| Binary | 0b110 | 6 | Begins with `0b` followed by binary digits (`0` or `1`). |
| Hexadecimal | 0x0f | 15 | Begins with `0x` followed by digits from `0` through `9` or letters from `a` through `f`. |

The expression `-5` consists of the unary operator `-` and the integer literal `5`. Letters in the prefixes and digit sequences of binary and hexadecimal literals are case-insensitive. Both `0x7c00` and `0X26FA` are valid.

#### ii. Floating-Point Numbers

Floating-point literals are written as decimal fractions, such as `3.14` and `0.5`. A decimal point (`.`) must have at least one decimal digit on each side. The forms `.5` and `5.` are invalid floating-point literals.

Leading zeroes do not change the radix of a floating-point literal. For example, `033.0` represents decimal 33. In `-3.14`, the `-` is a unary operator.

Floating-point literals have no type suffix. When the context requires `float32` or `float64`, the literal takes that type. If the context specifies no floating-point type, the default is `float64`.

#### iii. Characters

A character literal is enclosed in single quotes. Its contents consist of one character written directly or one escape sequence. After decoding escapes, the literal must contain exactly one Unicode scalar value. Empty character literals, literals containing multiple characters, and literals containing a line break in the source are invalid.

Character and string literals share the following escape sequences. Each starts with a backtick (U+0060).

| Escape sequence | Meaning |
| :--- | :--- |
| ``` `` ``` | Backtick. |
| `` `' `` | Single quote. |
| `` `" `` | Double quote. |
| `` `n `` | Line feed, U+000A. |
| `` `r `` | Carriage return, U+000D. |
| `` `t `` | Horizontal tab, U+0009. |
| `` `0 `` | Null character, U+0000. |

Write a literal backtick as two consecutive backticks. A backslash can appear directly. A quote matching the opening quote must be escaped. The compiler should report an error for any escape sequence absent from the table.

A character that fits in one UTF-8 byte can be used as a `char` or a `rune`. Examples include `'A'` and `` '`n' ``. A character that requires multiple UTF-8 bytes can be used only as a `rune`. One example is `'中'`. When the context does not specify a character type, a single-byte character defaults to `char` and a multibyte character defaults to `rune`.

```text
letter: char = 'A';
han: rune = '中';
```

#### iv. Strings

A string literal is enclosed in double quotes and may contain zero or more characters. `""` is the empty string. Strings use the same escape rules as character literals. Use `` `" `` to include a double quote and `` `n `` to include a line feed. A string literal cannot span source lines directly.

The same literal syntax is used for `string` and `string32`. A `string` encodes its contents in UTF-8 and has elements of type `char`. A `string32` encodes its contents in UTF-32 and has elements of type `rune`. When the context does not specify a string type, the default is `string`.

```text
message: string = "Hello`nU Language";
message32: string32 = "你好`nU 语言";
empty: string = "";
```

##### Interpolated Strings

An interpolated string starts with a lowercase `f` immediately followed by the opening double quote. A `{Expression}` field in the string marks an interpolation. The expressions are evaluated once each from left to right, and the text representation of each result is inserted in the corresponding field. An interpolation field must contain a complete U expression. An empty `{}` is invalid.

Outside interpolation fields, string text follows the ordinary backtick escape rules. The sequences `{{` and `}}` represent a single opening and closing brace, respectively. An unpaired brace outside an interpolation field is a syntax error. In an ordinary string, braces are kept as written.

Interpolated strings follow the same result type rules as ordinary strings. For example, if `name` is `"U"`, `f"hello, {name}!"` produces `"hello, U!"`. The expression `f"{{{1 + 2}}}"` produces `"{3}"`.

### VII. Comments

A **comment**, abbreviated **com**, is explanatory text in source code that has no effect on program logic or compilation. U has two forms of comments.

- Line comment — `// Comments...`
- Block comment — `/* Comments... */`

U uses the same comment delimiters as C++. In U, block comments can nest. For example, in `/* Comments /* Comments */ Comments */`, the inner `*/` closes only the inner comment. The block comment ends at the final `*/`.
