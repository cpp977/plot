#pragma once

#include "point.hpp"

namespace plot
{

struct Rect;

constexpr Rect operator+(Rect const& lhs, Point const& rhs);
constexpr Rect operator-(Rect const& lhs, Point const& rhs);
constexpr Rect operator*(Rect const& lhs, Coord const& rhs);
constexpr Rect operator*(Coord const& lhs, Rect const& rhs);
constexpr Rect operator/(Rect const& lhs, Coord const& rhs);
constexpr Rect operator/(Coord const& lhs, Rect const& rhs);

struct Rect
{
    constexpr Rect() = default;

    constexpr Rect(Point const& p1, Point const& p2)
        : p1(p1), p2(p2)
        {}

    constexpr Rect(Size const& size)
        : p1(), p2(size)
        {}

    constexpr Rect sorted() const {
        auto x = utils::minmax(p1.x, p2.x);
        auto y = utils::minmax(p1.y, p2.y);
        return {
            { x.first, y.first },
            { x.second, y.second }
        };
    }

    constexpr Point size() const {
        return { utils::abs(p2.x - p1.x), utils::abs(p2.y - p1.y) };
    }

    constexpr bool contains(Point p) const {
        return p.x >= p1.x && p.x < p2.x && p.y >= p1.y && p.y < p2.y;
    }

    Rect& operator+=(Point const& other) {
        return (*this) = (*this) + other;
    }

    Rect& operator-=(Point const& other) {
        return (*this) = (*this) - other;
    }

    Rect& operator*=(Coord n) {
        return (*this) = (*this) * n;
    }

    Rect& operator/=(Coord n) {
        return (*this) = (*this) / n;
    }

    constexpr bool operator==(Rect const& other) const {
        return p1 == other.p1 && p2 == other.p2;
    }

    constexpr bool operator!=(Rect const& other) const {
        return p1 != other.p1 || p2 != other.p2;
    }

    Point p1{}, p2{};
};

inline constexpr Rect operator+(Rect const& lhs, Point const& rhs) {
    return {
        lhs.p1 + rhs,
        lhs.p2 + rhs
    };
}

inline constexpr Rect operator-(Rect const& lhs, Point const& rhs) {
    return {
        lhs.p1 - rhs,
        lhs.p2 - rhs
    };
}

inline constexpr Rect operator*(Rect const& lhs, Coord const& rhs) {
    return {
        lhs.p1*rhs,
        lhs.p2*rhs
    };
}

inline constexpr Rect operator*(Coord const& lhs, Rect const& rhs) {
    return {
        lhs*rhs.p1,
        lhs*rhs.p2
    };
}

inline constexpr Rect operator/(Rect const& lhs, Coord const& rhs) {
    return {
        lhs.p1/rhs,
        lhs.p2/rhs
    };
}

inline constexpr Rect operator/(Coord const& lhs, Rect const& rhs) {
    return {
        lhs/rhs.p1,
        lhs/rhs.p2
    };
}

} /* namespace plot */