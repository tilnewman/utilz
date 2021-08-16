#ifndef UTILZ_STRINGS_HPP_INCLUDED
#define UTILZ_STRINGS_HPP_INCLUDED
//
// strings.hpp
//
#include <algorithm>
#include <string>

namespace utilz
{

    constexpr bool isUpper(const char CH) noexcept
    {
        return ((CH >= 'A') && (CH <= 'Z') && (CH != '\127'));
    }

    constexpr bool isLower(const char CH) noexcept
    {
        return ((CH >= 'a') && (CH <= 'z') && (CH != '\127'));
    }

    void toUpper(char & ch) noexcept
    {
        if (isLower(ch))
        {
            ch -= 32;
        }
    }

    [[nodiscard]] char toUpperCopy(const char CH) noexcept
    {
        auto copy{ CH };
        toUpper(copy);
        return copy;
    }

    void toUpper(std::string & str)
    {
        for (char & ch : str)
        {
            toUpper(ch);
        }
    }

    [[nodiscard]] const std::string toUpperCopy(const std::string & STR)
    {
        auto copy{ STR };
        toUpper(copy);
        return copy;
    }

    void toLower(char & ch) noexcept
    {
        if (isUpper(ch))
        {
            ch += 32;
        }
    }

    [[nodiscard]] char toLowerCopy(const char CH) noexcept
    {
        auto copy{ CH };
        toLower(copy);
        return copy;
    }

    void toLower(std::string & str)
    {
        for (char & ch : str)
        {
            toLower(ch);
        }
    }

    [[nodiscard]] const std::string toLowerCopy(const std::string & STR)
    {
        auto copy{ STR };
        toLower(copy);
        return copy;
    }

    constexpr bool isAlpha(const char CH) noexcept { return (isUpper(CH) || isLower(CH)); }

    constexpr bool isDigit(const char CH) noexcept { return ((CH >= '0') && (CH <= '9')); }

    // technically ascii printable set excluding delete
    constexpr bool isPrintable(const char CH) noexcept
    {
        return ((CH >= 32) && (CH <= 126) && (CH != '\127'));
    }

    constexpr bool isWhitespace(const char CH) noexcept
    {
        return ((CH == ' ') || (CH == '\t') || (CH == '\r') || (CH == '\n'));
    }

    // includes typical whitespace and the printable ascii set excluding delete
    constexpr bool isTypical(const char CH) noexcept
    {
        return (isWhitespace(CH) || isPrintable(CH));
    }

    constexpr bool isWhitespaceOrNonTypical(const char CH) noexcept
    {
        return (isWhitespace(CH) || !isTypical(CH));
    }

    // trims any char(s) for which the lambda returns false
    template <typename Lambda_t>
    void trimIfNot(std::string & str, Lambda_t lambda)
    {
        str.erase(std::begin(str), std::find_if(std::begin(str), std::end(str), lambda));
        str.erase(std::find_if(std::rbegin(str), std::rend(str), lambda).base(), std::end(str));
    }

    void trimWhitespace(std::string & str)
    {
        trimIfNot(str, [](const char CH) { return !isWhitespace(CH); });
    }

    [[nodiscard]] const std::string trimWhitespaceCopy(const std::string & STR_ORIG)
    {
        std::string newStr{ STR_ORIG };
        trimWhitespace(newStr);
        return newStr;
    }

    void trimNonTypical(std::string & str)
    {
        trimIfNot(str, [](const char CH) { return isTypical(CH); });
    }

    [[nodiscard]] const std::string trimNonTypicalCopy(const std::string & STR_ORIG)
    {
        std::string newStr{ STR_ORIG };
        trimNonTypical(newStr);
        return newStr;
    }

    void trimWhitespaceAndNonTypical(std::string & str)
    {
        trimIfNot(str, [](const char CH) { return !isWhitespaceOrNonTypical(CH); });
    }

    [[nodiscard]] const std::string trimWhitespaceAndNonTypicalCopy(const std::string & STR_ORIG)
    {
        std::string newStr{ STR_ORIG };
        trimWhitespaceAndNonTypical(newStr);
        return newStr;
    }

} // namespace utilz

#endif // UTILZ_STRINGS_HPP_INCLUDED
