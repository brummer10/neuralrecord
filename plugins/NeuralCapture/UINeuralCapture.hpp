/*
 * Neural Capture audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#ifndef UI_NEURALCAPTURE_H
#define UI_NEURALCAPTURE_H

#include "DistrhoUI.hpp"
#include "PluginNeuralCapture.hpp"

START_NAMESPACE_DISTRHO

class UINeuralCapture : public UI {
public:
    UINeuralCapture();
    ~UINeuralCapture();

protected:
    void parameterChanged(uint32_t, float value) override;
    void programLoaded(uint32_t index) override;
    void sampleRateChanged(double newSampleRate) override;

    void uiIdle() override;
    void uiReshape(uint width, uint height) override;

    void onDisplay() override;

    bool onKeyboard(const KeyboardEvent& ev) override;
    bool onMouse(const MouseEvent& ev) override;
    bool onMotion(const MotionEvent& ev) override;
    bool onScroll(const ScrollEvent& ev) override;

private:
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(UINeuralCapture)
};

END_NAMESPACE_DISTRHO

#endif
