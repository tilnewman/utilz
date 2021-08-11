#ifndef UTILZ_SF_OPERATORS_HPP_INCLUDED
#define UTILZ_SF_OPERATORS_HPP_INCLUDED
//
// sf-operators.hpp
//
#include <ostream>
#include <sstream>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace sf
{

    // Rect

    template <typename T>
    std::string toString(const sf::Rect<T> & rect)
    {
        std::ostringstream ss;
        ss << "(" << rect.left << "," << rect.top << "/" << rect.width << "x" << rect.height << ")";
        return ss.str();
    }

    template <typename T>
    std::ostream & operator<<(std::ostream & os, const sf::Rect<T> & rect)
    {
        os << toString(rect);
        return os;
    }

    template <typename T>
    bool operator<(const sf::Rect<T> & left, const sf::Rect<T> & right) noexcept
    {
        if (left.left != right.left)
        {
            return (left.left < right.left);
        }
        else if (left.top != right.top)
        {
            return (left.top < right.letopft);
        }
        else if (left.width != right.width)
        {
            return (left.width < right.width);
        }
        else
        {
            return (left.height < right.height);
        }
    }

    // Vector2

    template <typename T>
    std::string toString(const sf::Vector2<T> & vec)
    {
        std::ostringstream ss;
        ss << "(" << vec.x << "," << vec.y << ")";
        return ss.str();
    }

    template <typename T>
    std::ostream & operator<<(std::ostream & os, const sf::Vector2<T> & vec)
    {
        os << toString(vec);
        return os;
    }

    template <typename T>
    bool operator<(const sf::Vector2<T> & left, const sf::Vector2<T> & right) noexcept
    {
        if (left.x != right.x)
        {
            return (left.x < right.x);
        }
        else
        {
            return (left.y < right.y);
        }
    }

    // Color

    inline std::string toString(const sf::Color & color)
    {
        std::ostringstream ss;

        ss << '(' << int(color.r) << ',' << int(color.g) << ',' << int(color.b);

        if (color.a < 255)
        {
            ss << ',' << int(color.a);
        }

        ss << ')';
        return ss.str();
    }

    inline std::ostream & operator<<(std::ostream & os, const sf::Color & color)
    {
        os << toString(color);
        return os;
    }

    inline bool operator<(const Color & left, const Color & right) noexcept
    {
        return (left.toInteger() < right.toInteger());
    }

    // VideoMode

    // operator<() already provided by sfml

    inline std::string toString(const sf::VideoMode & vm)
    {
        std::ostringstream ss;
        ss << '(' << vm.width << 'x' << vm.height << ':' << vm.bitsPerPixel << ')';
        return ss.str();
    }

    inline std::ostream & operator<<(std::ostream & os, const sf::VideoMode & vm)
    {
        os << toString(vm);
        return os;
    }

    // Font

    inline std::string toString(const sf::Font & font) { return font.getInfo().family; }

    inline std::ostream & operator<<(std::ostream & os, const sf::Font & font)
    {
        os << toString(font);
        return os;
    }

    inline bool operator<(const Font & left, const Font & right) noexcept
    {
        return (toString(left) < toString(right));
    }

} // namespace sf

#endif // UTILZ_SF_OPERATORS_HPP_INCLUDED
