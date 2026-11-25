/*
 * File        lexer.hpp
 * Author      ZirconiumTian
 * About       Declarations for the U language lexer.
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace ulang {
namespace lexer {

/*
 * Enumeration TokenTypes
 * Description Lexical element types defined by the U26 specification.
 */
enum class TokenTypes : std::uint8_t {
	Identifier,
	Comment,

	KeywordAnd,              // and
	KeywordBreak,            // break
	KeywordCase,             // case
	KeywordCatch,            // catch
	KeywordContinue,         // continue
	KeywordElse,             // else
	KeywordFalse,            // false
	KeywordFn,               // fn
	KeywordFor,              // for
	KeywordIf,               // if
	KeywordIn,               // in
	KeywordOr,               // or
	KeywordNone,             // none
	KeywordNot,              // not
	KeywordReport,           // report
	KeywordReturn,           // return
	KeywordStruct,           // struct
	KeywordSwitch,           // switch
	KeywordTrue,             // true
	KeywordUsing,            // using
	KeywordWhile,            // while

	TypenameInt8,            // int8
	TypenameInt16,           // int16
	TypenameInt32,           // int32
	TypenameInt64,           // int64
	TypenameUInt8,           // uint8
	TypenameUInt16,          // uint16
	TypenameUInt32,          // uint32
	TypenameUInt64,          // uint64
	TypenameChar,            // char
	TypenameRune,            // rune
	TypenameString,          // string
	TypenameString32,        // string32
	TypenameFloat32,         // float32
	TypenameFloat64,         // float64
	TypenameBool,            // bool

	OperatorAmpersand,       // &
	OperatorAtSign,          // @
	OperatorArrowRight,      // ->
	OperatorTilde,           // ~
	OperatorPlusPlus,        // ++
	OperatorMinusMinus,      // --
	OperatorPlus,            // +
	OperatorMinus,           // -
	OperatorAsterisk,        // *
	OperatorSlash,           // /
	OperatorPeriod,          // .
	OperatorEqual,           // =
	OperatorGreater,         // >
	OperatorLess,            // <
	OperatorEqualEqual,      // ==
	OperatorBangEqual,       // !=
	OperatorGreaterEqual,    // >=
	OperatorLessEqual,       // <=
	OperatorQuestionMark,    // ?
	OperatorBang,            // !
	OperatorPlusEqual,       // +=
	OperatorMinusEqual,      // -=
	OperatorAsteriskEqual,   // *=
	OperatorSlashEqual,      // /=

	DelimiterSemicolon,      // ;
	DelimiterLeftParen,      // (
	DelimiterRightParen,     // )
	DelimiterLeftBracket,    // [
	DelimiterRightBracket,   // ]
	DelimiterLeftBrace,      // {
	DelimiterRightBrace,     // }
	DelimiterComma,          // ,
	DelimiterColon,          // :

	LiteralInteger,
	LiteralFloat,
	LiteralCharacter,
	LiteralString,
	LiteralString32,

	TokenError,
	TokenEOF,
};

/*
 * Namespace   TokenFlags
 * Description Flags that describe a token.
 */
namespace TokenFlags {
constexpr std::uint8_t
 None           = 0,      // No special flags. (^~^)
 InFormatString = 1 << 0, // The token is part of an interpolated string.
 EndsThisLine   = 1 << 1, // The token is at the end of its line.
 StartsThisLine = 1 << 2, // The token is at the start of its line.
 UnflagToken    = 1 << 3; // The token needs further analysis.

} // namespace TokenFlags

// Three unordered maps from UTF-32 strings to TokenTypes.
// Each key is the source spelling of a specific token type.
inline const std::unordered_map<std::u32string, TokenTypes>

keywords_typenames_map {
	// Keywords
	{U"and",      TokenTypes::KeywordAnd},
	{U"break",    TokenTypes::KeywordBreak},
	{U"case",     TokenTypes::KeywordCase},
	{U"catch",    TokenTypes::KeywordCatch},
	{U"continue", TokenTypes::KeywordContinue},
	{U"else",     TokenTypes::KeywordElse},
	{U"false",    TokenTypes::KeywordFalse},
	{U"fn",       TokenTypes::KeywordFn},
	{U"for",      TokenTypes::KeywordFor},
	{U"if",       TokenTypes::KeywordIf},
	{U"in",       TokenTypes::KeywordIn},
	{U"or",       TokenTypes::KeywordOr},
	{U"none",     TokenTypes::KeywordNone},
	{U"not",      TokenTypes::KeywordNot},
	{U"report",   TokenTypes::KeywordReport},
	{U"return",   TokenTypes::KeywordReturn},
	{U"struct",   TokenTypes::KeywordStruct},
	{U"switch",   TokenTypes::KeywordSwitch},
	{U"true",     TokenTypes::KeywordTrue},
	{U"using",    TokenTypes::KeywordUsing},
	{U"while",    TokenTypes::KeywordWhile},

	// Typenames
	{U"int8",     TokenTypes::TypenameInt8},
	{U"int16",    TokenTypes::TypenameInt16},
	{U"int32",    TokenTypes::TypenameInt32},
	{U"int64",    TokenTypes::TypenameInt64},
	{U"uint8",    TokenTypes::TypenameUInt8},
	{U"uint16",   TokenTypes::TypenameUInt16},
	{U"uint32",   TokenTypes::TypenameUInt32},
	{U"uint64",   TokenTypes::TypenameUInt64},
	{U"char",     TokenTypes::TypenameChar},
	{U"rune",     TokenTypes::TypenameRune},
	{U"string",   TokenTypes::TypenameString},
	{U"string32", TokenTypes::TypenameString32},
	{U"float32",  TokenTypes::TypenameFloat32},
	{U"float64",  TokenTypes::TypenameFloat64},
	{U"bool",     TokenTypes::TypenameBool},
},

punctuations_map {
	// Single Operators
	{U"&", TokenTypes::OperatorAmpersand},
	{U"@", TokenTypes::OperatorAtSign},
	{U"~", TokenTypes::OperatorTilde},
	{U"+", TokenTypes::OperatorPlus},
	{U"-", TokenTypes::OperatorMinus},
	{U"*", TokenTypes::OperatorAsterisk},
	{U"/", TokenTypes::OperatorSlash},
	{U".", TokenTypes::OperatorPeriod},
	{U"=", TokenTypes::OperatorEqual},
	{U">", TokenTypes::OperatorGreater},
	{U"<", TokenTypes::OperatorLess},
	{U"?", TokenTypes::OperatorQuestionMark},
	{U"!", TokenTypes::OperatorBang},

	// Delimiters
	{U";", TokenTypes::DelimiterSemicolon},
	{U"(", TokenTypes::DelimiterLeftParen},
	{U")", TokenTypes::DelimiterRightParen},
	{U"[", TokenTypes::DelimiterLeftBracket},
	{U"]", TokenTypes::DelimiterRightBracket},
	{U"{", TokenTypes::DelimiterLeftBrace},
	{U"}", TokenTypes::DelimiterRightBrace},
	{U",", TokenTypes::DelimiterComma},
	{U":", TokenTypes::DelimiterColon},
},

double_puncts_map {
	{U"->", TokenTypes::OperatorArrowRight},
	{U"++", TokenTypes::OperatorPlusPlus},
	{U"--", TokenTypes::OperatorMinusMinus},
	{U"==", TokenTypes::OperatorEqualEqual},
	{U"!=", TokenTypes::OperatorBangEqual},
	{U">=", TokenTypes::OperatorGreaterEqual},
	{U"<=", TokenTypes::OperatorLessEqual},
	{U"+=", TokenTypes::OperatorPlusEqual},
	{U"-=", TokenTypes::OperatorMinusEqual},
	{U"*=", TokenTypes::OperatorAsteriskEqual},
	{U"/=", TokenTypes::OperatorSlashEqual},
};

/*
 * Structure   Token
 * Description A token's source offset, length in characters, line and
 *             column numbers, flags, and type.
 */
struct Token {
	std::size_t   pos;
	std::size_t   length;
	std::uint32_t row;
	std::uint16_t column;
	std::uint8_t  flags;
	TokenTypes    type;

	// Checks whether this token has the specified type.
	bool operator==(TokenTypes type_cmp) const {
		return type == type_cmp;
	}
};

/*
 * Class       Lexer
 * Description A lexer processes one input file at a time. It supports
 *             Unicode characters and can skip comments. It does not
 *             store the file name.
 */
class Lexer {
private:
	std::u32string_view source_content;
	std::size_t source_length = 0;
	std::size_t current_pos = 0;
	std::uint32_t current_row = 1;
	std::uint16_t current_column = 1;
	bool ignore_comments = false; // Skip comments when true. Otherwise, emit comment tokens.
	Token token_register; // Temporarily holds a token for internal use.

	// Returns the char32_t at the specified position in the source.
	// current() calls current(current_pos).
	char32_t current(std::size_t) const;
	char32_t current() const;

	// Returns the char32_t at an offset from the given position.
	// peek(n) calls peek(current_pos, n).
	char32_t peek(std::size_t, int = 1) const;
	char32_t peek(int = 1) const;

	// Moves the given cursor forward, or backward for a negative step count.
	// advance(steps) calls advance(current_pos, steps).
	void advance(std::size_t&, int = 1);
	void advance(int = 1);

	void skipSpaces(); // Skips whitespace and leaves comments for readComment().
	void readComment();
	void readIdentifier(); // Reads a keyword, type name, or ordinary identifier.
	void readPunctuation(); // Reads an operator or delimiter.
	void readNumber(); // Reads binary, octal, decimal, or hexadecimal integers and decimal floats.
	void readString();

public:
	Lexer();
	Lexer& ignoreComments(bool);
	Lexer& sourceContent(std::string_view);
	void setSourceContent(std::string_view);
	void setIgnoreComments(bool);
	Token nextToken();
	const Token& peekNextToken(); // Returns a read-only Token without advancing the cursor.
	std::vector<Token> getAllTokens();
};

} // namespace lexer
} // namespace ulang
