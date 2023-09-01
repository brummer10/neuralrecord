/*
 * Neural Capture audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#ifndef UI_NEURALCAPTURE_H
#define UI_NEURALCAPTURE_H

#include <functional>
#include "DistrhoUI.hpp"
#include "PluginNeuralCapture.hpp"
#include "Cairo.hpp"
#include "CairoWidgets.hpp"

START_NAMESPACE_DISTRHO

class UINeuralCapture : public UI, public CairoShadows {
public:
    UINeuralCapture();
    ~UINeuralCapture();

protected:
    void parameterChanged(uint32_t, float value) override;
    void programLoaded(uint32_t index) override;
    void sampleRateChanged(double newSampleRate) override;

    void uiIdle() override;
    void uiReshape(uint width, uint height) override;
    
    void onCairoDisplay(const CairoGraphicsContext& context) override;

    bool onKeyboard(const KeyboardEvent& ev) override;
   // bool onMouse(const MouseEvent& ev) override;
    bool onMotion(const MotionEvent& ev) override;
    bool onScroll(const ScrollEvent& ev) override;
    void onResize(const ResizeEvent& ev) override;

private:
    int kInitialHeight;
    int kInitialWidth;
    ScopedPointer<CairoButton> fButton;
    ScopedPointer<CairoProgressBar> fProgressBar;
    ScopedPointer<CairoPeekMeter> fPeekMeter;
    ScopedPointer<CairoToolTip> fToolTip;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UINeuralCapture)
};

END_NAMESPACE_DISTRHO

#endif
