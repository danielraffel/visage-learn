/*
 * BaconPaul learns Visage
 *
 * MIT License, 2025, https://github.com/baconpaul/visage-learn
 */

#include "visage-learn-clap.h"
#include "sst/plugininfra/version_information.h"

#include <clap/helpers/plugin.hxx>
#include <clap/helpers/host-proxy.hxx>

#include "ui/visage-learn-editor.h"

namespace baconpaul::visage_learn
{

/*
 * Clap Factory API
 */
const clap_plugin_descriptor *getDescriptor()
{
    static const char *features[] = {CLAP_PLUGIN_FEATURE_INSTRUMENT,
                                     CLAP_PLUGIN_FEATURE_SYNTHESIZER, "Free and Open Source",
                                     "Audio Rate Modulation", nullptr};

    static char versionNum[1024];

    static clap_plugin_descriptor desc = {
        CLAP_VERSION,
        "org.baconpaul.visage-learn",
        PRODUCT_NAME,
        "BaconPaul",
        "https://baconpaul.org",
        "",
        "",
        sst::plugininfra::VersionInformation::project_version_and_hash,
        "Looks Purty",
        &features[0]};
    return &desc;
}

static constexpr clap::helpers::MisbehaviourHandler misLevel =
    clap::helpers::MisbehaviourHandler::Ignore;
static constexpr clap::helpers::CheckingLevel checkLevel = clap::helpers::CheckingLevel::Maximal;

using plugHelper_t = clap::helpers::Plugin<misLevel, checkLevel>;

struct VisageLearnClap : public plugHelper_t
{
    VisageLearnClap(const clap_host *host) : plugHelper_t(getDescriptor(), host) {}

    std::unique_ptr<baconpaul::visage_learn::VisageLearnEditor> editor_;

#ifdef __linux__
    bool implementsPosixFdSupport() const noexcept override { return true; }
    void onPosixFd(int fd, clap_posix_fd_flags_t flags) noexcept
    {
        if (app_ && app_->window())
            app_->window()->processPluginFdEvents();
    }
#endif

    bool implementsGui() const noexcept override { return true; }
    bool guiSetScale(double scale) noexcept override { return false; }
    bool guiCanResize() const noexcept override { return false; }

    bool guiIsApiSupported(const char *api, bool is_floating) noexcept override
    {
        if (is_floating)
            return false;

#ifdef _WIN32
        if (strcmp(api, CLAP_WINDOW_API_WIN32) == 0)
            return true;
#elif __APPLE__
        if (strcmp(api, CLAP_WINDOW_API_COCOA) == 0)
            return true;
#elif __linux__
        if (strcmp(api, CLAP_WINDOW_API_X11) == 0)
            return true;
#endif

        return false;
    }

    bool guiCreate(const char *api, bool is_floating) noexcept override
    {
        editor_ = std::make_unique<baconpaul::visage_learn::VisageLearnEditor>();

        return true;
    }

    void guiDestroy() noexcept override
    {
#if __linux__
        if (app_ && app_->window() && _host.canUsePosixFdSupport())
            _host.posixFdSupportUnregister(app_->window()->posixFd());
#endif
        editor_->close();
    }

    bool guiSetParent(const clap_window *window) noexcept override
    {
        if (editor_ == nullptr)
            return false;

        VLLOG("guiSetParent " << window);

        auto res = editor_->doGuiSetParent(window->ptr);

#if __linux__
        if (_host.canUsePosixFdSupport() && app_->window() == nullptr)
        {
            int fd_flags = CLAP_POSIX_FD_READ | CLAP_POSIX_FD_WRITE | CLAP_POSIX_FD_ERROR;
            return _host.posixFdSupportRegister(app_->window()->posixFd(), fd_flags);
        }
#endif
        return true;
    }

    bool guiAdjustSize(uint32_t *width, uint32_t *height) noexcept override
    {
        if (editor_ == nullptr)
            return false;

        editor_->adjustWindowDimensions(width, height, true, true);
        return true;
    }

    bool guiSetSize(uint32_t width, uint32_t height) noexcept override
    {
        if (editor_ == nullptr)
            return false;

        editor_->setWindowDimensions(width, height);
        return true;
    }

    bool guiGetSize(uint32_t *width, uint32_t *height) noexcept override
    {
        if (editor_ == nullptr)
            return false;

        *width = baconpaul::visage_learn::VisageLearnEditor::edWidth;
        *height = baconpaul::visage_learn::VisageLearnEditor::edHeight;
        return true;
    }

    bool guiShow() noexcept override { return true; }

  protected:
    bool implementsState() const noexcept override { return true; }
    bool stateSave(const clap_ostream *stream) noexcept override { return true; }
    bool stateLoad(const clap_istream *stream) noexcept override { return true; }

    bool implementsParams() const noexcept override { return true; }
    uint32_t paramsCount() const noexcept override { return 0; }
    bool paramsInfo(uint32_t paramIndex, clap_param_info *info) const noexcept override
    {
        return false;
    }
    bool paramsValue(clap_id paramId, double *value) noexcept override { return false; }
    bool paramsValueToText(clap_id paramId, double value, char *display,
                           uint32_t size) noexcept override
    {
        return false;
    }
    bool paramsTextToValue(clap_id paramId, const char *display, double *value) noexcept override
    {
        return false;
    }
    void paramsFlush(const clap_input_events *in, const clap_output_events *out) noexcept override
    {
    }
    int32_t getParamIndexForParamId(clap_id paramId) const noexcept override { return 0; }
    bool isValidParamId(clap_id paramId) const noexcept override { return false; }

  public:
    bool implementsAudioPorts() const noexcept override { return true; }
    uint32_t audioPortsCount(bool isInput) const noexcept override { return isInput ? 0 : 1; }
    bool audioPortsInfo(uint32_t index, bool isInput,
                        clap_audio_port_info *info) const noexcept override
    {
        assert(!isInput);
        if (isInput || index > 1)
            return false;
        info->id = 75241 + index;
        info->in_place_pair = CLAP_INVALID_ID;
        strncpy(info->name, "Main Out", sizeof(info->name));
        info->flags = CLAP_AUDIO_PORT_IS_MAIN;
        info->channel_count = 2;
        info->port_type = CLAP_PORT_STEREO;
        return true;
    }

  protected:
    bool implementsNotePorts() const noexcept override { return true; }
    uint32_t notePortsCount(bool isInput) const noexcept override { return isInput ? 1 : 0; }
    bool notePortsInfo(uint32_t index, bool isInput,
                       clap_note_port_info *info) const noexcept override
    {
        assert(isInput);
        if (!isInput || index > 1)
            return false;
        info->id = 7755 + index;
        strncpy(info->name, "Notes In", sizeof(info->name));
        info->supported_dialects =
            CLAP_NOTE_DIALECT_MIDI | CLAP_NOTE_DIALECT_MIDI_MPE | CLAP_NOTE_DIALECT_CLAP;
        info->preferred_dialect = CLAP_NOTE_DIALECT_CLAP;
        return true;
    }
};

extern const clap_plugin *makePlugin(const clap_host *h, bool)
{
    auto res = new VisageLearnClap(h);
    return res->clapPlugin();
}

} // namespace baconpaul::visage_learn