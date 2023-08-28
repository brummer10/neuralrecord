/*
 * Neural Capture audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "PluginNeuralCapture.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginNeuralCapture::PluginNeuralCapture()
    : Plugin(paramCount, presetCount, 0)  // paramCount param(s), presetCount program(s), 0 states
{
    smooth_gain = new CParamSmooth(20.0f, getSampleRate());

    for (unsigned p = 0; p < paramCount; ++p) {
        Parameter param;
        initParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

PluginNeuralCapture::~PluginNeuralCapture() {
    delete smooth_gain;
}

// -----------------------------------------------------------------------
// Init

void PluginNeuralCapture::initParameter(uint32_t index, Parameter& parameter) {
    if (index >= paramCount)
        return;

    parameter.ranges.min = -90.0f;
    parameter.ranges.max = 30.0f;
    parameter.ranges.def = -0.0f;
    parameter.unit = "db";
    parameter.hints = kParameterIsAutomatable;

    switch (index) {
        case paramGain:
            parameter.name = "Gain (dB)";
            parameter.shortName = "Gain";
            parameter.symbol = "gain";
            break;
    }
}

/**
  Set the name of the program @a index.
  This function will be called once, shortly after the plugin is created.
*/
void PluginNeuralCapture::initProgramName(uint32_t index, String& programName) {
    if (index < presetCount) {
        programName = factoryPresets[index].name;
    }
}

// -----------------------------------------------------------------------
// Internal data

/**
  Optional callback to inform the plugin about a sample rate change.
*/
void PluginNeuralCapture::sampleRateChanged(double newSampleRate) {
    fSampleRate = newSampleRate;
    smooth_gain->setSampleRate(newSampleRate);
}

/**
  Get the current value of a parameter.
*/
float PluginNeuralCapture::getParameterValue(uint32_t index) const {
    return fParams[index];
}

/**
  Change a parameter value.
*/
void PluginNeuralCapture::setParameterValue(uint32_t index, float value) {
    fParams[index] = value;

    switch (index) {
        case paramGain:
            gain = DB_CO(CLAMP(fParams[paramGain], -90.0, 30.0));
            break;
    }
}

/**
  Load a program.
  The host may call this function from any context,
  including realtime processing.
*/
void PluginNeuralCapture::loadProgram(uint32_t index) {
    if (index < presetCount) {
        for (int i=0; i < paramCount; i++) {
            setParameterValue(i, factoryPresets[index].params[i]);
        }
    }
}

// -----------------------------------------------------------------------
// Process

void PluginNeuralCapture::activate() {
    // plugin is activated
}



void PluginNeuralCapture::run(const float** inputs, float** outputs,
                              uint32_t frames) {

    // get the left and right audio inputs
    const float* const inpL = inputs[0];
    const float* const inpR = inputs[1];

    // get the left and right audio outputs
    float* const outL = outputs[0];
    float* const outR = outputs[1];

    // apply gain against all samples
    for (uint32_t i=0; i < frames; ++i) {
        float gainval = smooth_gain->process(gain);
        outL[i] = inpL[i] * gainval;
        outR[i] = inpR[i] * gainval;
    }
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginNeuralCapture();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
