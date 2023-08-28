/*
 * Neural Capture audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#include "UINeuralCapture.hpp"
#include "Window.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------
// Init / Deinit

UINeuralCapture::UINeuralCapture()
: UI(600, 400)  {

}

UINeuralCapture::~UINeuralCapture() {

}

// -----------------------------------------------------------------------
// DSP/Plugin callbacks

/**
  A parameter has changed on the plugin side.
  This is called by the host to inform the UI about parameter changes.
*/
void UINeuralCapture::parameterChanged(uint32_t index, float value) {
    switch (index) {
        case PluginNeuralCapture::paramGain:
            // do something when Gain param is set, such as update a widget
            break;
    }

    (void)value;
}

/**
  A program has been loaded on the plugin side.
  This is called by the host to inform the UI about program changes.
*/
void UINeuralCapture::programLoaded(uint32_t index) {
    if (index < presetCount) {
        for (int i=0; i < PluginNeuralCapture::paramCount; i++) {
            // set values for each parameter and update their widgets
            parameterChanged(i, factoryPresets[index].params[i]);
        }
    }
}

/**
  Optional callback to inform the UI about a sample rate change on the plugin side.
*/
void UINeuralCapture::sampleRateChanged(double newSampleRate) {
    (void)newSampleRate;
}

// -----------------------------------------------------------------------
// Optional UI callbacks

/**
  Idle callback.
  This function is called at regular intervals.
*/
void UINeuralCapture::uiIdle() {

}

/**
  Window reshape function, called when the parent window is resized.
*/
void UINeuralCapture::uiReshape(uint width, uint height) {
    (void)width;
    (void)height;
}

// -----------------------------------------------------------------------
// Widget callbacks


/**
  A function called to draw the view contents.
*/
void UINeuralCapture::onDisplay() {

    cairo_t* cr = getParentWindow().getGraphicsContext().cairo;

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
}


// -----------------------------------------------------------------------
// Optional widget callbacks; return true to stop event propagation, false otherwise.

/**
  A function called when a key is pressed or released.
*/
bool UINeuralCapture::onKeyboard(const KeyboardEvent& ev) {
    return false;
    (void)ev;
}

/**
  A function called when a mouse button is pressed or released.
*/
bool UINeuralCapture::onMouse(const MouseEvent& ev) {
    return false;
    (void)ev;
}

/**
  A function called when the mouse pointer moves.
*/
bool UINeuralCapture::onMotion(const MotionEvent& ev) {
    return false;
    (void)ev;
}

/**
  A function called on scrolling (e.g. mouse wheel or track pad).
*/
bool UINeuralCapture::onScroll(const ScrollEvent& ev) {
    return false;
    (void)ev;
}

// -----------------------------------------------------------------------

UI* createUI() {
    return new UINeuralCapture();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
