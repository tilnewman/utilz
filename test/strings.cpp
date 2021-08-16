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

TEST_CASE("startAndEndsWith", "[startAndEndsWith]")
{
    CHECK(startsWith("", "") == false);
    CHECK(startsWith("a", "") == false);
    CHECK(startsWith("", "a") == false);
    CHECK(startsWith("a", "b") == false);
    CHECK(startsWith("aaa", "b") == false);
    CHECK(startsWith("aaa", "aaaa") == false);

    CHECK(startsWith("a", "a"));
    CHECK(startsWith("aa", "aa"));
    CHECK(startsWith("aaa", "aaa"));
    CHECK(startsWith("andNowForTesting", "a"));
    CHECK(startsWith("andNowForTesting", "and"));
    CHECK(startsWith("andNowForTesting", "n") == false);

    CHECK(endsWith("", "") == false);
    CHECK(endsWith("a", "") == false);
    CHECK(endsWith("", "a") == false);
    CHECK(endsWith("a", "b") == false);
    CHECK(endsWith("aaa", "b") == false);
    CHECK(endsWith("aaa", "aaaa") == false);

    CHECK(endsWith("a", "a"));
    CHECK(endsWith("aa", "aa"));
    CHECK(endsWith("aaa", "aaa"));
    CHECK(endsWith("andNowForTesting", "a") == false);
    CHECK(endsWith("andNowForTesting", "and") == false);
    CHECK(endsWith("andNowForTesting", "n") == false);

    CHECK(endsWith("andNowForTesting", "g"));
    CHECK(endsWith("andNowForTesting", "Testing"));
}

TEST_CASE("replaceAll", "[replaceAll]")
{
    CHECK(replaceAllCopy("", "", "") == "");
    CHECK(replaceAllCopy("", "a", "") == "");
    CHECK(replaceAllCopy("", "", "b") == "");
    CHECK(replaceAllCopy("a", "a", "") == "");
    CHECK(replaceAllCopy("a", "", "b") == "a");
    CHECK(replaceAllCopy("aa", "a", "b") == "bb");
    CHECK(replaceAllCopy("aa", "aa", "b") == "b");
    CHECK(replaceAllCopy("This and that.", " ", "_") == "This_and_that.");
    CHECK(replaceAllCopy("ftp: ftpftp: ftp:", "ftp", "http") == "http: httphttp: http:");
}

TEST_CASE("removeAll", "[removeAll]")
{
    CHECK(removeAllCopy("", "") == "");
    CHECK(removeAllCopy("a", "") == "a");
    CHECK(removeAllCopy("", "a") == "");
    CHECK(removeAllCopy("a", "b") == "a");
    CHECK(removeAllCopy("aaa", "bbb") == "aaa");
    CHECK(removeAllCopy("a", "a") == "");
    CHECK(removeAllCopy("aaa", "a") == "");
    CHECK(removeAllCopy("ababab", "a") == "bbb");
    CHECK(removeAllCopy("ababab", "b") == "aaa");
}
