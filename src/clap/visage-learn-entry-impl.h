/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#ifndef BACONPAUL_VISAGE_LEARN_CLAP_VISAGE_LEARN_ENTRY_IMPL_H
#define BACONPAUL_VISAGE_LEARN_CLAP_VISAGE_LEARN_ENTRY_IMPL_H

namespace baconpaul::visage_learn
{
const void *get_factory(const char *factory_id);
bool clap_init(const char *p);
void clap_deinit();
} // namespace baconpaul::visage_learn
#endif // VISAGE_LEARN_ENTRY_IMPL_H
