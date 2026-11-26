/*
 * File        lexer.cpp
 * Author      ZirconiumTian
 */

#include "ulang/lexer.hpp"
#include "uctype.hpp"
#include "ustring.hpp"

#include <stdexcept>
#include <string_view>

using namespace ulang::lexer;

bool Lexer::atEOF(size_t pos) const
{
	return pos >= source_content.size();
}

bool Lexer::atEOF() const
{
	return atEOF(current_pos);
}

char32_t Lexer::current(std::size_t pos) const
{
	if (!atEOF(pos)) {
		return source_content[pos];
	}
	return 0;
}

char32_t Lexer::current() const
{
	return current(current_pos);
}

char32_t Lexer::peek(std::size_t pos, int n) const
{
	if (!atEOF(pos + n)) {
		return source_content[pos + n];
	}
	return 0;
}

char32_t Lexer::peek(int n) const
{
	return peek(current_pos, n);
}

void Lexer::advance(std::size_t &pos, int n)
{
	if (n < 0) {
		throw std::runtime_error(
			"Lexer::advance(pos, n), n < 0: Not allowed."
		);
	}
	while (n-- > 0) {
		if (!current()) break;
		if (current() == U'\n') {
			current_row++;
			current_column = 1;
		} else {
			current_column++;
		}
		pos++;
	}
}

void Lexer::advance(int steps)
{
	return advance(current_pos, steps);
}

void Lexer::skipSpaces()
{
	while (!atEOF()) {

	}
}

void Lexer::readComment()
{

}

void Lexer::readIdentifier()
{

}

void Lexer::readPunctuation()
{

}

void Lexer::readNumber()
{

}

void Lexer::readString()
{

}

Lexer::Lexer()
{

}

Lexer& Lexer::ignoreComments(bool ignore)
{
	ignore_comments = ignore;
	return *this;
}

Lexer& Lexer::sourceContent(std::string_view source)
{
	setSourceContent(source);
	return *this;
}

void Lexer::setSourceContent(std::string_view source)
{
	source_content = decodeToUTF32(source);
	current_pos = 0;
	current_row = 1;
	current_column = 1;
}

void Lexer::setIgnoreComments(bool ignore)
{
	ignore_comments = ignore;
}

Token Lexer::nextToken()
{

}

const Token& Lexer::peekNextToken()
{

}

std::vector<Token> Lexer::getAllTokens()
{

}
