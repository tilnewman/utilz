#include "catch.hpp"

#include "utilz/strings.hpp"

using namespace utilz;

TEST_CASE("upperAndLower", "[upperAndLower]")
{
    CHECK(isUpper('A'));
    CHECK(isUpper('a') == false);
    CHECK(isUpper('0') == false);
    CHECK(isUpper('\0') == false);
    CHECK(isUpper('\127') == false);
    CHECK(isUpper('\255') == false);

    CHECK(isLower('a'));
    CHECK(isLower('A') == false);
    CHECK(isLower('0') == false);
    CHECK(isLower('\0') == false);
    CHECK(isLower('\127') == false);
    CHECK(isLower('\255') == false);

    CHECK(toUpperCopy('a') == 'A');
    CHECK(toUpperCopy('A') == 'A');
    CHECK(toUpperCopy('0') == '0');

    CHECK(toLowerCopy('a') == 'a');
    CHECK(toLowerCopy('A') == 'a');
    CHECK(toLowerCopy('0') == '0');

    CHECK(toUpperCopy("123 abc ABC") == "123 ABC ABC");
    CHECK(toLowerCopy("123 abc ABC") == "123 abc abc");
}

TEST_CASE("isAndIsNot", "[isAndIsNot]")
{
    CHECK(isAlpha('z'));
    CHECK(isAlpha('Z'));
    CHECK(isAlpha('\0') == false);
    CHECK(isAlpha('\127') == false);
    CHECK(isAlpha('\255') == false);

    CHECK(isDigit('0'));
    CHECK(isDigit('1'));
    CHECK(isDigit('8'));
    CHECK(isDigit('9'));
    CHECK(isDigit('a') == false);
    CHECK(isDigit('A') == false);
    CHECK(isDigit('\0') == false);
    CHECK(isDigit('\127') == false);
    CHECK(isDigit('\255') == false);

    CHECK(isPrintable(' '));
    CHECK(isPrintable('\t') == false);
    CHECK(isPrintable('\r') == false);
    CHECK(isPrintable('\n') == false);
    CHECK(isPrintable('a'));
    CHECK(isPrintable('A'));
    CHECK(isPrintable('0'));
    CHECK(isPrintable('9'));
    CHECK(isPrintable('\0') == false);
    CHECK(isPrintable('\127') == false);
    CHECK(isPrintable('\255') == false);

    CHECK(isWhitespace(' '));
    CHECK(isWhitespace('\t'));
    CHECK(isWhitespace('\r'));
    CHECK(isWhitespace('\n'));
    CHECK(isWhitespace('a') == false);
    CHECK(isWhitespace('A') == false);
    CHECK(isWhitespace('0') == false);
    CHECK(isWhitespace('9') == false);
    CHECK(isWhitespace('\0') == false);
    CHECK(isWhitespace('\127') == false);
    CHECK(isWhitespace('\255') == false);

    CHECK(isTypical(' '));
    CHECK(isTypical('\t'));
    CHECK(isTypical('\r'));
    CHECK(isTypical('\n'));
    CHECK(isTypical('a'));
    CHECK(isTypical('A'));
    CHECK(isTypical('0'));
    CHECK(isTypical('9'));
    CHECK(isTypical('\126'));
    CHECK(isTypical('\0') == false);
    CHECK(isTypical('\127') == false);
    CHECK(isTypical('\255') == false);

    CHECK(isWhitespaceOrNonTypical(' '));
    CHECK(isWhitespaceOrNonTypical('\t'));
    CHECK(isWhitespaceOrNonTypical('\r'));
    CHECK(isWhitespaceOrNonTypical('\n'));
    CHECK(isWhitespaceOrNonTypical('a') == false);
    CHECK(isWhitespaceOrNonTypical('A') == false);
    CHECK(isWhitespaceOrNonTypical('0') == false);
    CHECK(isWhitespaceOrNonTypical('9') == false);
    CHECK(isWhitespaceOrNonTypical('\0'));
    CHECK(isWhitespaceOrNonTypical('\126') == false);
    CHECK(isWhitespaceOrNonTypical('\127'));
    CHECK(isWhitespaceOrNonTypical('\255'));
}

TEST_CASE("trim", "[trim]")
{
    CHECK(trimWhitespaceCopy("a a") == "a a");
    CHECK(trimWhitespaceCopy(" \r\n\t a a \r\t\n ") == "a a");

    CHECK(trimNonTypicalCopy("\fa a\f") == "a a");

    CHECK(trimWhitespaceAndNonTypicalCopy(" \f\r\n\t a a \r\t\n \f") == "a a");
}
