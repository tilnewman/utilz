#ifndef UTILZ_SF_PLOT_HPP_INCLUDED
#define UTILZ_SF_PLOT_HPP_INCLUDED
//
// sf-plot.hpp
//
#include "utilz/math.hpp"

#include <SFML/Graphics.hpp>

namespace utilz
{

    namespace plot
    {

        struct Colors
        {
            static inline const sf::Uint8 alt_diff{ 16 };
            static inline const sf::Color alt_color{ alt_diff, alt_diff, alt_diff };
            static inline const sf::Color default_foreground{ sf::Color(64, 64, 255) };
            static inline const sf::Color default_background{ sf::Color(36, 35, 36) };
            static inline const sf::Color default_offwhite{ sf::Color(222, 222, 222) };

            explicit Colors(
                const sf::Color & foreColor = default_foreground,
                const sf::Color & backColor = default_background)
                : background(backColor)
                , border(default_offwhite)
                , data(foreColor)
                , data_alt(makeAlternate(data))
                , data_highlight(makeLight(data))
                , title(makeVeryLight(foreColor))
                , axis_line(makeLight(foreColor) + alt_color)
                , axis_label(axis_line + alt_color)
                , axis_title(axis_label + alt_color)
            {}

            static sf::Color makeAlternate(const sf::Color color)
            {
                sf::Color alt(color);

                if (alt.r < (255 - alt_diff))
                {
                    alt.r += alt_diff;
                }
                else
                {
                    alt.r -= alt_diff;
                }

                if (alt.g < (255 - alt_diff))
                {
                    alt.g += alt_diff;
                }
                else
                {
                    alt.g -= alt_diff;
                }

                return alt;
            }

            static sf::Color makeLight(const sf::Color color) { return (color + color); }

            static sf::Color makeVeryLight(const sf::Color color)
            {
                return (color + color + color);
            }

            sf::Color background;
            sf::Color border;
            sf::Color data;
            sf::Color data_alt;
            sf::Color data_highlight;
            sf::Color title;
            sf::Color axis_line;
            sf::Color axis_label;
            sf::Color axis_title;
        };

        struct Layout
        {
            static inline const float default_border_ratio{ 0.01f };

            static inline const sf::Vector2u default_size{
                (sf::VideoMode::getDesktopMode().width / 4),
                (sf::VideoMode::getDesktopMode().height / 4)
            };

            explicit Layout(
                const sf::Vector2u & sizeParam = default_size,
                const float borderRatioParam = default_border_ratio)
                : size(sizeParam)
                , border_ratio(borderRatioParam)
            {}

            sf::Vector2u size;
            float border_ratio;
            bool show_stats{ true };
        };

        struct Labels
        {
            explicit Labels(
                std::string titleParam = "",
                std::string axisHorizParam = "",
                std::string axisVertParam = "",
                std::string unitsParam = "")
                : title(titleParam)
                , axis_horiz(axisHorizParam)
                , axis_vert(axisVertParam)
                , units(unitsParam)
            {}

            std::string title;
            std::string axis_horiz;
            std::string axis_vert;
            std::string units;
        };

        struct Settings
        {
            explicit Settings(
                const Colors & colorsParam = Colors(),
                const Layout & layoutParam = Layout(),
                const Labels & labelsParam = Labels())
                : colors(colorsParam)
                , layout(layoutParam)
                , labels(labelsParam)
            {}

            Colors colors;
            Layout layout;
            Labels labels;
        };

        // template <typename Container_t>
        // sf::Image plotToImage(const Container_t & numbers, const Settings & settings = {})
        //{
        //    static_assert(std::is_arithmetic_v<typename Container_t::value_type>);
        //    static_assert(!std::is_same_v<std::remove_cv<typename Container_t::value_type>,
        //    bool>);
        //
        //    return image;
        //}

    } // namespace plot

} // namespace utilz

#endif // UTILZ_SF_PLOT_HPP_INCLUDED
