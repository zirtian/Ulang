# About the U26 Syntax Specification

[→ 简体中文版](syntax-u26.zh.md)

The U26 Syntax Specification,

formally the **Lexical and Syntactic Specification for the Uranium Programming Language (U26)**, defines the lexical and syntactic structure of source code in Uranium (U) under the U26 standard. It also specifies how the compiler reports lexical and syntactic errors. The two parts, **Lexical Structure** and **Syntax**, describe the expected output of the lexer and parser, respectively.

## Contributors

Many people contributed to this specification. The following table records some of their contributions.

| Contributor | Contributions | Profile |
| :--- | :--- | :--- |
| ZirconiumTian | Writing, review, release, maintenance | [→ GitHub](https://github.com/zirtian) |
| GPT-6.2 Sol | Translation, proofreading, maintenance | [→ OpenAI](https://developers.openai.com/api/docs/models/gpt-6.2-sol?site_locale=en) |

## License

This specification, including the language editions (`syntax-u26.*.md`) available in the [Ulang repository](https://github.com/zirtian/Ulang), is licensed under [Creative Commons Attribution-NonCommercial 4.0 International](https://creativecommons.org/licenses/by-nc/4.0/).

<br>

# Lexical and Syntactic Specification for the Uranium Programming Language (U26)

ZirconiumTian, Wednesday, November 25, 2026

## Lexical Structure

This part defines the lexical elements of U and the kinds of tokens the lexer produces. Implementers can use these definitions to check the lexer output.

A token stream represents the source code as a flat sequence.

### I. Identifiers

An **identifier**, abbreviated `Id`, is a lexical element used to name entities such as variables, functions, and structure instances. The ASCII characters used in identifiers are uppercase and lowercase letters, decimal digits, and the underscore (`A–Za–z0–9_`). Consider the following examples.

- `variable_name`
- `Tokenizer`
- `decode_to_utf32`

All three are valid identifiers. An identifier cannot start with a digit.

- `1st_version`
- `3seconds_ago`

Both are invalid identifiers.

Identifiers are case-sensitive. `Function` and `function` are distinct identifiers.

Identifiers may also contain other fullwidth or halfwidth Unicode characters. Operating systems with different locale settings may use different default file encodings, so ASCII characters are recommended for identifiers.

> **Lexical Tip to Emit**<br>
> ```
> Tip: Using ASCII characters for identifiers is recommended.
> ```

### II. Keywords

A **keyword**, abbreviated `Kwd`, is a special lexical element formed from the same character set as an identifier. Each keyword has a specific role in its context.

| Keyword | Meaning |
| :--- | :--- |
| `and` | Logical AND operator. |
| `break` | Exits the current loop. |
| `case` | Introduces a branch of a `switch` statement. |
| `catch` | Introduces a recovery statement that listens for error reports. |
| `continue` | Ends the current iteration and proceeds to the next one. |
| `else` | Introduces an alternative branch of an `if` statement. |
| `false` | Boolean literal for false. |
| `fn` | Introduces a general function declaration or definition, a function type, or a portable function expression. |
| `for` | Introduces a `for` loop. |
| `if` | Introduces a conditional branch. |
| `in` | Introduces the expression to iterate over in `for`, the bounds in a range test, the owning structure in an out-of-line method declaration or definition, or the monitored expression in `catch`. |
| `none` | Represents the absence of a value. It can mark a function as returning no value or indicate that a `catch` statement discards the error value. |
| `not` | Logical negation operator. |
| `or` | Logical OR operator. |
| `report` | Issues an error report that a `catch` statement can handle. |
| `return` | Ends a function or method and can supply a return value. |
| `struct` | Introduces a structure declaration or definition. |
| `switch` | Introduces branching based on a matched value. |
| `true` | Boolean literal for true. |
| `using` | Imports a module at global scope. |
| `while` | Introduces a `while` loop. |

> **Lexer Guidance**<br>
> Classify a token that meets the identifier character rules as an identifier if its spelling appears in neither the keyword table nor the type name table.

### III. Type Names

A **type name**, abbreviated `Type`, is a lexical element that names a data type. Type names use the same character set as identifiers.

| Type name | Meaning |
| :--- | :--- |
| `bool` | Boolean value, either `true` or `false`. |
| `int8` | 8-bit signed integer. |
| `int16` | 16-bit signed integer. |
| `int32` | 32-bit signed integer. |
| `int64` | 64-bit signed integer. |
| `uint8` | 8-bit unsigned integer. |
| `uint16` | 16-bit unsigned integer. |
| `uint32` | 32-bit unsigned integer. |
| `uint64` | 64-bit unsigned integer. |
| `float32` | 32-bit floating-point number. |
| `float64` | 64-bit floating-point number. |
| `char` | Extension of `uint8` that stores an 8-bit character. Element type of `string`. |
| `rune` | Extension of `uint32` that stores a UTF-32 character. Element type of `string32`. |
| `string` | UTF-8 string. |
| `string32` | UTF-32 string. |

### IV. Operators

An **operator**, abbreviated `Op`, is a lexical element that specifies the operation in an operator expression. U classifies operators by the number of operands they take.

#### 1. Unary Operators

A **unary operator**, abbreviated `Op.Unary`, generally has the form `Op Expr`.

U26 defines the following unary operators.

| Operator | Meaning |
| :--- | :--- |
| `@` | Obtains a read-only view of the operand. |
| `&` | Obtains a writable reference to the operand. |
| `->` | Obtains a pointer to the object designated by the operand. |
| `++` | Increments an integer operand by one. |
| `--` | Decrements an integer operand by one. |
| `~` | Produces a new value by inverting every bit in the integer or floating-point operand's bit pattern. |
| `-` | Negates an integer or floating-point operand. |
| `not` | Logically negates a `bool` operand. |

#### 2. Binary Operators

A **binary operator**, abbreviated `Op.Binary`, generally has the form `Expr Op Expr`.

U26 defines the following binary operators.

| Operator | Meaning |
| :--- | :--- |
| `+` | Adds two numbers. |
| `-` | Subtracts the right operand from the left operand. |
| `*` | Multiplies two numbers. |
| `/` | Divides the left operand by the right operand. |
| `=` | Assigns the right operand's value to the location designated by the left operand. |
| `+=` | Adds the operands and stores the result in the left operand. |
| `-=` | Subtracts the right operand from the left and stores the result in the left operand. |
| `*=` | Multiplies the operands and stores the result in the left operand. |
| `/=` | Divides the left operand by the right and stores the result in the left operand. |
| `==` | Tests whether the operands are equal. |
| `!=` | Tests whether the operands differ. |
| `>` | Tests whether the left operand is greater than the right. |
| `<` | Tests whether the left operand is less than the right. |
| `>=` | Tests whether the left operand is greater than or equal to the right. |
| `<=` | Tests whether the left operand is less than or equal to the right. |
| `[]` | Accesses an array element using the integer index inside the brackets. |
| `.` | Accesses a structure member or method, or a built-in method provided by the value. |
| `and` | Produces `true` if both Boolean operands are `true`. |
| `or` | Produces `true` if at least one Boolean operand is `true`. |

All six comparison operators produce a `bool` result.

#### 3. Ternary Operators

A **ternary operator**, abbreviated `Op.Ternary`, generally has the form `Expr Op Expr Op Expr`.

U26 defines the following ternary operators.

| Operator | Meaning |
| :--- | :--- |
| `in` | In `a in b, c`, tests whether `a` lies within the numeric range with lower bound `b` and upper bound `c`. Either bound can be written as `none` to leave that side unbounded. With both bounds present, the test corresponds to `a >= b and a <= c`. |
| `? :` | Forms the conditional expression `a ? b : c`. When `a` is `true`, it selects `b`. When `a` is `false`, it selects `c`. |

### V. Delimiters

A **delimiter**, abbreviated `Deli`, is a lexical element that marks boundaries between or within statements and expressions.

| Delimiter | Use |
| :--- | :--- |
| `(` `)` | Group expressions and enclose call arguments or function parameters. |
| `[` `]` | Enclose an index used to access an element. |
| `{` `}` | Mark the scope boundaries of a block statement. |
| `,` | Separate parameters, arguments, or entries. |
| `:` | Separates a data declaration's identifier from its type and introduces a function return type. |
| `;` | Separates statements. |

### VI. Literals

A **literal**, abbreviated `Lit`, is a lexical element that directly represents a value known at compile time.

#### 1. Integer Literals

An **integer literal**, abbreviated `Lit.Int`, represents an integer value and can be used with a type whose name begins with `int` or `uint`. See [Type Names](#iii-type-names).

U supports integer literals in bases 2, 8, 10, and 16. Each base has a distinct lexical form.

| Base | Example | Lexical form |
| :--- | :--- | :--- |
| 2 | `0b01100111` | Prefix `0b` followed by binary digits (`0` or `1`). |
| 8 | `033` | Prefix `0` followed by octal digits (`0` through `7`). |
| 10 | `1024` | A nonzero decimal digit followed by decimal digits. |
| 16 | `0x7c00` | Prefix `0x` followed by hexadecimal digits (`0` through `9` or `a` through `f`). |

Letters in binary and hexadecimal literals are case-insensitive. Both `0B0010` and `0X84b2` are valid.

#### 2. Floating-Point Literals

A **floating-point literal**, abbreviated `Lit.Float`, represents a floating-point value and can be used with `float32` or `float64`.

Floating-point literals use decimal notation with an ASCII period as the decimal point. `3.141592` and `0.125` are valid examples.

The period cannot be the first or last character, so `.231` and `7632.` are invalid floating-point literals.

> **Lexer Guidance**<br>
> In `.231`, the lexer reads the period as a Period token followed by an integer literal, so the parser reports a syntax error. `7632.` is an incomplete floating-point literal.
>
> When a token starts with a digit, check the base prefix, the characters permitted for that base, and the decimal point to determine the kind of numeric literal.

#### 3. Character Literals

A **character literal**, abbreviated `Lit.Char`, represents a character value. It can be used with `char` or `rune`, or with their underlying types `uint8` and `uint32`.

Single quotes enclose character literals.

`'C'` `'a'` `','`

All three are examples of character literals.

##### 3.1. UTF-32 Prefix

Character literals with values from 0 through 255 fit in `char`. For values from 256 up to, but excluding, 2^32, the underlying type is `uint32` and the UTF-32 prefix is required. Write a lowercase `u` immediately before the opening single quote, as in the following example.

`u'中'`

Use `rune` for this example. Its character value is outside the range of `char`.

#### 4. String Literals

A **string literal**, abbreviated `Lit.Str`, represents a string value and can be used with `string` or `string32`.

Double quotes enclose ordinary string literals.

`"This is a string!"` `"Love you so much! (>_<)"`

Both are examples of string literals.

##### 4.1. String Prefixes

Like the [UTF-32 prefix](#31-utf-32-prefix) for characters, string prefixes specify properties of a literal. The following sections describe interpolation, raw strings, and UTF-32 strings.

##### 4.2. Interpolated Strings

The `f` prefix enables type-safe string interpolation. Enclose an expression that produces a value in braces. To include a literal brace, write `{{` or `}}`.

```ul
f"2 + 3 = {2 + 3}"
f"f(x) = {{a + b[a - (c + x)]}}^2, type: {type}"
```

If `type` holds the `string` value `"Function"`, the examples produce the following strings.

```ul
"2 + 3 = 5"
"f(x) = {a + b[a - (c + x)]}^2, type: Function"
```

> **Lexer Guidance**<br>
> For an interpolated string such as `f"2 + 3 = {2 + 3}"`, emit four tokens: `Lit.Str("2 + 3 = ")`, `Lit.Int(2)`, `Op(+)`, and `Lit.Int(3)`. Mark each token as part of an interpolated string so the parser can build the corresponding expression tree.

##### 4.3. Raw Strings

A raw string literal can span source lines and preserves escape sequences as written. Use the lowercase `r` prefix. Place parentheses inside the quotes, immediately next to them, to delimit the raw content.

```ul
r"(This is a
   raw string in the Uranium
   Programming Language!)"
```

The same string can be written on one source line.

```ul
"This is a`n   raw string in the Uranium`n   Programming Language!"
```

##### 4.4. UTF-32 Strings

A `string` can contain Unicode characters.

```ul
"アンノウン・マザーグース"
```

This example is a UTF-8 string with `char` elements. Use the `u` prefix for a UTF-32 string with `rune` elements, where each element stores one Unicode code point.

```ul
u"アンノウン・マザーグース"
```

##### 4.5. Combined Prefixes

These prefixes can be combined in any order. The following example combines the `u`, `r`, and `f` prefixes.

```ul
urf"(Project Information:
项目: {project.name}
作者: {project.author}"
许可证: {project.license})"
```

The result is a multiline interpolated string encoded in UTF-32.

> **Lexer Guidance**<br>
> When an unrecognized prefix appears before a quoted string, as in `a"String demo"`, emit two tokens, `Id(a)` and `Lit.Str("String demo")`. Treat a sequence of letters as a string prefix only if it consists entirely of `u`, `f`, and `r` and immediately precedes the opening double quote. For a character literal, the `u` prefix immediately precedes the opening single quote.
> ```ul
> urf "(Raw UTF-32 Format String)"
> ```
> The space between `urf` and the opening quote separates the input into `Id(urf)` and `Lit.Str("(Raw UTF-32 Format String)")`.

#### 5. Escape Sequences

In character literals and ordinary string literals, an ASCII backtick (U+0060) introduces an escape sequence. Raw string content preserves these characters as written.

| Escape sequence | Meaning |
| :--- | :--- |
| ``` `` ``` | ASCII backtick. |
| `` `' `` | ASCII single quote. |
| `` `" `` | ASCII double quote. |
| `` `n `` | Line feed (U+000A). |
| `` `r `` | Carriage return (U+000D). |
| `` `t `` | Horizontal tab (U+0009). |
| `` `0 `` | Null character (U+0000). |
| `` `033 `` | Escape character, ESC (U+001B). |
| `` `e `` | Escape character, ESC (U+001B). |

In literals that process escapes, escape a quote that matches the opening quote. A backslash can appear directly. The compiler should report an error for an escape sequence absent from the table.

### VII. Comments

A **comment**, abbreviated `Com`, annotates source code. The compiler normally treats comments as whitespace. A tool can preserve comments as tokens, for example when an IDE plugin reads temporary configuration from a comment. Comments do not affect program execution.

U supports line comments and block comments.

```ul
// This is a line comment.
/* This is a block comment. */
/*
 * Block comments can span multiple lines
 * and can /* nest */.
 */
```
The notation follows C++ conventions. U block comments can nest.

## Syntax

This part defines the syntactic constructs of U and the kinds of syntax tree nodes the parser produces. Implementers can use these definitions to check the parser output.

A syntax tree represents the hierarchical structure of the source code.

### I. Expressions

An **expression**, abbreviated `Expr`, represents a value or an operation. An expression can contain subexpressions, such as the arguments of a call or the operands of an operator.

#### 1. Literal Expressions

A **literal expression**, abbreviated `Expr.Lit`, consists of a [literal](#vi-literals). It directly represents a value written in the source code and known at compile time.

```ul
3.141592
1024
"test"
```

These are literal expressions.

#### 2. Identifier Expressions

An **identifier expression**, abbreviated `Expr.Id`, consists of an identifier that refers to the corresponding entity, such as a variable, constant, structure, or function.

```ul
function
VkInstance
```

These are identifier expressions.

#### 3. Atomic Expressions

An **atomic expression**, abbreviated `Expr.Atom`, is a basic form used to build more complex expressions. Literal expressions and identifier expressions are atomic expressions.

#### 4. Operator Expressions

An **operator expression**, abbreviated `Expr.Op`, consists of an operator and its operands. An operand can itself be an expression. The kind of operation determines whether it produces a value and what type that value has.

##### 4.1. Arithmetic

The four arithmetic operations are addition, subtraction, multiplication, and division. They use `+`, `-`, `*`, and `/`, respectively.

| Expression | Meaning |
| :--- | :--- |
| `a + b` | The sum of `a` and `b`. |
| `a - b` | The difference obtained by subtracting `b` from `a`. |
| `a * b` | The product of `a` and `b`. |
| `a / b` | The quotient obtained by dividing `a` by `b`. |

##### 4.2. Comparisons

A comparison tests equality or ordering between two operands and produces a `bool` value.

| Expression | Meaning |
| :--- | :--- |
| `a > b` | Tests whether `a` is greater than `b`. |
| `a < b` | Tests whether `a` is less than `b`. |
| `a >= b` | Tests whether `a` is greater than or equal to `b`. |
| `a <= b` | Tests whether `a` is less than or equal to `b`. |
| `a == b` | Tests whether `a` equals `b`. |
| `a != b` | Tests whether `a` differs from `b`. |

##### 4.3. Logical Operations

The logical operators `not`, `and`, and `or` take expressions of type `bool` as operands. The unary operator `not` takes one operand to its right. The binary operators `and` and `or` take one operand on each side.

| Expression | Meaning |
| :--- | :--- |
| `not a` | Negates the Boolean expression `a`. |
| `a > b and a > c` | Tests whether both comparisons are true. |
| `a > b or a > c` | Tests whether at least one comparison is true. |
| `not a > b and a > c` | Negates `a > b` and combines it with `a > c` using `and`. |
| `not (a > b and a > c)` | Negates the entire conjunction in parentheses. |

In `not a > b and a > c`, `not` takes the comparison `a > b` as its operand. The expression groups as `(not (a > b)) and (a > c)`.

##### 4.4. Subscripting

A subscript expression `a[b]` accesses an array element. The expression `a` is the array being indexed, and `b` is the index expression. The index must have a type whose name begins with `int` or `uint`.

##### 4.5. Assignment

Assignment operators appear between two operands. Simple assignment uses `=`. Compound assignment uses `+=`, `-=`, `*=`, or `/=`. Increment and decrement operators appear before their operand.

| Operation | Examples |
| :--- | :--- |
| Simple assignment | `a = b` |
| Compound assignment | `a += b`, `a -= b`, `a *= b`, `a /= b` |
| Increment and decrement | `++a`, `--a` |

#### 5. Call Expressions

A **call expression**, abbreviated `Expr.Call`, consists of a callee followed by an argument list. Parentheses enclose the argument list, which can be empty.

| Call expression | Meaning |
| :--- | :--- |
| `test("value")` | Calls `test` with the string literal `"value"` as an argument. |
| `next()` | Calls `next` with an empty argument list. |

#### 6. Portable Function Expressions

A **portable function expression**, abbreviated `Expr.PtFunc`, consists of `fn`, a parameter list, and a block statement as the function body. A return type annotation can follow the parameter list.

```ul
fn(arg: int32): int32 {
        return arg + 1;
}
```

This portable function expression produces a value of type `fn(int32): int32`.

### II. Statements

A **statement**, abbreviated `Stmt`, is a syntactic unit of a program.

#### 1. Block Statements

A **block statement**, abbreviated `Stmt.Block`, is a brace-enclosed sequence of statements. A block can contain other blocks.

#### 2. Expression Statements

An **expression statement**, abbreviated `Stmt.Expr`, consists of an expression followed by a semicolon. A standalone function call is one example.

| Example | Statement kind | Expression structure |
| :--- | :--- | :--- |
| `test("value");` | Call statement | Call expression with a string literal as its argument. |
| `++index;` | Assignment statement | Increment expression with an identifier as its operand. |
| `name = ask_name();` | Assignment statement | Assignment expression with a call expression as the right operand. |

#### 3. Declaration Statements

A **declaration statement**, abbreviated `Stmt.Decl`, introduces a name and specifies its type or signature. A data declaration can include an initializer after `=`, in which case it is a definition statement. See [Definition Statements](#4-definition-statements).

##### 3.1. Data Declarations

A **data declaration**, abbreviated `Stmt.Decl.Data`, generally has the form `Id: Type;`.

```ul
age: int32;
name: string;
```

These statements declare variables of type `int32` and `string`, respectively. Types support two kinds of qualifiers. The form qualifiers use `[]` and `!`, and the access qualifiers use `&`, `@`, and `->`.

| Type | Meaning |
| :--- | :--- |
| `Type` | A value of type `Type`. |
| `Type!` | A read-only value of type `Type`. |
| `Type[]` | A dynamic array with elements of type `Type`. |
| `Type[n]` | A fixed-length array with `n` elements of type `Type`. |
| `Type![]` | A dynamic array with read-only elements of type `Type`. |
| `Type[]!` | A read-only fixed-length array with elements of type `Type`. Its length is determined at compile time from the initializer. |
| `&Type` | A reference to a value of type `Type`. |
| `@Type` | A read-only view of a value of type `Type`. |
| `->Type` | A pointer to an instance of `Type`. |
| `->Type!` | A pointer to a read-only instance of `Type`. |
| `->Type[]` | A pointer to a dynamic array with elements of type `Type`. |
| `&Type!` | A reference to a read-only value of type `Type`. This has similar properties to a read-only view. |
| `Type[][]` | A two-dimensional array with elements of type `Type`. |

Parentheses group the type and its qualifiers to clarify the order in which the qualifiers apply.

| Type | Meaning |
| :--- | :--- |
| `(->Type)!` | A read-only pointer to an instance of `Type`. |
| `(->Type)[]` | A dynamic array of pointers to instances of `Type`. |
| `@->Type` | A read-only view of a pointer to `Type`. |
| `->&Type` | A pointer to a reference to `Type`. |
| `(fn(int32): int32)` | The type of a function that takes one `int32` parameter and returns an `int32` value. |

See [Portable Function Declarations](#33-portable-function-declarations) for function types.

> **Syntax Diagnostic**<br>
> For `->int32[]`, the compiler may emit the following warning and tip.
> ```
> Warning: `->int32[]` is parsed as a pointer to a dynamic array of `int32`.
> Tip: Write `->(int32[])` to make the grouping explicit, or `(->int32)[]` if you meant a dynamic array of pointers.
> ```

##### 3.2. Function Declarations

A **function declaration**, abbreviated `Stmt.Decl.Func`, has the form `fn Id(Args...): Type;` for a general function. A parameter can be written using its type alone. Omit `: Type` if the function returns no value.

```ul
fn ask_for_age(): int32;
fn print_about(): none;
```

These declarations introduce `ask_for_age`, which returns an `int32`, and `print_about`, which returns no value. The return type `none` can be omitted, as shown below.

```ul
fn print_about();
```

This declaration is equivalent to the preceding declaration of `print_about`.

Separate multiple parameters with commas and use empty parentheses for a function with no parameters. The following declaration lists only the types of its two parameters.

```ul
fn sum(int32, int32): int32;
```

##### 3.3. Portable Function Declarations

A **portable function declaration**, abbreviated `Stmt.Decl.PtFunc`, declares data of a function type, such as `portable: (fn(int32): int32);`. In a function type, the parameter list contains only types. The return type annotation can be omitted for a function with no return value.

```ul
portable: (fn(int32): int32);
notify: fn();
```

The type of `portable` takes one `int32` parameter and returns an `int32`. The type of `notify` takes no parameters and returns no value. It can also be written as `fn(): none`. A function type can also serve as the type of a parameter or return value of a general function.

##### 3.4. Structure Declarations

A **structure declaration**, abbreviated `Stmt.Decl.Struct`, introduces a structure name. A forward declaration has the form `struct Id;`. The structure definition supplies the member list.

```ul
struct Position;
```

##### 3.5. Structure Method Declarations

A **structure method declaration**, abbreviated `Stmt.Decl.Method`, appears outside the structure body and has the form `fn Id(Args...) in Structure: Type;`. A structure method belongs to the named structure and otherwise follows the syntax of a function declaration.

```ul
fn origin_index() in Position: int32;
```

#### 4. Definition Statements

A **definition statement**, abbreviated `Stmt.Def`, declares and defines an entity. It can define a variable, constant, structure, or function.

##### 4.1. Data Definitions

A **data definition**, abbreviated `Stmt.Def.Data`, generally has the form `Id: Type = Expr;`, where `Expr` is the initializer. Extend the form described in [Data Declarations](#31-data-declarations) by adding `=` and an initializer before the final semicolon.

```ul
age: int32 = 17;
name: string = "Lovely Puski";
```

These definitions declare two variables and supply their initial values.

When a string literal initializes data, the literal type must match the declared type. An ordinary string literal has type `string`, and a string literal with the `u` prefix has type `string32`.

```ul
message: string = "Hello";
message32: string32 = u"你好";
```

##### 4.2. Function Definitions

A **function definition**, abbreviated `Stmt.Def.Func`, has the form `fn Id(Args...): Type { ... }` for a general function. Each parameter has the form `Id: Type`, as in a data declaration.

```ul
fn find_char_in_string(target: char, from: string): bool {
    for element in from {
        if element == target {
            return true;
        }
    }
    return false;
}
```

For a function that returns no value, write `none` or omit the return type annotation. A function can also have a function type as its return type. See [Portable Function Definitions](#43-portable-function-definitions).

##### 4.3. Portable Function Definitions

A **portable function definition**, abbreviated `Stmt.Def.PtFunc`, uses a portable function expression as the initializer for data of a function type. A portable function expression can also be assigned after the declaration with `Id = Expr;`.

```ul
portable: (fn(int32): int32);
portable = fn(arg: int32): int32 {
    return arg + 1;
};

notify: fn() = fn() {};
```

A general function can take or return a portable function. To pass a stored function value, use the name of the data that holds it.

```ul
fn apply(value: int32, operation: (fn(int32): int32)): int32 {
    return operation(value);
}

fn select_operation(): (fn(int32): int32) {
    operation: (fn(int32): int32) = fn(arg: int32): int32 {
        return arg + 1;
    };
    return operation;
}

operation: (fn(int32): int32) = select_operation();
result: int32 = apply(32, operation);
```

In this example, `apply(32, operation(32))` is invalid because `operation(32)` has type `int32`. A portable function expression cannot appear directly as a call argument.

##### 4.4. Structure Definitions

A **structure definition**, abbreviated `Stmt.Def.Struct`, has the form `struct Id { ... };`. The braces enclose data members only. A data member can have a function type.

A data member can have an initializer. In the following example, `adjust` is a data member that holds a portable function value.

```ul
struct Position {
    row: int32;
    column: int32 = 4;
    adjust: (fn(int32): int32) = fn(arg: int32): int32 {
        return arg + 1;
    };
};
```

A structure instance also supports positional assignment. Write a comma-separated list of values in member declaration order inside braces. Use `none` to skip the corresponding member.

```ul
position: Position;
position = {42, 42, none};
position = {none, 17, none};
```

##### 4.5. Structure Method Definitions

A **structure method definition**, abbreviated `Stmt.Def.Method`, appears outside the structure body and has the form `fn Id(Args...) in Structure: Type { ... }`.

```ul
fn origin_index() in Position: int32 {
    return 0;
}
```

#### 5. Branching Statements

A **branching statement**, abbreviated `Stmt.Branch`, selects a branch based on a condition or match.

##### 5.1. If-Else Statements

After `if`, write a condition of type `bool` followed by a block or a single statement. An optional `else` branch can also contain a block or a single statement. An `if` statement as the body of `else` forms an `else if` branch.

```ul
if score >= 90 {
    excellent();
} else if score >= 60 {
    pass();
} else {
    retry();
}
```

Both branches can have a single statement as their body.

```ul
if ready start();
else retry();
```

##### 5.2. Switch-Case Statements

After `switch`, write the expression to match, followed by the `case` branches in braces. Each ordinary branch consists of a match value and a block. The value being matched must support `==`, and the ordinary branches must have distinct match values. Separate branches with commas. The final comma is optional.

The default branch is written `case none` and can appear at most once.

```ul
switch answer {
    case "yes" { accept(); },
    case "no" { reject(); },
    case none { retry(); },
}
```

##### 5.3. Ternary Branch Statements

The ternary form is `a ? b : c`. The condition `a` must have type `bool`. Each branch can be an expression or a `return`, `break`, or `continue` statement. Omit the jump statement's own semicolon when it appears in a branch. A single semicolon terminates the entire ternary branch statement.

```ul
ready ? start() : wait();
```

The following example uses `return` and `break` as branches.

```ul
fn choose(yes: bool): string {
    while true {
        yes ? return "s" : break;
    }
    return "";
}
```

The semicolon after `break` terminates the entire ternary branch statement. When a jump statement appears as a branch, the constraints in [Jump Statements](#7-jump-statements) still apply.

Both branches can also be atomic expressions.

```ul
age >= 18 ? "adult" : "teen"
```

#### 6. Loop Statements

A **loop statement**, abbreviated `Stmt.Loop`, repeats its body. The body can be a block or a single statement.

##### 6.1. For Statements

`for` supports an iteration form and a three-part form. The iteration form is `for Id in Expr`, where `Id` is the iteration variable and `Expr` has a fixed-length array, dynamic array, or string type.

```ul
for item in items {
    use(item);
}
```

A single-statement body can directly follow the expression being iterated over.

```ul
for item in items use(item);
```

The three-part form is `for Init; Condition; Update` followed by the loop body. Semicolons separate the three parts of the loop header.

```ul
for i: int32 = 0; i < 3; ++i {
    use(i);
}
```

The three-part form also accepts a single-statement body.

```ul
for i: int32 = 0; i < 3; ++i use(i);
```

##### 6.2. While Statements

After `while`, write a condition of type `bool` followed by the loop body.

```ul
while ready {
    do();
}
```

The loop body can also be a single statement.

```ul
while ready do();
```

#### 7. Jump Statements

A **jump statement**, abbreviated `Stmt.Jump`, exits a loop, advances to the next iteration, or returns to the caller.

##### 7.1. Break Statements

A **break statement**, abbreviated `Stmt.Jump.Brk`, has the form `break;`. It appears in a block within the body of a `while` or `for` loop and exits that loop.

```ul
while true {
        data.append(read_from_user());
        if data.count > max_capacity {
                putln("At max capacity!!!");
                break;
        }
}
```

##### 7.2. Continue Statements

A **continue statement**, abbreviated `Stmt.Jump.Cont`, has the form `continue;`. It can appear in a loop body and ends the current iteration.

```ul
for item in items {
    if item == stop_value {
        break;
    }
    if item == skip_value {
        continue;
    }
    use(item);
}
```

##### 7.3. Return Statements

A **return statement**, abbreviated `Stmt.Jump.Ret`, has the form `return Expr;` in a function or method that returns a value. A function or method with no return value can use `return;`.

```ul
fn print_when_ready(ready: bool) {
    if not ready {
        return;
    }
    print_about();
}
```

#### 8. Error Handling Statements

An **error handling statement**, abbreviated `Stmt.Error`, can be a `report` statement that issues an error report or a `catch` recovery statement that handles one.

##### 8.1. Report Statements

A report statement has the form `report Expr;`. The value of `Expr` is the reported error value. Its type is used for matching by a typed `catch` recovery statement. The function `read` below reports a `string` error value.

```ul
fn read() {
    report "Unable to read input.";
}
```

##### 8.2. Catch Recovery Statements

A `catch` statement consists of an error binding specification, a monitored expression (ListenExpr), and a block statement that provides the recovery measures. The monitored expression can be a call expression (`Expr.Call`) or an operator expression (`Expr.Op`) containing a call expression.

```
catch Id: Type in ListenExpr Stmt.Block
catch none in ListenExpr Stmt.Block
```

Both forms use `in` to introduce the monitored expression. The first form specifies the name and type of the error binding as `Id: Type`. The error value's type must match `Type`. The name `Id` is visible only within the recovery block.

```ul
catch err: string in read() {
    putln(err);
}
```

The second form uses `none` to match error reports of any type and omit the error value binding.

```ul
catch none in read() {
    retry();
}
```

A monitored expression can also be an assignment expression containing a nested call.

```ul
catch err: string in age = parse(read_input()) {
    putln(err);
}
```