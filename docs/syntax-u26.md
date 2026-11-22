# About the U26 Syntax Specification

[→ 简体中文版](syntax-u26.zh.md)

U26 is the 2026 standard for the Uranium programming language. This document specifies U26's lexical and syntactic rules, provides examples, and defines the corresponding compiler diagnostics.

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

> **Compiler rule:** The compiler should accept identifiers made up of valid ASCII and Unicode characters without an error or warning, provided they do not match a keyword or type name.<br>
> If an identifier contains an invalid character, report `Unexpected character in identifiers.`

An identifier cannot have the same spelling as a keyword or type name.

### II. Keywords

**Keywords**, abbreviated **Kwd**, are a special category of identifiers at the lexical level.

| Keyword | Meaning |
| :--- | :--- |
| `and` | Logical AND. |
| `break` | Jump statement used in a loop. |
| `case` | Used in a `switch` statement. |
| `continue` | Jump statement used in a loop. |
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
| `return` | Return statement used in functions and methods. |
| `struct` | Declares a structure. |
| `switch` | Introduces a `switch` statement. |
| `true` | Boolean literal for the true value. |
| `using` | Imports a module. It is allowed only at global scope or in an `if` or `else` branch directly within global scope. |
| `while` | Introduces a `while` loop. |

The keywords listed above are reserved and cannot be used as identifiers.

> **Compiler rule:** If a keyword is used as an identifier, the compiler should report an error and stop compilation.<br>
> Diagnostic: `Should not be used here as an identifier`

### III. Type Names

A **type name**, abbreviated **Type** and also called **TypeName**, is a special identifier that names a data type.

| Type name | Meaning |
| :--- | :--- |
| `int8`, `int16`, `int32`, `int64` | Signed integers. |
| `uint8`, `uint16`, `uint32`, `uint64` | Unsigned integers. |
| `char`, `rune` | Characters. |
| `string` | UTF-8 string. |
| `string32` | UTF-32 string. |
| `float32`, `float64` | Floating-point numbers. |
| `bool` | Boolean value. |

The type names listed above are reserved and cannot be used as identifier names.

> **Compiler rule:** If a type name is used as an identifier, the compiler should report an error and stop compilation.<br>
> Diagnostic: `Should not be used here as an identifier`

### IV. Operators

An **operator**, abbreviated **Op**, is a symbol that denotes an operation or a relation between values. Operators are classified as **unary**, **binary**, or **ternary**. Some operators are written as keywords.

| Arity | General form | Common operations |
| :--- | :--- | :--- |
| 1 | `Op Id` | Pointer, reference, and view operations, logical negation, increment, and decrement. |
| 2 | `Id Op Id` | Arithmetic and comparisons. |
| 3 | `Id Op Id Op Id` | The `?:` conditional operator and the `in` range test. |

Unary operators in U

| Operator | Meaning |
| :--- | :--- |
| `not a` | Logically negates the value or expression a. |
| `&a` | A writable reference to a. |
| `@a` | Returns a read-only view of a. |
| `->a` | Denotes the pointer target or address of a. |
| `~a` | Inverts the bits of the integer or floating-point value or expression a. |
| `++a` | Integer increment. |
| `--a` | Integer decrement. |
| `-a` | Negates a, which must have an integer or floating-point type. |

Binary operators in U

| Operator | Meaning |
| :--- | :--- |
| `a + b` | Adds the integer or floating-point operands a and b. |
| `a - b` | Subtracts the integer or floating-point operand b from a. |
| `a * b` | Multiplies the integer or floating-point operands a and b. |
| `a / b` | Integer or floating-point division. |
| `a[b]` | Accesses the element at index b of the slice or array a. The index must have a signed or unsigned integer type. |
| `a.b` | Accesses member or method b of structure a, or accesses built-in method b on a value a that provides it. |
| `a = b` | Assignment. |
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
| `a ? b : c` | Conditional expression. a is the condition, and b and c are the two branches. |
| `a in b, c` | Range test. b and c are the lower and upper bounds, respectively. Either bound can be written as `none`. |

For example, `age in 0, 18` specifies both bounds, while `age in none, -1` specifies only the upper bound.

### V. Delimiters

**Delimiters**, abbreviated **Spt**, separate statements and mark scope boundaries. U has the following delimiters.

`;` `(` `)` `[` `]` `{` `}` `,`

A semicolon (`;`) terminates a statement. Parentheses (`()`) group an expression to control precedence. Square brackets (`[]`) are used for subscripting. Braces (`{}`) mark scope boundaries. A comma (`,`) separates expressions.

### VI. Literals

A **literal**, abbreviated **Lit**, directly represents a value in source code, such as an integer, a floating-point number, a character, or a string.

#### 1. Integers

| Notation | Example | Decimal value | Rule |
| :--- | :--- | :--- | :--- |
| Decimal | 42 | 42 | A sequence of decimal digits with no decimal point. The first digit is nonzero, except for `0` itself. |
| Octal | 033 | 27 | Begins with `0` followed by digits from `0` through `7`. |
| Binary | 0b110 | 6 | Begins with `0b` followed by binary digits (`0` or `1`). |
| Hexadecimal | 0x0f | 15 | Begins with `0x` followed by digits from `0` through `9` or letters from `a` through `f`. |

The expression `-5` consists of the unary operator `-` and the integer literal `5`. Letters in the prefixes and digit sequences of binary and hexadecimal literals are case-insensitive. Both `0x7c00` and `0X26FA` are valid.

#### 2. Floating-Point Numbers

Floating-point literals are written as decimal fractions, such as `3.14` and `0.5`. A decimal point (`.`) must have at least one decimal digit on each side. The forms `.5` and `5.` are invalid floating-point literals.

Leading zeroes do not change the radix of a floating-point literal. For example, `033.0` represents decimal 33. In `-3.14`, the `-` is a unary operator.

Floating-point literals have no type suffix.

#### 3. Characters

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

A character that fits in one UTF-8 byte can be used as a `char` or a `rune`. Examples include `'A'` and `` '`n' ``. A character that requires multiple UTF-8 bytes, such as `'中'`, can be used only as a `rune`.

```text
letter: char = 'A';
han: rune = '中';
```

#### 4. Strings

A string literal is enclosed in double quotes and may contain zero or more characters. `""` is the empty string. Strings use the same escape rules as character literals. Use `` `" `` to include a double quote and `` `n `` to include a line feed. A string literal cannot span source lines directly.

The same literal syntax can be used in `string` and `string32` declarations.

```text
message: string = "Hello`nU Language";
message32: string32 = "你好`nU 语言";
empty: string = "";
```

##### Interpolated Strings

An interpolated string starts with a lowercase `f` immediately followed by the opening double quote. A `{Expression}` field marks an interpolation. The braces must enclose a complete U expression. An empty `{}` is invalid.

Outside interpolation fields, string text follows the ordinary backtick escape rules. The sequences `{{` and `}}` represent a single opening and closing brace, respectively. An unpaired brace outside an interpolation field is a syntax error. In an ordinary string, braces are kept as written.

For example, `f"hello, {name}!"` uses an identifier as the interpolation expression. In `f"{{{1 + 2}}}"`, each doubled brace outside the interpolation field represents a literal brace.

### VII. Comments

A **comment**, abbreviated **com**, is explanatory text in source code. U has two forms of comments.

- Line comment — `// Comments...`
- Block comment — `/* Comments... */`

U uses the same comment delimiters as C++. In U, block comments can nest. For example, in `/* Comments /* Comments */ Comments */`, the inner `*/` closes only the inner comment. The block comment ends at the final `*/`.

## Syntax

### I. Expressions

An **expression**, abbreviated **Expr**, can appear in an initializer, as an argument, as a condition, or as the operand of `return`. An expression can contain other expressions.

#### 1. Atomic Expressions

An **atomic expression**, abbreviated **Expr.Atom**, can consist of a literal or an identifier.

- A **literal expression** consists of a literal such as the integer `42` or the string `"string"`.
- An **identifier expression**, abbreviated **Expr.Id**, consists of an identifier. In `age + 1`, `age` is the left operand of addition.

#### 2. Conditional Expressions

A **conditional expression**, abbreviated **Expr.Condit**, has the form `a ? b : c`. The condition `a` has type `bool`. Each of the two branches, `b` and `c`, can be an expression or a `return` statement.

```ul
x >= 0 ? x : -x
```

#### 3. Operator Expressions

An **operator expression**, abbreviated **Expr.Calc**, consists of an operator and its operands. An operand can itself be an expression. Parentheses can specify grouping explicitly.

##### Comparison Operators

A comparison expression joins two operands with `>`, `<`, `>=`, `<=`, `==`, or `!=`. One example is `a == 3`.

The relational operators `>`, `<`, `>=`, and `<=` share a precedence level higher than that of the equality operators `==` and `!=`. Equality operators share a precedence level and associate from left to right.

| Expression | Grouping |
| :--- | :--- |
| `a == b == flag` | `(a == b) == flag` |
| `a == b > c` | `a == (b > c)` |

##### Logical Operators

`and` and `or` are binary logical operators. `not` is a unary logical operator. Their operands and results have type `bool`. Both `not ready` and `not (a and b)` are valid when `ready`, `a`, and `b` are Boolean values.

Comparisons bind more tightly than `not`, which binds more tightly than `and`. `and` binds more tightly than `or`.

| Expression | Grouping |
| :--- | :--- |
| `not a == b and a == c` | `(not (a == b)) and (a == c)` |
| `a == 2 and b == 3 or a + b == 5` | `((a == 2) and (b == 3)) or ((a + b) == 5)` |
| `not a + b == c` | `not ((a + b) == c)` |

##### Arithmetic Operators

`*` and `/` share a precedence level higher than that of `+` and `-`, which also share a level. These arithmetic operators bind more tightly than comparison operators. Arithmetic operators at the same precedence level group from left to right. For example, `a + b * c` parses as `a + (b * c)`, and `a - b - c` parses as `(a - b) - c`.

##### Assignment

An assignment expression has the form `left_operand = right_operand`. The left operand must designate a writable location. For example, `test = a;` is an expression statement. An assignment expression cannot appear where a value is required, so `f(a = b)` and `a = b = c` are invalid.

> **Compiler rule:** If the left operand is a constant expression, the compiler should report `Constant expression is unexpected here.`

A structure instance also supports assignment from a brace-enclosed list in member declaration order. See [Positional Assignment](#positional-assignment).

#### 4. Call Expressions

A **call expression**, abbreviated **Expr.Call**, consists of a callee followed by an argument list. A call by identifier has the form `Id(...)`. The argument list is enclosed in parentheses and can be empty. Commas separate multiple arguments. For example, `get_current_date()` has no arguments, and `f(x, y)` has two.

In `a: int32 = get_current_date();`, the call expression is the initializer for `a`.

See [Anonymous Function Expressions](#anonymous-function-expressions) for the syntax of anonymous functions.

### II. Statements

A **statement**, abbreviated **Stmt**, can appear in a block such as a function body. Whether a statement ends with a semicolon depends on its form.

#### 1. Block Statements

A **block statement**, abbreviated **Stmt.Block**, encloses a group of statements in braces and introduces a scope. Blocks can nest. In a function body or control-flow body, a block can contain a sequence of statements.

#### 2. Expression Statements

An **expression statement**, abbreviated **Stmt.Expr**, consists of an expression followed by a semicolon.

For example, `putln("hello, world!")` is a call expression, and `putln("hello, world!");` is an expression statement.

An anonymous function expression can also stand alone as a statement with a trailing semicolon. See [Anonymous Function Expressions](#anonymous-function-expressions).

#### 3. Declaration Statements

A **declaration statement**, abbreviated **Stmt.Decl**, is a declaration within a block. Both `age: int32;` and `type_times: int32 = 0;` are declaration statements. See [Variables and Constants](#1-variables-and-constants) for the parts of a declaration.

#### 4. If-Else Statements

`if` is followed by a condition of type `bool` and then a block or a single statement. An optional `else` branch can also contain a block or a single statement. Using another `if` statement as the body of an `else` forms an `else if` branch.

```ul
if ask_for_age(age) break;
```

[→ See the example program](../examples/getstart.ul)

#### 5. For Statements

`for` supports an iteration form and a three-part form. In either form, the loop body can be a block or a single statement.

The **iteration form** is `for a in b`, where `a` is the iteration variable name and `b` is an array, slice, or string expression.

```ul
for item in items {
    use(item);
}
```

The **three-part form** is `for initializer; condition; update` followed by the loop body. Semicolons separate the three parts of the loop header.

```ul
for i: int32 = 0; i < 3; ++i {
    use(i);
}
```

#### 6. While Statements

`while` is followed by a condition of type `bool` and then a block or a single statement. For example, `while ready { work(); }` has a block as its loop body.

#### 7. Switch-Case Statements

`switch` is followed by the expression to match and a brace-enclosed list of `case` branches. A semicolon terminates the entire `switch` statement. Each `case` has a match value and a block. Commas separate branches, and the comma after the final branch is optional.

The matched expression must support `==` comparison. Ordinary branches must have distinct match values. `case none` denotes the default branch and can appear at most once.

```ul
switch text {
    case "yes" { accept(); },
    case "no" { reject(); },
    case none { retry(); },
};
```

#### 8. Jump Statements

- `break;` and `continue;` can appear in a loop body.
- `return expression;` includes a return value expression. A function with no return value can use `return;`.

#### 9. Error-Handling Statements

##### Reporting Errors

A report statement has the form `report expression;`. The expression specifies the error value.

```ul
fn test() {
    report "error";
}
```

##### Recovery Blocks

`failed` is followed by the call to monitor and a block called the **recovery block**.

```ul
failed test() {
}
```

To name the error value, write an identifier between `failed` and the call. Write a colon and the error value type after the call.

```ul
failed err test(): string {
    putln(err);
}
```

Here, `: string` is the type annotation for `err`.

An assignment expression that contains a call can also follow `failed`, as in `failed age = string_to_int(input) { ... }`.

[→ See the example program](../examples/getstart.ul)

### III. Declarations and Definitions

A declaration gives a name and its associated type or signature. A function definition also supplies a function body. See [Declaration Statements](#3-declaration-statements) for declarations within blocks.

#### 1. Variables and Constants

A variable declaration has the form `name: Type;`. A declaration with an initializer has the form `name: Type = initializer;`. The `=` introduces the initializer.

```ul
age: int32;
type_times: int32 = 0;
limit: int32! = 10;
```

The `!` type suffix in the third declaration marks `limit` as read-only.

Type suffixes, called **Extern Descriptions**, follow the type name. Suffixes can be combined and are interpreted from right to left.

| Type form | Meaning |
| :--- | :--- |
| `T!` | Read-only `T`. |
| `T[]` | Slice with elements of type `T`. |
| `T[n]` | Array of length `n` with elements of type `T`. |
| `T[]!` | Read-only array of fixed length, with the length omitted from the type form. Its elements are read-only. |
| `T[n]!` | Read-only array of length `n`. Its elements are read-only. |
| `T[]![]!` | Two-dimensional read-only array. Both dimensions have fixed lengths, and the elements are read-only. |

##### Pointers, References, and Read-Only Views

Pointer, writable reference, and read-only view markers precede the target type.

| Type form | Meaning | Example declaration |
| :--- | :--- | :--- |
| `->T` | Pointer to an object of type `T`. | `ptr: ->int32 = &3;` |
| `&T` | Writable reference to an object of type `T`. | `ref: &int32 = refer;` |
| `@T` | Read-only view of an object of type `T`. | `view: @int32 = value;` |

These markers can nest. Each marker applies to the complete type to its right. The leftmost marker forms the outermost type.

- `@->int32` is a read-only view of the `->int32` pointer itself.
- `->@int32` is a pointer to an `@int32` read-only view.
- `->&int32` is a pointer to an `&int32` reference.

#### 2. Functions

A named function starts with `fn`, followed by the function name and a parameter list in parentheses. A parameter has the form `name: Type`. Commas separate multiple parameters. The parentheses remain even when the list is empty. An optional `: ReturnType` follows the closing parenthesis.

A function definition uses a block as its body. A declaration without a body ends the signature with a semicolon.

```ul
fn answer(): int32;

fn answer(): int32 {
    return 42;
}
```

Writing `none` as the return type or omitting the return type indicates that the function has no return value. `fn f(): none { ... }` and `fn f() { ... }` are equivalent definition forms. `fn f(): none;` and `fn f();` are equivalent declaration forms.

##### Anonymous Function Expressions

An **anonymous function expression** has the form `fn(parameter_list) { ... }`. The parameter list follows `fn` directly. An anonymous function with no parameters starts with `fn()`. The body is enclosed in braces.

An anonymous function expression is typically used as the right operand of assignment. It can also appear after `=` as a declaration initializer, as in `subtotal: int32 = fn() { return 42; };`. The left side of the declaration has the form `name: Type`. A parameter list follows the function name only in named function declarations and definitions that start with `fn`. Thus, `subtotal(): int32 = fn() { return 42; };` is invalid.

An anonymous function expression cannot appear directly as a call argument. With a trailing semicolon, it forms an **anonymous function statement** of the form `fn(parameter_list) { ... };`.

An anonymous function must have a body. `test: int32 = fn();` is invalid because the body is missing.

An anonymous function expression can initialize a local declaration within a named or anonymous function, so anonymous functions can nest.

```ul
fn calculate(): int32 {
    subtotal: int32 = fn() {
        base_value: int32 = fn() {
            return 40;
        };
        return base_value() + 2;
    };
    return subtotal();
}
```

#### 3. Structures

A structure definition starts with `struct` followed by the structure name, a brace-enclosed list of member declarations, and a semicolon. Only member declarations can appear in the structure body. A data member can be written as `name: Type;` or `name: Type = initializer;`.

```ul
struct Position {
    row: int32;
    column: int32 = 4;
};
```

##### Methods

The recommended form defines methods outside the structure body. Write `in StructureName` after the parameter list, followed by the return type and the function body.

```ul
fn origin_index() in Position: int32 {
    return 0;
}
```

A structure can also declare a member initialized with an anonymous function expression. The member declaration has the form `name: Type = fn(parameter_list) { ... };`. The parameter list follows `fn` on the right side.

```ul
struct Counter {
    count: int32 = 0;
    initial_count: int32 = fn() {
        return 0;
    };
};
```

> **Compiler rule:** The compiler should emit a tip for this form of member declaration. For `initial_count` in `Counter`, the tip is `using fn initial_count() in Counter is recommended.`

##### Positional Assignment

Use `instance = {value, value, ...};` to assign to a structure instance by position. The comma-separated entries are written in member declaration order. `none` is a placeholder that skips the corresponding member.

```ul
position: Position;
position = {42, 42};
position = {none, 17};
```
