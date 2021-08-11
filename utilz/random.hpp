#ifndef UTILZ_RANDOM_HPP_INCLUDED
#define UTILZ_RANDOM_HPP_INCLUDED
//
// random.hpp
//
// TODO
//  Change the primary fromTo() so that it repeats and fills by default
//  Handle (from<0) && ((from+max) < to)
//  keep commonly used distributions?
//
#include <cmath>
#include <iterator>
#include <limits>
#include <random>
#include <stdexcept>
#include <type_traits>

namespace utilz
{

    class Random
    {
    public:
        explicit Random(
            const std::random_device::result_type seed = 0,
            const unsigned long long warmUpSkipCount = 123456)
            : m_warmupSkipCount(warmUpSkipCount)
            , m_seed((0 == seed) ? std::random_device()() : seed)
            , m_engine()
        {
            std::seed_seq seedSequence { m_seed };
            m_engine.seed(seedSequence);
            m_engine.discard(m_warmupSkipCount);
        }

        std::random_device::result_type seed() const noexcept { return m_seed; }

        unsigned long long warmupSkipCount() const noexcept { return m_warmupSkipCount; }

        template <typename T>
        T fromTo(const T from, const T to) const
        {
            static_assert(std::is_arithmetic_v<T>);
            static_assert(!std::is_same_v<std::remove_cv<T>, bool>);

            // handle (from>to) which can crash std::uniform_distributions
            if (to < from)
            {
                return fromTo(to, from);
            }

            if (from == to)
            {
                return from;
            }

            // TODO handle (from<0) && ((from+max) < to)

            if constexpr (std::is_integral_v<T>)
            {
                // std::uniform_int_distribution does not support single-byte types (chars)
                if constexpr (1 == sizeof(T))
                {
                    return static_cast<T>(fromTo(static_cast<int>(from), static_cast<int>(to)));
                }
                else
                {
                    std::uniform_int_distribution<T> distribution(from, to);
                    return distribution(m_engine);
                }
            }
            else
            {
                // uniform_real_distribution is actually [min, max) so nextafter() is required
                std::uniform_real_distribution<T> distribution(
                    from, std::nextafter(to, std::numeric_limits<T>::max()));

                return distribution(m_engine);
            }
        }

        template <typename T>
        T zeroTo(const T to) const
        {
            return fromTo(T(0), to);
        }

        template <typename T>
        T zeroToOneLessThan(const T to) const
        {
            return zeroTo(to - T(1));
        }

        inline bool boolean() const { return (zeroTo(1) == 1); }

        template <typename T>
        T integer() const
        {
            static_assert(std::is_integral_v<T>);

            if constexpr (std::is_signed_v<T>)
            {
                if (boolean())
                {
                    return fromTo(std::numeric_limits<T>::lowest(), T(-1));
                }
                else
                {
                    return fromTo(T(0), std::numeric_limits<T>::max());
                }
            }
            else
            {
                return fromTo(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max());
            }
        }

        // returns [0, size-1]
        template <typename T>
        std::size_t index(const T & container) const
        {
            if (0 == container.size())
            {
                throw std::runtime_error("Random::index() but container.size()==0.");
            }

            return zeroToOneLessThan(container.size());
        }

        template <typename Iterator_t>
        auto & from(Iterator_t begin, const Iterator_t end) const
        {
            if (end == begin)
            {
                throw std::runtime_error("Random::from(begin, end) but begin==end.");
            }

            return fromIterAndSize(begin, std::distance(begin, end));
        }

        template <typename T>
        auto & from(T & container) const
        {
            if (0 == container.size())
            {
                throw std::runtime_error("Random::from(container) but container.size()==0.");
            }

            return fromIterAndSize(std::begin(container), container.size());
        }

        template <typename T>
        const T & from(const std::initializer_list<T> initList) const
        {
            return fromIterAndSize(std::begin(initList), initList.size());
        }

        template <typename Iterator_t>
        void shuffle(const Iterator_t begin, const Iterator_t end) const
        {
            std::shuffle(begin, end, m_engine);
        }

        template <typename T>
        void shuffle(T & container) const
        {
            shuffle(std::begin(container), std::end(container));
        }

    private:
        template <typename Iterator_t>
        auto & fromIterAndSize(Iterator_t iter, const std::size_t size) const
        {
            if (0 == size)
            {
                throw std::runtime_error("Random::fromIterAndSize(iter, size) but size==0.");
            }

            std::advance(iter, zeroToOneLessThan(size));
            return *iter;
        }

    private:
        // The first few numbers generated by mt19937 are easily predictable if the seed is bad, and
        // our seed is just an unsigned int -which is BAD.  So skip the first few numbers.  This is
        // called 'warm-up', and is a good standard practice when working with any PRNG.  Any warmup
        // count from roughly thousands to millions will work fine.
        unsigned long long m_warmupSkipCount;

        // this is kept so that the seed can be printed or logged for replay testing
        std::random_device::result_type m_seed;

        mutable std::mt19937 m_engine;
    };

    /*
    template <typename T, typename = std::enable_if_t<can_generate_type<T>::value>>
    const std::tuple<T, T> randomSelectSubInterval(const T MIN, const T MAX) const
    {
        // setup LOW interval [MIN, (MIN + NUMERIC_LIMIT_MAX)]
        const auto LOW_MIN { MIN };
        const auto LOW_MAX { static_cast<T>(MIN + std::numeric_limits<T>::max()) };
        const auto LOW_SPAN { static_cast<long double>(std::numeric_limits<T>::max()) };

        // setup HIGH interval [(MIN + NUMERIC_LIMIT_MAX + 1), MAX]
        const auto HIGH_MIN = [&]() {
            if constexpr (std::is_floating_point<T>::value)
            {
                return static_cast<T>(std::nextafter(LOW_MAX, MAX));
            }
            else
            {
                return static_cast<T>(LOW_MAX + T(1));
            }
        }();

        const auto HIGH_MAX { MAX };
        const auto HIGH_SPAN { std::abs(static_cast<long double>(HIGH_MAX - HIGH_MIN)) };

        // note that the LOW_SPAN is always >= HIGH_SPAN
        const auto HIGH_TO_LOW_SPAN_RATIO { std::max(
            std::numeric_limits<long double>::min(), (HIGH_SPAN / LOW_SPAN)) };

        // decide which interval to use, the chance starts at 50/50 % (0.5L) but is
        // then scaled to make choosing the smaller interval proportionally less likely
        const auto HIGH_INTERVAL_CHANCE_RATIO { (0.5L * HIGH_TO_LOW_SPAN_RATIO) };

        std::uniform_real_distribution<long double> tempDist(0.0L, 1.0L);
        const auto RAND_RATIO { tempDist(m_engine) };

        const auto WILL_USE_HIGH_INTERVAL { (
            (IsRealClose(RAND_RATIO, HIGH_INTERVAL_CHANCE_RATIO))
            || (RAND_RATIO < HIGH_INTERVAL_CHANCE_RATIO)) };

        if (WILL_USE_HIGH_INTERVAL)
        {
            return { HIGH_MIN, HIGH_MAX };
        }
        else
        {
            return { LOW_MIN, LOW_MAX };
        }
    }
    */

} // namespace utilz

#endif // UTILZ_RANDOM_HPP_INCLUDED
