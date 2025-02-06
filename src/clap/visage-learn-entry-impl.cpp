/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#include "visage-learn-entry-impl.h"
#include <clap/clap.h>
#include <cstring>
#include "visage-learn-clap.h"

namespace baconpaul::visage_learn
{
uint32_t clap_get_plugin_count(const clap_plugin_factory *) { return 1; };
const clap_plugin_descriptor *clap_get_plugin_descriptor(const clap_plugin_factory *f, uint32_t w)
{
    if (w == 0)
    {
        return getDescriptor();
    }

    return nullptr;
}

const clap_plugin *clap_create_plugin(const clap_plugin_factory *f, const clap_host *host,
                                      const char *plugin_id)
{

    if (strcmp(plugin_id, getDescriptor()->id) == 0)
    {
        return makePlugin(host, false);
    }

    return nullptr;
}

const void *get_factory(const char *factory_id)
{
    if (strcmp(factory_id, CLAP_PLUGIN_FACTORY_ID) == 0)
    {
        static const struct clap_plugin_factory six_sines_clap_factory = {
            clap_get_plugin_count,
            clap_get_plugin_descriptor,
            clap_create_plugin,
        };
        return &six_sines_clap_factory;
    }

    return nullptr;
}
bool clap_init(const char *p) { return true; }
void clap_deinit() {}
} // namespace baconpaul::visage_learn