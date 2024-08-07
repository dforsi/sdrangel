/*  patchpanel.c

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2013 Warren Pratt, NR0V
Copyright (C) 2024 Edouard Griffiths, F4EXB Adapted to SDRangel

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

The author can be reached by email at

warren@wpratt.com

*/

#include "comm.hpp"
#include "patchpanel.hpp"
#include "RXA.hpp"
#include "TXA.hpp"

namespace WDSP {

PANEL* PANEL::create_panel (int run, int size, float* in, float* out, float gain1, float gain2I, float gain2Q, int inselect, int copy)
{
    PANEL* a = new PANEL;
    a->run = run;
    a->size = size;
    a->in = in;
    a->out = out;
    a->gain1 = gain1;
    a->gain2I = gain2I;
    a->gain2Q = gain2Q;
    a->inselect = inselect;
    a->copy = copy;
    return a;
}

void PANEL::destroy_panel (PANEL *a)
{
    delete (a);
}

void PANEL::flush_panel (PANEL *)
{

}

void PANEL::xpanel (PANEL *a)
{
    int i;
    float I, Q;
    float gainI = a->gain1 * a->gain2I;
    float gainQ = a->gain1 * a->gain2Q;
    // inselect is either 0(neither), 1(Q), 2(I), or 3(both)
    switch (a->copy)
    {
    case 0: // no copy
        for (i = 0; i < a->size; i++)
        {
            I = a->in[2 * i + 0] * (a->inselect >> 1);
            Q = a->in[2 * i + 1] * (a->inselect &  1);
            a->out[2 * i + 0] = gainI * I;
            a->out[2 * i + 1] = gainQ * Q;
        }
        break;
    case 1: // copy I to Q (then Q == I)
        for (i = 0; i < a->size; i++)
        {
            I = a->in[2 * i + 0] * (a->inselect >> 1);
            Q = I;
            a->out[2 * i + 0] = gainI * I;
            a->out[2 * i + 1] = gainQ * Q;
        }
        break;
    case 2: // copy Q to I (then I == Q)
        for (i = 0; i < a->size; i++)
        {
            Q = a->in[2 * i + 1] * (a->inselect &  1);
            I = Q;
            a->out[2 * i + 0] = gainI * I;
            a->out[2 * i + 1] = gainQ * Q;
        }
        break;
    case 3: // reverse (I=>Q and Q=>I)
        for (i = 0; i < a->size; i++)
        {
            Q = a->in[2 * i + 0] * (a->inselect >> 1);
            I = a->in[2 * i + 1] * (a->inselect &  1);
            a->out[2 * i + 0] = gainI * I;
            a->out[2 * i + 1] = gainQ * Q;
        }
        break;
    }
}

void PANEL::setBuffers_panel (PANEL *a, float* in, float* out)
{
    a->in = in;
    a->out = out;
}

void PANEL::setSamplerate_panel (PANEL *, int)
{

}

void PANEL::setSize_panel (PANEL *a, int size)
{
    a->size = size;
}

/********************************************************************************************************
*                                                                                                       *
*                                           RXA Properties                                              *
*                                                                                                       *
********************************************************************************************************/

void PANEL::SetPanelRun (RXA& rxa, int run)
{
    rxa.csDSP.lock();
    rxa.panel.p->run = run;
    rxa.csDSP.unlock();
}

void PANEL::SetPanelSelect (RXA& rxa, int select)
{
    rxa.csDSP.lock();
    rxa.panel.p->inselect = select;
    rxa.csDSP.unlock();
}

void PANEL::SetPanelGain1 (RXA& rxa, float gain)
{
    rxa.csDSP.lock();
    rxa.panel.p->gain1 = gain;
    rxa.csDSP.unlock();
}

void PANEL::SetPanelGain2 (RXA& rxa, float gainI, float gainQ)
{
    rxa.csDSP.lock();
    rxa.panel.p->gain2I = gainI;
    rxa.panel.p->gain2Q = gainQ;
    rxa.csDSP.unlock();
}

void PANEL::SetPanelPan (RXA& rxa, float pan)
{
    float gain1, gain2;
    rxa.csDSP.lock();
    if (pan <= 0.5)
    {
        gain1 = 1.0;
        gain2 = sin (pan * PI);
    }
    else
    {
        gain1 = sin (pan * PI);
        gain2 = 1.0;
    }
    rxa.panel.p->gain2I = gain1;
    rxa.panel.p->gain2Q = gain2;
    rxa.csDSP.unlock();
}

void PANEL::SetPanelCopy (RXA& rxa, int copy)
{
    rxa.csDSP.lock();
    rxa.panel.p->copy = copy;
    rxa.csDSP.unlock();
}

void PANEL::SetPanelBinaural (RXA& rxa, int bin)
{
    rxa.csDSP.lock();
    rxa.panel.p->copy = 1 - bin;
    rxa.csDSP.unlock();
}

/********************************************************************************************************
*                                                                                                       *
*                                           TXA Properties                                              *
*                                                                                                       *
********************************************************************************************************/

void PANEL::SetPanelRun (TXA& txa, int run)
{
    txa.csDSP.lock();
    txa.panel.p->run = run;
    txa.csDSP.unlock();
}

void PANEL::SetPanelGain1 (TXA& txa, float gain)
{
    txa.csDSP.lock();
    txa.panel.p->gain1 = gain;
    //print_message ("micgainset.txt", "Set MIC Gain to", (int)(100.0 * gain), 0, 0);
    txa.csDSP.unlock();
}

void PANEL::SetPanelSelect (TXA& txa, int select)
{
    txa.csDSP.lock();
    if (select == 1)
        txa.panel.p->copy = 3;
    else
        txa.panel.p->copy = 0;
    txa.panel.p->inselect = select;
    txa.csDSP.unlock();
}

} // namespace WDSP
