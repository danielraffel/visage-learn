//
// Created by Paul Walker on 2/5/25.
//

#include "fonts.h"

#include "config.h"

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(resource_fonts);

namespace baconpaul::visage_learn
{
char *Fonts::firaCode{nullptr};
size_t Fonts::firaCodeSize{0};

char *Fonts::outfit{nullptr};
size_t Fonts::outfitSize{0};

char *Fonts::pacifico{nullptr};
size_t Fonts::pacificoSize{0};

void Fonts::setup()
{
    static bool isSetup{false};

    if (isSetup)
        return;

    try
    {
        auto fs = cmrc::resource_fonts::get_filesystem();
        auto f = fs.open("fonts/FiraCode-Regular.ttf");
        firaCodeSize = f.size();
        firaCode = new char[firaCodeSize];
        memcpy(firaCode, f.begin(), firaCodeSize);
        VLLOG("FiraCode-Regular set up with " << VLV(f.size()));

        f = fs.open("fonts/Outfit-Regular.ttf");
        outfitSize = f.size();
        outfit = new char[outfitSize];
        memcpy(outfit, f.begin(), outfitSize);
        VLLOG("Outfit-Regular set up with " << VLV(f.size()));

        f = fs.open("fonts/Pacifico-Regular.ttf");
        pacificoSize = f.size();
        pacifico = new char[pacificoSize];
        memcpy(pacifico, f.begin(), pacificoSize);
        VLLOG("Pacifico-Regular set up with " << VLV(f.size()));
    }
    catch (std::exception &e)
    {
        VLLOG(e.what());
    }

    isSetup = true;
}

} // namespace baconpaul::visage_learn