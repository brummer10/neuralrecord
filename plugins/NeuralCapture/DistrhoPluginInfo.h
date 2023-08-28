/*
 * Neural Capture audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#ifndef DISTRHO_PLUGIN_INFO_H
#define DISTRHO_PLUGIN_INFO_H

#define DISTRHO_PLUGIN_BRAND "MOD"
#define DISTRHO_PLUGIN_NAME  "NeuralCapture"
#define DISTRHO_PLUGIN_URI   "https://github.com/brummer10/neuralcapture"
#define DISTRHO_PLUGIN_CLAP_ID "com.github.brummer10.neuralcapture"

#define DISTRHO_PLUGIN_HAS_UI        1
#define DISTRHO_UI_USE_NANOVG        0

#define DISTRHO_PLUGIN_IS_RT_SAFE       1
#define DISTRHO_PLUGIN_NUM_INPUTS       2
#define DISTRHO_PLUGIN_NUM_OUTPUTS      2
#define DISTRHO_PLUGIN_WANT_TIMEPOS     0
#define DISTRHO_PLUGIN_WANT_PROGRAMS    1
#define DISTRHO_PLUGIN_WANT_MIDI_INPUT  0
#define DISTRHO_PLUGIN_WANT_MIDI_OUTPUT 0

#define DISTRHO_PLUGIN_LV2_CATEGORY "lv2:AmplifierPlugin"
#define DISTRHO_PLUGIN_VST3_CATEGORIES "Fx|Tools|Stereo"
#define DISTRHO_PLUGIN_CLAP_FEATURES "audio-effect", "utility", "stereo"

#endif // DISTRHO_PLUGIN_INFO_H
