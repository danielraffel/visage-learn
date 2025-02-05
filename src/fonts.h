/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#ifndef BACONPAUL_VISAGE_LEARN_FONTS_H
#define BACONPAUL_VISAGE_LEARN_FONTS_H

#include <cstddef>

namespace baconpaul::visage_learn
{
struct Fonts
{
    static void setup();

    // This implementation leaks on exit.
    static char *firaCode;
    static size_t firaCodeSize;

    static char *outfit;
    static size_t outfitSize;

    static char *pacifico;
    static size_t pacificoSize;
};

} // namespace baconpaul::visage_learn
#endif // FONTS_H
