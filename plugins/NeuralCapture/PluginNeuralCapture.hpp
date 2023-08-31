/*
 * Neural Capture audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#ifndef PLUGIN_NEURALCAPTURE_H
#define PLUGIN_NEURALCAPTURE_H

#include "DistrhoPlugin.hpp"
#include "profiler.h"

START_NAMESPACE_DISTRHO

#ifndef MIN
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )
#endif

#ifndef MAX
#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#endif

#ifndef CLAMP
#define CLAMP(v, min, max) (MIN((max), MAX((min), (v))))
#endif

#ifndef DB_CO
#define DB_CO(g) ((g) > -90.0f ? powf(10.0f, (g) * 0.05f) : 0.0f)
#endif

// -----------------------------------------------------------------------

class PluginNeuralCapture : public Plugin {
public:
    enum Parameters {
        paramButton = 0,
        paramState = 1,
        paramMeter = 2,
        paramCount
    };

    PluginNeuralCapture();

    ~PluginNeuralCapture();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override {
        return "NeuralCapture";
    }

    const char* getDescription() const override {
        return "A Neural Capture plug to make the process of cloning external soft/hardware a bit more comfortable ";
    }

    const char* getMaker() const noexcept override {
        return "brummer";
    }

    const char* getHomePage() const override {
        return "https://github.com/brummer10/neuralcapture";
    }

    const char* getLicense() const noexcept override {
        return "https://spdx.org/licenses/GPL-2.0-or-later";
    }

    uint32_t getVersion() const noexcept override {
        return d_version(0, 1, 0);
    }

    // Go to:
    //
    // http://service.steinberg.de/databases/plugin.nsf/plugIn
    //
    // Get a proper plugin UID and fill it in here!
    int64_t getUniqueId() const noexcept override {
        return d_cconst('a', 'b', 'c', 'd');
    }

    // -------------------------------------------------------------------
    // Init

    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void setParameterValue(uint32_t index, float value) override;
    void loadProgram(uint32_t index) override;

    void setOutputParameterValue(uint32_t index, float value);

    // -------------------------------------------------------------------
    // Optional

    // Optional callback to inform the plugin about a sample rate change.
    void sampleRateChanged(double newSampleRate) override;

    // -------------------------------------------------------------------
    // Process

    void activate() override;

    void run(const float**, float** outputs, uint32_t frames) override;


    // -------------------------------------------------------------------

private:
    float           fParams[paramCount];
    double          fSampleRate;
    float           button;
    float           state;
    float           meter;
    // pointer to dsp class
    profiler::Profil*  profil;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginNeuralCapture)
};

struct Preset {
    const char* name;
    float params[PluginNeuralCapture::paramCount];
};

const Preset factoryPresets[] = {
    {
    }
    //,{
    //    "Another preset",  // preset name
    //    {-14.0f, ...}      // array of presetCount float param values
    //}
};

const uint presetCount = sizeof(factoryPresets) / sizeof(Preset);

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // #ifndef PLUGIN_NEURALCAPTURE_H
