/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#include <clap/clap.h>
#include "visage-learn-entry-impl.h"

extern "C"
{

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wattributes"
#endif

    // clang-format off
    const CLAP_EXPORT struct clap_plugin_entry clap_entry = {
        CLAP_VERSION,
        baconpaul::visage_learn::clap_init,
        baconpaul::visage_learn::clap_deinit,
        baconpaul::visage_learn::get_factory
    };
    // clang-format on

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
}