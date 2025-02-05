/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#ifndef BACONPAUL_VISAGE_LEARN_PIXEL_MATH_H
#define BACONPAUL_VISAGE_LEARN_PIXEL_MATH_H

#include <cmath>

namespace baconpaul::visage_learn
{

template <typename T> struct PixelMixin
{
    T *asT() { return reinterpret_cast<T *>(this); }
    const T *asT() const { return reinterpret_cast<const T *>(this); }

    int l2d(int x) const { return (int)std::round(x * asT()->dpiScale()); }
    int d2l(int x) const { return (int)std::round(x / asT()->dpiScale()); }
};

} // namespace baconpaul::visage_learn

#endif // PIXEL_MATH_H
