/*
* Author: Christian Huitema
* Copyright (c) 2017, Private Octopus, Inc.
* All rights reserved.
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL Private Octopus, Inc. BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "DnsStats.h"
#include "CaptureTest.h"
#include "pcap_reader.h"

#ifdef _WINDOWS
#ifndef _WINDOWS64
static char const * pcap_input_test = "..\\data\\tiny-capture.pcap";
static char const * pcap_test_output = "..\\data\\tiny-capture-tcp.csv";
#else
static char const * pcap_input_test = "..\\..\\data\\tiny-capture.pcap";
static char const * pcap_test_output = "..\\..\\data\\tiny-capture-tcp.csv";
#endif
static char const * pcap_test_debug = "tiny-capture-out.csv";
#else
static char const * pcap_input_test = "data/tiny-capture.pcap";
static char const * pcap_test_output = "data/tiny-capture-tcp.csv";
static char const * pcap_test_debug = "tiny-capture-out.csv";
#endif

CaptureTest::CaptureTest()
{
}


CaptureTest::~CaptureTest()
{
}

bool CaptureTest::DoTest()
{
    DnsStats capture;
    CaptureSummary cs;
    char const * list[1] = { pcap_input_test };
    bool ret = capture.LoadPcapFiles(1, list);

    if (ret)
    {
        ret = capture.ExportToCaptureSummary(&cs);

        if (ret)
        {
            CaptureSummary tcs;

            ret = tcs.Load(pcap_test_output);

            if (ret)
            {
                cs.Sort();
                tcs.Sort();

                ret = cs.Compare(&tcs);

                if (!ret)
                {
                    cs.Save(pcap_test_debug);
                }
            }
        }
    }

    return ret;
}
