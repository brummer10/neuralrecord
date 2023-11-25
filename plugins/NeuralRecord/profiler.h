/*
 * Copyright (C) 2013 Hermann Meyer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * --------------------------------------------------------------------------
 */

#pragma once

#ifndef PROFILER_H
#define PROFILER_H

#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>

#include <iomanip>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cstring>

#include <sndfile.hh>

#include <libgen.h>
#include <stdio.h>

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <fstream>
#include <functional>

#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>


namespace profiler {


struct Freq
{
    int   p;
    int   f;
    float xa;
    float ya;
    float x1;
    float y1;
    float x2;
    float y2;
};


struct MTDM
{
    double  _del;
    double  _err;
    float   _wlp;
    int     _cnt;
    int     _inv;

    struct Freq _freq [13];
};

class Profil;

class ProfilWorker {
private:
    std::atomic<bool> _execute;
    std::thread _thd;
    std::mutex m;

public:
    ProfilWorker();
    ~ProfilWorker();
    void stop();
    void start(Profil *pt);
    bool is_running() const noexcept;
    std::condition_variable cv;
};

class Profil {
private:
    SNDFILE *       recfile;
    SNDFILE *       playfile;
    std::string     inputfile;
    std::string     outputfile;
    struct MTDM     *mtdm;
    ProfilWorker    worker;
    int             fSamplingFreq;
    int             channel;
    float           fcheckbox0;
    float           fcheckbox1;
    float           fbargraph;
    float           fbargraph1;
    float           errors;
    int             reset_errors;
    int             latency;
    int             roundtrip;
    int             measure;
    int             finish;
    int             IOTA;
    int             IOTAP;
    int             iA;
    int             savesize;
    int             filesize;
    int             inputsize;
    float           *fRec0;
    float           *fRec1;
    float           *tape;
    float           *tape1;
    volatile bool   keep_stream;
    bool            mem_allocated;
    bool            err;
    bool            time_match;
    float           fConst0;
    float           fConst1;
    float           fConst2;
    float           nf;
    float           fRecb0[2];
    int             iRecb1[2];
    float           fRecb2[2];
    float           fRecb0r[2];
    int             iRecb1r[2];
    float           fRecb2r[2];
    int             iRef;
    int             iRefSet;
    float           fRef;

    void        mem_alloc();
    void        mem_free();
    void        clear_state_f();
    int         activate(bool start);
    void        init(unsigned int samplingFreq);
    void        compute(int count, const float *input0, float *output0);
    void        save_to_wave(SNDFILE * sf, float *tape, int lSize);
    SNDFILE     *open_stream(std::string fname);
    void        close_stream(SNDFILE **sf);
    void        disc_stream();
    void        connect(uint32_t port, float data);
    void        normalize();
    inline int  load_from_wave(std::string fname);
    inline void  convert_to_wave(std::string fname, std::string oname);
    inline std::string get_path(); 
    inline std::string get_ffilename(); 
    inline std::string get_ifilename(); 
    std::function<void(const uint32_t, float) > setOutputParameterValue;
    std::function<void(const uint32_t, float) > requestParameterValueChange;

public:
    static void run_thread(void* p);
    static void clear_state(Profil*);
    static int  activate_plugin(bool start, Profil*);
    static void set_samplerate(unsigned int samplingFreq, Profil*);
    static void mono_audio(int count, const float *input0, float *output0, Profil*);
    static void delete_instance(Profil *p);
    static void connect_ports(uint32_t port, float data, Profil *p);
    Profil(int channel_, std::function<void(const uint32_t , float) > setOutputParameterValue_,
                         std::function<void(const uint32_t , float) > requestParameterValueChange_);
    ~Profil();
};


} // end namespace profiler

#endif  // #ifndef PROFILER_H
