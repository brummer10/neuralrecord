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
: UI(350, 250, true), theme() {
    kInitialHeight = 250;
    kInitialWidth = 350;
    sizeGroup = new UiSizeGroup(kInitialWidth, kInitialHeight);
    getPathInfo(pathInfo);
    inputFile = "Error: Couldn't find ";
    inputFile += pathInfo;
    inputFile += "input.wav";

    outputFile = "Saved to ";
    outputFile += pathInfo;
    outputFile += "target.wav";

    fButton = new CairoButton(this, theme, dynamic_cast<UI*>(this), "Capture", PluginNeuralCapture::paramButton);
    sizeGroup->addToSizeGroup(fButton, 75, 30, 200, 50);
    
    fProgressBar = new CairoProgressBar(this, theme);
    sizeGroup->addToSizeGroup(fProgressBar, 75, 105, 200, 30);
    
    fPeekMeter = new CairoPeekMeter(this, theme);
    sizeGroup->addToSizeGroup(fPeekMeter, 75, 160, 200, 50);

    fToolTip = new CairoToolTip(this, theme, "This is a Message");
    sizeGroup->addToSizeGroup(fToolTip, 0, 95, 350, 50);

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
            } else if (value > 0.9969) {
                fToolTip->setLabel(outputFile.c_str());                
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
            else if ((int)value == 4) 
                fToolTip->setLabel(inputFile.c_str());

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
  Get the path were recording been saved
*/

void UINeuralCapture::getPathInfo(std::string &pInfo)
{
#ifndef  __MOD_DEVICES__
#if defined(WIN32) || defined(_WIN32)
    pInfo = getenv("USERPROFILE");
    if (pInfo.empty()) {
        pInfo = getenv("HOMEDRIVE");
        pInfo +=  getenv("HOMEPATH");
    }
#else
    pInfo += getenv("HOME");
#endif
    pInfo +=PATH_SEPARATOR;
    pInfo +="profiles";
    pInfo +=PATH_SEPARATOR;
#else
    pInfo += "/data/user-files/Audio Recordings/profiles/";
#endif
    //pInfo += "target.wav";
}


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
    theme.setCairoColour(cr, theme.idColourBackground);
    cairo_paint(cr);
    theme.boxShadow(cr, width, height, 25, 25);
    cairo_pop_group_to_source (cr);
    cairo_paint (cr);
}

void UINeuralCapture::onResize(const ResizeEvent& ev)
{
    UI::onResize(ev);
    sizeGroup->resizeAspectSizeGroup(ev.size.getWidth(), ev.size.getHeight());
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
/*
bool UINeuralCapture::onMotion(const MotionEvent& ev) {
    return false;
    (void)ev;
}
*/

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
