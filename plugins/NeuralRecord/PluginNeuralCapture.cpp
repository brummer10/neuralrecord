/*
 * Neural Capture audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "PluginNeuralCapture.hpp"
#include "profiler.cc"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

PluginNeuralCapture::PluginNeuralCapture()
    : Plugin(paramCount, presetCount, 0)  // paramCount param(s), presetCount program(s), 0 states
{

    profil = new profiler::Profil(1, [this] (const uint32_t index, float value) {this->setOutputParameterValue(index, value);},
                                     [this] (const uint32_t index, float value) {this->requestParameterValueChange(index, value);});
    profil->set_samplerate(getSampleRate(), profil); // init the DSP class

    for (unsigned p = 0; p < paramCount; ++p) {
        Parameter param;
        initParameter(p, param);
        setParameterValue(p, param.ranges.def);
    }
}

PluginNeuralCapture::~PluginNeuralCapture() {
    profil->activate_plugin(false, profil);
    profil->delete_instance(profil);
}

// -----------------------------------------------------------------------
// Init

void PluginNeuralCapture::initParameter(uint32_t index, Parameter& parameter) {
    if (index >= paramCount)
        return;

    switch (index) {
        case paramButton:
            parameter.name = "Capture";
            parameter.shortName = "Capture";
            parameter.symbol = "PROFILE";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.ranges.def = 0.0f;
            parameter.hints = kParameterIsAutomatable|kParameterIsInteger|kParameterIsBoolean;
            break;
        case paramState:
            parameter.name = "State";
            parameter.shortName = "State";
            parameter.symbol = "STATE";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 1.0f;
            parameter.hints = kParameterIsAutomatable|kParameterIsOutput;
            break;
        case paramMeter:
            parameter.name = "Meter";
            parameter.shortName = "Meter";
            parameter.symbol = "METER";
            parameter.ranges.min = -130.0f;
            parameter.ranges.max = 4.0f;
            parameter.hints = kParameterIsAutomatable|kParameterIsOutput;
            break;
        case paramError:
            parameter.name = "Error";
            parameter.shortName = "Error";
            parameter.symbol = "ERRORS";
            parameter.ranges.min = 0.0f;
            parameter.ranges.max = 3.0f;
            parameter.hints = kParameterIsOutput;
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
    //fprintf(stderr, "setParameterValue %i %f\n", index,value);
    switch (index) {
        case paramButton:
            button = fParams[paramButton];
            break;
        case paramState:
            state = fParams[paramState];
            break;
        case paramMeter:
            meter = fParams[paramMeter];
            break;
        case paramError:
            p_error = fParams[paramError];
            break;
    }
    profil->connect_ports(index, value, profil);
}

void PluginNeuralCapture::setOutputParameterValue(uint32_t index, float value)
{
    fParams[index] = value;
    //fprintf(stderr, "setOutputParameterValue %i %f\n", index,value);
    switch (index) {
        case paramButton:
            button = fParams[paramButton];
            break;
        case paramState:
            //fprintf(stderr, "setOutputParameterValue %i %f\n", index,value);
            state = fParams[paramState];
            break;
        case paramMeter:
            meter = fParams[paramMeter];
            break;
        case paramError:
            p_error = fParams[paramError];
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
    profil->activate_plugin(true, profil);
}



void PluginNeuralCapture::run(const float** inputs, float** outputs,
                              uint32_t frames) {

    // get the left and right audio inputs
    const float* const inpL = inputs[0];
   // const float* const inpR = inputs[1];

    // get the left and right audio outputs
    float* const outL = outputs[0];
   // float* const outR = outputs[1];

    profil->mono_audio(static_cast<int>(frames), inpL, outL, profil);
}

// -----------------------------------------------------------------------

Plugin* createPlugin() {
    return new PluginNeuralCapture();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
