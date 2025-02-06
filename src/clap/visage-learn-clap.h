/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#ifndef BACONPAUL_VISAGE_LEARN_CLAP_VISAGE_LEARN_CLAP_H
#define BACONPAUL_VISAGE_LEARN_CLAP_VISAGE_LEARN_CLAP_H

#include <clap/clap.h>

namespace baconpaul::visage_learn
{

const clap_plugin *makePlugin(const clap_host *, bool);
const clap_plugin_descriptor *getDescriptor();
} // namespace baconpaul::visage_learn
#endif // VISAGE_LEARN_CLAP_H
