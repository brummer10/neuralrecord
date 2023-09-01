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
: UI(350, 250)  {
    kInitialHeight = 250;
    kInitialWidth = 350;
    fButton = new CairoButton(this, "Capture",
                [this] (const uint32_t index, float value) {this->setParameterValue(index, value);});
    fButton->setSize(200, 50);
    fButton->setAbsolutePos(75, 30);
    
    fProgressBar = new CairoProgressBar(this);
    fProgressBar->setSize(200, 30);
    fProgressBar->setAbsolutePos(75, 105);
    
    fPeekMeter = new CairoPeekMeter(this, 200, 50);
    fPeekMeter->setAbsolutePos(75, 160);

    fToolTip = new CairoToolTip(this, "This is a Error Message");
    fToolTip->setSize(350, 50);
    fToolTip->setAbsolutePos(0, 105);

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
                setParameterValue(PluginNeuralCapture::paramButton, 0.0f);
            }
            break;
        case PluginNeuralCapture::paramMeter:
            fPeekMeter->setValue(value);
            break;
        case PluginNeuralCapture::paramError:
            // if ((int)value == 0) fToolTip->unset();
            if ((int)value > 0) 
                fButton->setValue(0.0f);
            if ((int)value == 1) 
                fToolTip->setLabel("Error: no signal comes in, stop the process here");
            else if ((int)value == 2) 
                fToolTip->setLabel("Error: seems we receive garbage, stop the process here");
            else if ((int)value == 3) 
                fToolTip->setLabel("Error: Sample Rate mismatch, please use 48kHz");

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
    if (newSampleRate != 48000) fToolTip->setLabel("Sample Rate mismatch, please use 48kHz");
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
void UINeuralCapture::onCairoDisplay(const CairoGraphicsContext& context) {
    cairo_t* const cr = context.handle;
    int width = getWidth();
    int height = getHeight();

    cairo_push_group (cr);
    cairo_set_source_rgba(cr, 0.13, 0.13, 0.13, 1.0);
    cairo_paint(cr);
    box_shadow(cr, width, height, 25, 25);
    cairo_pop_group_to_source (cr);
    cairo_paint (cr);
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

    fToolTip->setSize(350*scaleFactor, 50*scaleFactor);
    fToolTip->setAbsolutePos(0*scaleFactor, 105*scaleFactor);
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
