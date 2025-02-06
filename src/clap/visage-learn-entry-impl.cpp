/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#include "visage-learn-entry-impl.h"
#include <clap/clap.h>
#include <cstring>
#include "visage-learn-clap.h"
#include "clapwrapper/auv2.h"
#include "clapwrapper/vst3.h"

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

/*
 * Clap Wrapper AUV2 Factory API
 */

static bool clap_get_auv2_info(const clap_plugin_factory_as_auv2 *factory, uint32_t index,
                               clap_plugin_info_as_auv2_t *info)
{
    if (index > 0)
        return false;

    if (index == 0)
    {
        strncpy(info->au_type, "aumu", 5); // use the features to determine the type
        strncpy(info->au_subt, "vsLn", 5);
    }

    return true;
}

static const clap_plugin_info_as_vst3 *clap_get_vst3_info(const clap_plugin_factory_as_vst3 *f,
                                                          uint32_t index)
{
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

    if (strcmp(factory_id, CLAP_PLUGIN_FACTORY_INFO_AUV2) == 0)
    {
        static const struct clap_plugin_factory_as_auv2 six_sines_auv2_factory = {
            "BcPL",      // manu
            "BaconPaul", // manu name
            clap_get_auv2_info};
        return &six_sines_auv2_factory;
    }

    if (strcmp(factory_id, CLAP_PLUGIN_FACTORY_INFO_VST3) == 0)
    {
        static const struct clap_plugin_factory_as_vst3 six_sines_vst3_factory = {
            "BaconPaul", "https://baconpaul.org", "", clap_get_vst3_info};

        return &six_sines_vst3_factory;
    }
    return nullptr;
}
bool clap_init(const char *p) { return true; }
void clap_deinit() {}
} // namespace baconpaul::visage_learn