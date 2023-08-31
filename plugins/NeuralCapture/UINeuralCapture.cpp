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
using DGL_NAMESPACE::CairoGraphicsContext;
using DGL_NAMESPACE::CairoImage;
using DGL_NAMESPACE::CairoImageButton;
using DGL_NAMESPACE::CairoImageKnob;

// -----------------------------------------------------------------------
// Init / Deinit

UINeuralCapture::UINeuralCapture()
: UI(350, 250)  {
    kInitialHeight = 250;
    kInitialWidth = 350;
    fButton = new CairoButton(this, "Capture", [this] (const uint32_t index, float value) {this->setParameterValue(index, value);});
    fButton->setSize(200, 50);
    fButton->setAbsolutePos(75, 30);
    
    fProgressBar = new CairoProgressBar(this);
    fProgressBar->setSize(200, 30);
    fProgressBar->setAbsolutePos(75, 105);
    
    fPeekMeter = new CairoPeekMeter(this, 200, 50);
    fPeekMeter->setAbsolutePos(75, 160);

    setGeometryConstraints(kInitialWidth, kInitialHeight, true);
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
        case PluginNeuralCapture::paramButton:
            fButton->setValue(value);
            break;
        case PluginNeuralCapture::paramState:
            fProgressBar->setValue(value);
            if (value >=1.0) {
                fButton->setValue(0.0f);
                setParameterValue(0, 0.0f);
            }
            break;
        case PluginNeuralCapture::paramMeter:
            fPeekMeter->setValue(value);
            break;
    }
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


void UINeuralCapture::box_shadows(cairo_t* const cr, int wi, int h) {
    int width = getWidth();
    int height = getHeight();

    cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, wi, 0);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.33, 0.33, 0.33, 0.8);
    cairo_pattern_add_color_stop_rgba (pat, 0.4,  0.33, 0.33, 0.33, 0.3);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.33, 0.33, 0.33, 0.0);
    cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
    cairo_set_source(cr, pat);
    cairo_paint (cr);
    cairo_pattern_destroy (pat);
    pat = NULL;

    pat = cairo_pattern_create_linear (0, 0, 0, h);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.33, 0.33, 0.33, 0.8);
    cairo_pattern_add_color_stop_rgba (pat, 0.4,  0.33, 0.33, 0.33, 0.3);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.33, 0.33, 0.33, 0.0);
    cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
    cairo_set_source(cr, pat);
    cairo_paint (cr);
    cairo_pattern_destroy (pat);
    pat = NULL;

    pat = cairo_pattern_create_linear (width - wi, 0, width, 0);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.05, 0.05, 0.05, 0.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.4,  0.05, 0.05, 0.05, 0.3);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.05, 0.05, 0.05, 0.8);
    cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
    cairo_set_source(cr, pat);
    cairo_paint (cr);
    cairo_pattern_destroy (pat);
    pat = NULL;

    pat = cairo_pattern_create_linear (0, height - h, 0, height);
    cairo_pattern_add_color_stop_rgba (pat, 0,  0.05, 0.05, 0.05, 0.0);
    cairo_pattern_add_color_stop_rgba (pat, 0.4,  0.05, 0.05, 0.05, 0.3);
    cairo_pattern_add_color_stop_rgba (pat, 1,  0.05, 0.05, 0.05, 0.8);
    cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
    cairo_set_source(cr, pat);
    cairo_paint (cr);
    cairo_pattern_destroy (pat);
    pat = NULL;

}

/**
  A function called to draw the view contents.
*/
void UINeuralCapture::onCairoDisplay(const CairoGraphicsContext& context) {
    cairo_t* const cr = context.handle;

    cairo_set_source_rgba(cr, 0.13, 0.13, 0.13, 1.0);
    cairo_paint(cr);
    box_shadows(cr, 25, 25);
}

void UINeuralCapture::onResize(const ResizeEvent& ev)
{
    UI::onResize(ev);
    const float scaleHFactor = static_cast<float>(ev.size.getHeight())/static_cast<float>(kInitialHeight);
    const float scaleWFactor = static_cast<float>(ev.size.getWidth())/static_cast<float>(kInitialWidth);
    const float scaleFactor = scaleHFactor < scaleWFactor ? scaleHFactor : scaleWFactor;

    fButton->setSize(200*scaleFactor, 50*scaleFactor);
    fButton->setAbsolutePos(75*scaleWFactor, 30*scaleHFactor);
    
    fProgressBar->setSize(200*scaleFactor, 30*scaleFactor);
    fProgressBar->setAbsolutePos(75*scaleWFactor, 105*scaleHFactor);
    
    fPeekMeter->setSize( 200*scaleFactor, 50*scaleFactor);
    fPeekMeter->setAbsolutePos(75*scaleWFactor, 160*scaleHFactor);
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
/*
bool UINeuralCapture::onMouse(const MouseEvent& ev) {
    fprintf(stderr, "mouse main\n");
    fButton->onMouse(ev);
    return false;
    (void)ev;
}
*/
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
    return new UINeuralCapture;
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
