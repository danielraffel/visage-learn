//
// Created by Paul Walker on 2/5/25.
//

#ifndef FONTS_H
#define FONTS_H

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
