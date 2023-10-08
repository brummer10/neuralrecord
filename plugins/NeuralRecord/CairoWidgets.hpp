/*
 * Neural Capture audio effect based on DISTRHO Plugin Framework (DPF)
 *
 * SPDX-License-Identifier:  GPL-2.0 license 
 *
 * Copyright (C) 2023 brummer <brummer@web.de>
 */

#pragma once

#ifndef CAIROWIDGETS_H
#define CAIROWIDGETS_H

#include <functional>
#include <atomic>
#include "Cairo.hpp"
#include "extra/Runner.hpp"

START_NAMESPACE_DISTRHO

class CairoColourTheme
{
public:
    CairoColourTheme()
    {
        init();
    }

    struct CairoColour{
        double r;
        double g;
        double b;
        double a;
    };

    void setCairoColour(cairo_t* const cr, const CairoColour idColour, float darker = 0.8f)
    {
        cairo_set_source_rgba(cr, idColour.r * darker, idColour.g * darker,
                                idColour.b * darker, idColour.a);
    }

    void setIdColour(CairoColour &idColour, double r, double g, double b, double a) {
        idColour = CairoColour {r, g, b, a};
    }

    void boxShadowInset(cairo_t* const cr, int width, int height)
    {
        cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, width, 0);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.95, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.1, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;
        pat = cairo_pattern_create_linear (0, 0, 0, height);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.9, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.1, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.0);
        cairo_pattern_add_color_stop_rgba 
            (pat, 0, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
    }

    void boxShadowOutset(cairo_t* const cr, int width, int height)
    {
        cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, width, 0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.05, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.95, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.0);
        cairo_pattern_add_color_stop_rgba 
            (pat, 1, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;
        pat = cairo_pattern_create_linear (0, 0, 0, height);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.1, idColourBoxLight.r * 0.6, idColourBoxLight.g * 0.6, idColourBoxLight.b * 0.6, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.9, idColourBoxShadow.r * 2.0, idColourBoxShadow.g * 2.0, idColourBoxShadow.b * 2.0, 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
    }

    void boxShadow(cairo_t* const cr, int width, int height, int w, int h)
    {
        cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, w, 0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.8);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.4, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.3);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.0);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;

        pat = cairo_pattern_create_linear (0, 0, 0, h);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.8);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.4, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.3);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxLight.r, idColourBoxLight.g, idColourBoxLight.b, idColourBoxLight.a * 0.0);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;

        pat = cairo_pattern_create_linear (width - w, 0, width, 0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.4, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.3);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.8);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;

        pat = cairo_pattern_create_linear (0, height - h, 0, height);
        cairo_pattern_add_color_stop_rgba
            (pat, 0, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.0);
        cairo_pattern_add_color_stop_rgba
            (pat, 0.4, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.3);
        cairo_pattern_add_color_stop_rgba
            (pat, 1, idColourBoxShadow.r, idColourBoxShadow.g, idColourBoxShadow.b, idColourBoxShadow.a * 0.8);
        cairo_pattern_set_extend(pat, CAIRO_EXTEND_NONE);
        cairo_set_source(cr, pat);
        cairo_paint (cr);
        cairo_pattern_destroy (pat);
        pat = NULL;
    }

    CairoColour idColourBackground;
    CairoColour idColourBackgroundNormal;
    CairoColour idColourBackgroundPrelight;
    CairoColour idColourBackgroundActive;
    CairoColour idColourBackgroundProgress;

    CairoColour idColourForground;
    CairoColour idColourForgroundNormal;
    CairoColour idColourForgroundActive;

    CairoColour idColourFrame;

    CairoColour idColourBoxShadow;
    CairoColour idColourBoxLight;

protected:

    void init()
    {
        setIdColour(idColourBackground, 0.13, 0.13, 0.13, 1);
        setIdColour(idColourBackgroundNormal, 0.13, 0.13, 0.13, 1.0);
        setIdColour(idColourBackgroundPrelight, 0.63, 0.63, 0.63, 0.03);
        setIdColour(idColourBackgroundActive, 0.63, 0.13, 0.13, 1.0);
        setIdColour(idColourBackgroundProgress, 0.4, 0.4, 0.4, 1.0);

        setIdColour(idColourForground, 0.63, 0.63, 0.63, 1.0);
        setIdColour(idColourForgroundNormal, 0.63, 0.63, 0.63, 1.0);
        setIdColour(idColourForgroundActive, 0.93, 0.63, 0.63, 1.0);

        setIdColour(idColourFrame, 0.03, 0.03, 0.03, 1.0);

        setIdColour(idColourBoxShadow,  0.05, 0.05, 0.05, 1.0);
        setIdColour(idColourBoxLight, 0.33, 0.33, 0.33, 1.0);
    }

private:
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoColourTheme)
};

// -----------------------------------------------------------------------

class CairoButton : public CairoSubWidget
{
public:

    explicit CairoButton(SubWidget* const parent, CairoColourTheme &theme_,
                            UI *ui, const char* lab, const uint32_t index)
        : CairoSubWidget(parent),
          theme(theme_),
          setParameterValue([ui] (const uint32_t index, float value)
                                {ui->setParameterValue(index, value);}),
          label(lab), port(index)
          {
            init();
          }

    explicit CairoButton(TopLevelWidget* const parent, CairoColourTheme &theme_,
                                UI *ui, const char* lab, const uint32_t index)
        : CairoSubWidget(parent),
          theme(theme_),
          setParameterValue([ui] (const uint32_t index, float value)
                                {ui->setParameterValue(index, value);}),
          label(lab), port(index)
          {
            init();
          }

    void setValue(float v)
    {
        value = v;
        state = (int)value;
        repaint();
    }

protected:

    void init()
    {
        value = 0.0f;
        state = 0;
        prelight = false;
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        const Size<uint> sz = getSize();
        const int w = sz.getWidth();
        const int h = sz.getHeight();

        cairo_push_group (cr);

        if (!state)
            theme.setCairoColour(cr, theme.idColourBackgroundNormal);
        else 
            theme.setCairoColour(cr, theme.idColourBackgroundActive);
        cairo_paint(cr);

        if (prelight) {
            theme.setCairoColour(cr, theme.idColourBackgroundPrelight);
            cairo_paint(cr);
        }

        if (!state)
            theme.boxShadowOutset(cr, w, h);
        else
            theme.boxShadowInset(cr, w, h); 

        int offset = 0;
        cairo_text_extents_t extents;
        if(state==0) {
            theme.setCairoColour(cr, theme.idColourForgroundNormal);
        } else if(state==1) {
            theme.setCairoColour(cr, theme.idColourForgroundActive);
            offset = 2;
        }
        cairo_set_font_size (cr, h/2.2);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                   CAIRO_FONT_WEIGHT_BOLD);
        cairo_text_extents(cr, label , &extents);

        cairo_move_to (cr, (w-extents.width)*0.5 +offset, (h+extents.height)*0.45 +offset);
        cairo_show_text(cr, label);

        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

    bool onMouse(const MouseEvent& event) override
    {
        if (!event.press && contains(event.pos)) // mouse button release
        {
            value = value ? 0.0f : 1.0f;
            state = !state;
            setParameterValue(port, value);
            repaint();
        }

        return CairoSubWidget::onMouse(event);
    }

    bool onMotion(const MotionEvent& event) override
    {
        if (contains(event.pos)) // enter
        {
            if (!prelight) {
                prelight = true;
                repaint();
            }
        }
        else if (prelight) // leave
        {
            prelight = false;
            repaint();
        }

        return CairoSubWidget::onMotion(event);
    }

private:
    CairoColourTheme &theme;
    std::function<void(const uint32_t, float) > setParameterValue;
    float value;
    uint state;
    bool prelight;
    const char* label;
    const uint32_t port;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoButton)
};

// -----------------------------------------------------------------------

class CairoProgressBar : public CairoSubWidget
{
public:

    explicit CairoProgressBar(SubWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          theme(theme_)
          {
            init();
          }

    explicit CairoProgressBar(TopLevelWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          theme(theme_)
          {
            init();
          }

    void setValue(float v)
    {
        value = v;
        repaint();
    }

protected:
    void init()
    {
        value = 0.0f;
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        cairo_push_group (cr);

        const Size<uint> sz = getSize();
        const int width = sz.getWidth();
        const int height = sz.getHeight();

        theme.setCairoColour(cr,theme.idColourFrame);
        cairo_rectangle(cr,0, 0, width, height);
        cairo_set_line_width(cr,2);
        cairo_stroke(cr);

        theme.setCairoColour(cr, theme.idColourBackgroundProgress);
        cairo_rectangle(cr,0, 0, width * value, height);
        cairo_fill(cr);

        cairo_text_extents_t extents;
        cairo_set_font_size (cr, height/2.2);
        char s[64];
        snprintf(s, 63,"%d%%",  (int) (value * 100.0));
        cairo_text_extents(cr,s , &extents);
        cairo_move_to (cr, width * 0.5 - extents.width * 0.5,  height * 0.5 + extents.height * 0.5 );
        theme.setCairoColour(cr, theme.idColourForground);
        cairo_set_operator(cr, CAIRO_OPERATOR_ADD);
        cairo_show_text(cr, s);
        cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
        cairo_new_path (cr);
        theme.boxShadowInset(cr, width, height);
        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

private:
    CairoColourTheme &theme;
    float value;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoProgressBar)
};

// -----------------------------------------------------------------------

class CairoPeekMeter : public CairoSubWidget
{
public:

    explicit CairoPeekMeter(SubWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          image(nullptr),
          theme(theme_)
          {
            init();
          }

    explicit CairoPeekMeter(TopLevelWidget* const parent, CairoColourTheme &theme_)
        : CairoSubWidget(parent),
          image(nullptr),
          theme(theme_)
          {
            init();
          }

    void setValue(float v)
    {
        value = v;
        repaint();
    }

    ~CairoPeekMeter() {
        cairo_surface_destroy(image);
    }

protected:
    void init()
    {
        old_value = -70.0f;
        std_value = -70.0f;
        value = -70.0f;
    }

    float power2db(float power)
    {
        const float falloff = 27 * 60 * 0.0005;
        const float fallsoft = 6 * 60 * 0.0005;
        //power = 20.*log10(power);
        if (power <=  20.*log10(0.00021)) { // -70db
            power = 20.*log10(0.00000000001); //-137db
            old_value = MIN(0.0,old_value - fallsoft);
        }
        // retrieve old meter value and consider falloff
        if (power < std_value) {
            power = MAX(power, std_value - falloff);
            old_value = MIN(0.0,old_value - fallsoft);
        }
        if (power > old_value) {
            old_value = power ;
        }
        
        std_value = power;
        return  power;
    }

    float logMeter (float db)
    {
        float def = 0.0f; /* Meter deflection %age */

        if (db < -70.0f) {
            def = 0.0f;
        } else if (db < -60.0f) {
            def = (db + 70.0f) * 0.25f;
        } else if (db < -50.0f) {
            def = (db + 60.0f) * 0.5f + 2.5f;
        } else if (db < -40.0f) {
            def = (db + 50.0f) * 0.75f + 7.5f;
        } else if (db < -30.0f) {
            def = (db + 40.0f) * 1.5f + 15.0f;
        } else if (db < -20.0f) {
            def = (db + 30.0f) * 2.0f + 30.0f;
        } else if (db < 6.0f) {
            def = (db + 20.0f) * 2.5f + 50.0f;
        } else {
            def = 115.0f;
        }

        /* 115 is the deflection %age that would be
           when db=6.0. this is an arbitrary
           endpoint for our scaling.
        */
        return def/115.0f;
    }


    void drawMeterImage(int width, int height)
    {
        image = cairo_image_surface_create( 
                            CAIRO_FORMAT_ARGB32, width, height*2);
        cairo_t *cri = cairo_create (image);
        cairo_push_group (cri);

        theme.setCairoColour(cri, theme.idColourFrame);
        cairo_paint(cri);

        cairo_pattern_t *pat = cairo_pattern_create_linear (0, 0, width, 0.0);
        cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.1, 0.5, 0.1, 0.4);
        cairo_pattern_add_color_stop_rgba(pat, 0.8, 0.4, 0.4, 0.1, 0.4);
        cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.5, 0.0, 0.0, 0.4);
        cairo_set_source(cri, pat);

        int c = (height) * 0.5 ;
        int ci = c-2;

        int i = 1;
        int j = 1;
        for(;i<width;) {
            for(;j<height;) {
                cairo_rectangle(cri,i,j,2,ci);
                cairo_fill(cri);
                j +=c;
            }
            i +=3;
            j = 1;
        }

        cairo_pattern_destroy (pat);
        pat = cairo_pattern_create_linear (0, 0, width, 0.0);
        cairo_pattern_add_color_stop_rgba(pat, 0.0, 0.1, 0.5, 0.1, 1);
        cairo_pattern_add_color_stop_rgba(pat, 0.8, 0.4, 0.4, 0.1, 1);
        cairo_pattern_add_color_stop_rgba(pat, 1.0, 0.5, 0.0, 0.0, 1);
        cairo_set_source(cri, pat);
        i = 1;
        j = 1;
        for(;i<width;) {
            for(;j<height;) {
                cairo_rectangle(cri,i,height+j,2,ci);
                cairo_fill(cri);
                j +=c;
            }
            i +=3;
            j = 1;
        }

        cairo_pattern_destroy (pat);
        cairo_pop_group_to_source (cri);
        cairo_paint (cri);
        cairo_destroy(cri);
    }


    void drawMeterScale(cairo_t* const cr, int y0, int rect_width, int rect_height)
    {
        double x0      = 0;

        int  db_points[] = { -50, -40, -30, -20, -15, -10, -6, -3, 0, 3 };
        char  buf[32];

        cairo_set_font_size (cr, (float)rect_height * 0.5);
        theme.setCairoColour(cr, theme.idColourForground);

        for (unsigned int i = 0; i < sizeof (db_points)/sizeof (db_points[0]); ++i)
        {
            float fraction = logMeter(db_points[i]);
            //cairo_set_source_rgb (cr,0.32 + 0.22*i/2,0.5 +  0.1*i/2, 0.1);

            cairo_move_to (cr, x0+(rect_width * fraction),y0+rect_height*0.1);
            cairo_line_to (cr, x0+(rect_width * fraction) ,y0+rect_height*0.6);
            if (i<6)
            {
                snprintf (buf, sizeof (buf), "%d", db_points[i]);
                cairo_move_to (cr, x0+(rect_width * fraction)+3,y0+rect_height);
            }
            else
            {
                snprintf (buf, sizeof (buf), " %d", db_points[i]);
                cairo_move_to (cr, x0+(rect_width * fraction)+3,y0+rect_height );
            }
            cairo_show_text (cr, buf);
        }

        theme.setCairoColour(cr, theme.idColourForground);
        cairo_set_line_width(cr, 1.5);
        cairo_stroke(cr);
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        cairo_push_group (cr);

        const Size<uint> sz = getSize();
        const int width = sz.getWidth();
        const int height = sz.getHeight() * 0.5;

        double meterstate = logMeter(power2db(value));
        double oldstate = logMeter(old_value);
        cairo_set_source_surface (cr, image, 0, height * 0.5);
        cairo_rectangle(cr,0, height * 0.5, width, height * 0.5);
        cairo_fill(cr);
        cairo_set_source_surface (cr, image, 0, -height);
        cairo_rectangle(cr, 0,height * 0.5, width*meterstate, height * 0.5);
        cairo_fill(cr);

        cairo_rectangle(cr,(width*oldstate)-3, height * 0.5, 3, height * 0.5);
        cairo_fill(cr);
        drawMeterScale(cr, height, width, height * 0.5);
        theme.boxShadowInset(cr, width, height*2);
        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

    void onResize(const ResizeEvent& ev) override
    {
        cairo_surface_destroy(image);
        image = nullptr;
        drawMeterImage(ev.size.getWidth(), ev.size.getHeight() * 0.5);
    }

private:
    cairo_surface_t* image;
    CairoColourTheme &theme;
    float value;
    float old_value;
    float std_value;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoPeekMeter)
};

// -----------------------------------------------------------------------

class CairoToolTip : public CairoSubWidget, public Runner
{
public:

    explicit CairoToolTip(SubWidget* const parent_, CairoColourTheme &theme_, const char* lab)
        : CairoSubWidget(parent_),
          parent(parent_),
          theme(theme_),
          label(lab)
          {
            init();
          }

    explicit CairoToolTip(TopLevelWidget* const parent_, CairoColourTheme &theme_, const char* lab)
        : CairoSubWidget(parent_),
          parent(parent_),
          theme(theme_),
          label(lab)
          {
            init();
          }

    ~CairoToolTip() {if (isRunnerActive()) stopRunner();}

    void setLabel(const char* lab)
    {
        label = lab;
        state.store(false, std::memory_order_release);
        if (!isRunnerActive()) {
            if (!isVisible()) show();
            startRunner(2500);
        }
        repaint();
    }
    
    void unset()
    {
        if (isVisible()) hide();
        parent->repaint();
    }

protected:
    void init()
    {
        hide();
        state.store(false, std::memory_order_release);
    }

    void onCairoDisplay(const CairoGraphicsContext& context) override
    {
        cairo_t* const cr = context.handle;
        cairo_push_group (cr);

        const Size<uint> sz = getSize();
        const int w = sz.getWidth();
        const int h = sz.getHeight();
        theme.setCairoColour(cr, theme.idColourBackground);
        
        cairo_rectangle(cr, 0, 0, w, h);
        cairo_fill_preserve(cr);
        theme.setCairoColour(cr, theme.idColourFrame);
        cairo_stroke(cr);
        cairo_text_extents_t extents;
        theme.setCairoColour(cr, theme.idColourForground);
        cairo_set_font_size (cr, h * 0.24);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
                                   CAIRO_FONT_WEIGHT_BOLD);
        cairo_text_extents(cr, label , &extents);

        cairo_move_to (cr, (w-extents.width)*0.5, (h+extents.height)*0.45);
        cairo_show_text(cr, label);
        cairo_new_path (cr);
        cairo_pop_group_to_source (cr);
        cairo_paint (cr);
    }

    bool run() override
    {
        if (state.load(std::memory_order_acquire)) {
            state.store(false, std::memory_order_release);
            unset();
            return false;
        } else {
            state.store(true, std::memory_order_release);
            return true;
        }
    }

private:
    Widget * const parent;
    CairoColourTheme &theme;
    const char* label;
    std::atomic<bool> state;
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CairoToolTip)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif
