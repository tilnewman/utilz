#ifndef UTILZ_MATH_HPP_INCLUDED
#define UTILZ_MATH_HPP_INCLUDED
//
// math.hpp
//
#include <cmath>
#include <iomanip>
#include <iterator>
#include <limits>
#include <sstream>
#include <type_traits>

namespace utilz
{

    namespace math
    {

        // abs

        template <typename T>
        [[nodiscard]] T constexpr abs(const T number) noexcept
        {
            static_assert(std::is_arithmetic_v<T>);

            if constexpr (std::is_unsigned_v<T>)
            {
                return number;
            }
            else
            {
                if (number < T(0))
                {
                    return -number;
                }
                else
                {
                    return number;
                }
            }
        }

        // min/max

        template <typename T>
        [[nodiscard]] constexpr T max(const T left, const T right) noexcept
        {
            static_assert(std::is_arithmetic_v<T>);

            if (left < right)
            {
                return right;
            }
            else
            {
                return left;
            }
        }

        template <typename T, typename... Ts>
        [[nodiscard]] constexpr T max(const T first, const Ts... allOthers) noexcept
        {
            return max(first, max(allOthers...));
        }

        template <typename T>
        [[nodiscard]] constexpr T min(const T left, const T right) noexcept
        {
            static_assert(std::is_arithmetic_v<T>);

            if (left < right)
            {
                return left;
            }
            else
            {
                return right;
            }
        }

        template <typename T, typename... Ts>
        [[nodiscard]] constexpr T min(const T first, const Ts... allOthers) noexcept
        {
            return min(first, min(allOthers...));
        }

        // isRealClose

        template <typename T>
        [[nodiscard]] constexpr bool isRealClose(const T left, const T right) noexcept
        {
            static_assert(std::is_arithmetic_v<T>);

            if constexpr (std::is_integral_v<T>)
            {
                return (left == right);
            }
            else
            {
                const T diffAbs { abs(right - left) };

                if (diffAbs < T(1))
                {
                    return !(diffAbs > (std::numeric_limits<T>::epsilon() * 100));
                }
                else
                {
                    return !(
                        diffAbs
                        > (max(abs(left), abs(right), T(1)) * std::numeric_limits<T>::epsilon()));
                }
            }
        }

        template <typename T>
        [[nodiscard]] constexpr bool isRealCloseOrLess(const T number, const T comparedTo) noexcept
        {
            return ((number < comparedTo) || isRealClose(number, comparedTo));
        }

        template <typename T>
        [[nodiscard]] constexpr bool
            isRealCloseOrGreater(const T number, const T comparedTo) noexcept
        {
            return ((number > comparedTo) || isRealClose(number, comparedTo));
        }

        // isRealZero

        template <typename T>
        [[nodiscard]] constexpr bool isRealZero(const T number)
        {
            return isRealClose(number, T(0));
        }

        template <typename T>
        [[nodiscard]] constexpr bool isRealZeroOrLess(const T number) noexcept
        {
            return ((number < T(0)) || isRealClose(number, T(0)));
        }

        template <typename T>
        [[nodiscard]] constexpr bool isRealZeroOrGreater(const T number) noexcept
        {
            return ((number > T(0)) || isRealClose(number, T(0)));
        }

        // isRealOne

        template <typename T>
        [[nodiscard]] constexpr bool isRealOne(const T number)
        {
            return isRealClose(number, T(1));
        }

        template <typename T>
        [[nodiscard]] constexpr bool isRealOneOrLess(const T number) noexcept
        {
            return ((number < T(1)) || isRealClose(number, T(1)));
        }

        template <typename T>
        [[nodiscard]] constexpr bool isRealOneOrGreater(const T number) noexcept
        {
            return ((number > T(1)) || isRealClose(number, T(1)));
        }

        // map

        template <typename T, typename U = T>
        [[nodiscard]] constexpr U map(
            const T number, const T inMin, const T inMax, const U outMin, const U outMax) noexcept
        {
            if (isRealClose(inMin, inMax))
            {
                return outMax;
            }

            return (
                outMin + static_cast<U>(((number - inMin) * (outMax - outMin)) / (inMax - inMin)));
        }

        // assumes ratio is [0,1]
        template <typename Ratio_t, typename Number_t>
        [[nodiscard]] constexpr Number_t
            mapRatioTo(const Ratio_t ratio, const Number_t outMin, const Number_t outMax) noexcept
        {
            static_assert(std::is_arithmetic_v<Number_t>);
            static_assert(std::is_floating_point_v<Ratio_t>);

            return (
                outMin
                + static_cast<Number_t>(
                    ratio * (static_cast<Ratio_t>(outMax) - static_cast<Ratio_t>(outMin))));
        }

        template <typename Number_t, typename Ratio_t = float>
        [[nodiscard]] constexpr Ratio_t
            mapToRatio(const Number_t number, const Number_t inMin, const Number_t inMax) noexcept
        {
            static_assert(std::is_floating_point_v<Ratio_t>);

            if (isRealClose(inMin, inMax))
            {
                return Ratio_t(1);
            }

            return static_cast<Ratio_t>((number - inMin) / (inMax - inMin));
        }

        // statistics

        template <typename T>
        struct Stats
        {
            std::string toString(const std::streamsize numberWidth = 5) const
            {
                std::ostringstream ss;
                ss.imbue(std::locale("")); // this is only to put commas in the big numbers

                ss << "x" << count;
                ss << " [" << std::setw(numberWidth) << std::right << min;
                ss << ", " << std::setw(numberWidth) << std::right << static_cast<T>(avg);
                ss << ", " << std::setw(numberWidth) << std::right << max;
                ss << "] sd" << std::setw(numberWidth) << std::left << sdv;

                return ss.str();
            }

            std::size_t count { 0 };
            T min { T(0) };
            T max { T(0) };
            T sum { T(0) };
            double avg { 0.0 };
            double sdv { 0.0 };
        };

        template <typename T>
        std::ostream & operator<<(std::ostream & os, const Stats<T> & stats)
        {
            os << stats.toString();
            return os;
        }

        template <typename Container_t>
        Stats<typename Container_t::value_type> makeStats(const Container_t & container)
        {
            using T = typename Container_t::value_type;

            Stats<T> stats;

            stats.count = container.size();

            stats.min = std::numeric_limits<T>::max();

            for (const T number : container)
            {
                stats.sum += number;

                if (number < stats.min)
                {
                    stats.min = number;
                }

                if (number > stats.max)
                {
                    stats.max = number;
                }
            }

            stats.avg = (static_cast<double>(stats.sum) / static_cast<double>(stats.count));

            if (stats.count < 2)
            {
                return stats;
            }

            double deviationSum { 0.0 };
            for (const T number : container)
            {
                const double diff { static_cast<double>(number) - stats.avg };
                deviationSum += (diff * diff);
            }

            stats.sdv = std::sqrt(deviationSum / static_cast<double>(stats.count));

            return stats;
        }

    } // namespace math

} // namespace utilz

#endif // UTILZ_MATH_HPP_INCLUDED
