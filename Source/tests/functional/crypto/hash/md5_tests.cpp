//
//  md5_test.cpp
//  OpenPGP
//
//  Created by Yanfeng Zhang on 10/28/16.
//
//  The MIT License
// 
//  Copyright (c) 2019 Proton Technologies AG
// 
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.



#import "utils_test.h"
#include <hash/MD5.h>

namespace tests {
    namespace hash_tests {
        // Test vectors from <http://www.nsrl.nist.gov/testdata/NSRLvectors.zip>
        const std::vector<std::string> MD5_BYTES = {
            "",
            "24",
            "70f0",
            "0e1ef0",
            "0838788f",
            "103e08fc0f",
            "e7c71e07ef03",
            "e0fb71f8f9c1fc",
            "ff7c603c1f80e207",
            "f03fc86081fe01f87f",
            "9fc7f81fc1e3c7c73f00",
            "007fbfdfc0fe027e00f87f",
            "0101c01e03f830080ff3f9ff",
            "c403fc0ff801c00ff0061041ff",
            "ff078047fc1fc060301fe03c03ff",
            "803f843effc03f0f007fc01fe7fc00",
            "ffe07f018181ff81ff003e00207f800f",
            "003e00701fe00ffaffc83ff3fe00ff80ff",
            "7fefc01e7cffe01ffe001ff008ffc07ff000",
            "e00f80070c01ffe003f02ff83fef007801fe00",
            "e7001000f8180ff0ff00ff803fc3fef00ffc01ff",
            "001ff80ffc00fc00ff87c00f807bff000f0201ffc0",
            "000ff003c7f83e03ff8003ff8007ff0fff1f83ff801f",
            "ffc01f803f9ff8783e7ff8003e20043f807ffc001ffe00",
            "3f0780e007e000fc7fc0c00f8ff0800e0e03ffbffc01ffe0",
            "fffc11fce00e1fff87801fe0fffdffc003ffc00f0007f001ff",
            "f007c1fe00f801e780ff803f1f7f8c001c000ff807fc00fffc00",
            "000ff83fc060007ff8ff0003f03c07c07fe03ff801007e03ffc000",
            "000ff803001fff000ffe003f0003ffe007c0ff003c7ff001fff83fff",
            "0001e0e01ffe0003fc000fffe00fff000e007ffc0ffe0078003fff00ff",
            "8041ffc3fe001e000fffe0ff800fe0007ff7ff01fe01ffdfff0001ffe000",
            "f80700ffc07fbe000fff0003e3f0fff0001f81ff800fff802003f00380fffc",
            "003820007ff001fffecffe07ffc0007ff81f0000c000c00fff3e0fc00fff8000",
            "1ff807fff803e001fffc3ff800381f003fdc01c004ffff000ffc08020001f03fff",
            "8007860003ffe0003ff8000f800ff80fffe0001f80007ff8c00ffff07c0407ff0000",
            "01ff00183e0f0007ffc000f01ffe0780600ff8003ffe381fc0003f81fffc1fe0003fff",
            "f03fffc0007ff0003fff0fe0070ffc7e03fff0fc0f9fc03fffcfff0000ffc000e701fff8",
            "0001ff8020007fe0007e07fff8c7f8fff00ffe0000e00fe0001fff87ff0001f0007fc1ffff",
            "00007fffc001fe7e01fffefff07fffcff807fe000fffc007fffc003e0007fc007fc007800fff",
            "ffff03ff07f8ffff80007ffefffe0003fff81fff3ff81fff001fff0fc07ff001ffe0001fff0000",
            "ffff0000fffc00030ffff001f8000fe1ffff03e03f1fff80007c0001ffc0017ffe000e07ffe0ffff",
            "c0003ffe03fc0c000401ffe1e003ffe03001ff00003c1e018001ff00403ffe003fff807c01ff80007f",
            "3fa0000fff81ffc00ff07ff8000fc0007fe001e00004ff001ffe0001ff8007fffe003fffc003ff80003f",
            "f01fff01ff80ffc08007f00003ff80001801fffc00fffc03ffff007fc003ffc7ffc003f0ff80003ffe0000",
            "07f1bfffe000780007e0008003f03ff700003800fe00f80ffe0000803fffc1fffc00ffff8ff0001ffff00fff",
            "001c0007fffc005e3fff00003cffffc03fff81e070001ffc0003ff00007fffc01f8c0ffff0ff8007e01001ffff",
            "c00007ff807fff8001803fffcfc0fe00ffc01ffc01fff800fffe0ffff0060000c03fff8078fffc000ffff0000fff",
            "ffe007fff8007ff01fff8001fff81ff80103ffe00003e0780fff000ffc1ff8000fffe01f0007fffc001f03fff7ffff",
            "c0f80003fe003ffff00003fc0fff8000e3fff83ffe000073e0fffc07ffc3fffe030000700003fff80fffe0001ffff800",
            "fff00fc7fffc003ffe00003fff803f80003fffc0007001ffc18003ffff800061fffe03fd803fffe001c1ffff80000ffe00",
            "fffc0003fff00ff80007df8ffff80001fffe008000ff801ff000011c00003ff8003fffeffffe01c3808001ffffc00007ffff",
            "ffffc001ffc1ffff87ffff003f00001ffc0001ff801fc01fff0000ff801ffff87ff83fffc1ffffe001c03ff7fffefc00003fff",
            "00ff81ffe003f80e0000fff81ffffe0000ff800007fff801ffe0000ff001fe003ff07fe0007fffe01ffffc01ffe001800007ffff",
            "000ffff00000e00ff80000ffff8003ffe1ffff3ff80fffc7e0001fff003ffe0ffff00300c0001ffffc3fffe03ffff81ff0001fffc0",
            "0180001f01ffff830001fc007fe00e7ffe00003800ff00003fff8383ffc0007fff801ffff01ffffc00037fff81c00007ff83ffff0000",
            "ff800dffe003fff000fffc00f001f807fff80f800fffff00ffff87ffe1fffc678c7ffe0003ff3ffc0701ffffe00001ffffc00c400fffff",
            "00001ffffe001f00001fffff07ffffc007ffe000020000ff00780000e00008001fffff0003f81f00000fffc00001ffffe1f800003f800fff",
            "000ff800fc0003ffff00003ff001ffffe07ff800f80fffff80000ffffc0fffe00000ffc3fff007ffff0038f800201ffe3ffe00fe007fffc000",
            "003f00e0000ffffc7ffffc00007e0000fffe1ff0001ff0001fff87f0003fc00fff87ff003f81fffff7ffe0ffe03f9fff0007007ffc03fff00000",
            "e03ffff0ff803e0003ffe0000ffc0007fff800007f80000ff801ff7ffff0003ffffe7fffe000ffc3ffff0000f000007fff003ffff00001c003ffff",
            "0003c001ffdffdff9ffe1fffff003ffffe00007fcffff01ffffe07f000ffffe000010007ff801fe00000fffe03ffff8003f00ffffe00001ffff80000",
            "001ffffbfffe0007fff00000ffff00000ff3fffe007800003e00003ffff8001fffff800003ffff0007ffee001ffc007800001fff07fffe03ffffe00000",
            "007ffffe00003ffc03fffc1ffff07fd803f000fdfc380008001000e006007ffe00000fff80003f03fffefffff9fff80007fffc01ffc00003ffffe003ffff",
            "fff00fffff000600fffff007ffe0040003000003f0ffff0003fffbffc3fff007ffffc7007f800003fff8001fe1fff863fc003fc09ffff800007fff1ffffc00",
            "003ffffc000fc7800002001e0000607f03fe00001fff801ff80000ffff800003ffc0007fffc07fe003fc00fff7ffff00001ff00003ffffe1ffff800ff800001f",
            "0001fe000383f3ffff8007fffc3ffffc03ff8000060000780007ffff8007fc01f80007ffffc000380007fffe3ffff83fffcf3ffc007fff001fff80003003ffff00",
            "f8003800003e3f00003ffff00200000fffff808003ffc00004000fc03ffffe00003ffffe003ffff80030007bff000003fffc3fe1ff8000701fffc007fc001ffff000",
            "0003f8180000703ffff80000ffcfffffc003fffe00100000fe03fff800007e00007f8fffc000007fffe0003c07c000007fff01fff801ff80000ffff9e0003fffe00000",
            "fffe003fc01ffff07ff80001fff81ffffe0000fffff8007fff803fffff007ffff8000c00000ffe7e003fe0187ffe00003800003ffffe000003fcffe1fe1ffffe000007ff",
            "000007fffe000007fe00003fe0007fffc000007ffffc00fe0003ffe0001f0ffc001fff800007fffff000fffff000001ffff801ffe01fffff001f8007f00001fff80001ffff",
            "00003fffff03fe000007c000007ffc0ff000001ffffe000007c00000fffe00003ffffc01ff7ffc001ff8001fff07ffffe0007ffffc01fffff00001fff8001e00007ffc003fff",
            "fe3fff83fffe0007fffff0003e0000fffffc00403ffe000003f00000703ff80fffffe01f800003c3fffff00001fff00f80000fe0fffffef00001ffc000007ff000007ffee00000",
            "000003fff001fc0000ffff00007fffff8007ff8fff80000ffff000003c0003c0fffffe01ffff800c7ffff800001ff000007f800000800000fffff01fffe000fffffe1fff1fc00000",
            "fffffe07ffc000063f9ff007fff03ffe1fffff81ffffc0000200fe00040007000001fffffe000007fffe001ffe0000ffffe007f800fffffc003ff3ffffc0007fffe0000ffffc07ffff",
            "fff000007e001e03ffff000073fff000000fffdfffffdffc0007fe07fffe00001fdfeffff03ffffc000007fffff000007fe007ff8000007fe003fffff9ffe000003fe3fffffc000003ff",
            "0003ff00003fff8001f0000ffe0000060003fffffc03fffff78000007fc00fffe3fe0f00007fff007ff80000ffffee007e01c0001fe00007fffff80000e1fffc3fe7fffff83ffffc001fff",
            "00000ffff80000fffffc001fe007ffff0001ffdfff80003ffffc00000ffc07ff0000ff800003fffff00007fffff000fffe1fffffe03ffffe0000600000ffff7ffff00003ffffc0070001ffff",
            "0000207ffe0f83ffff8003ff000000ffffe0001fffffe0003ffe7ffff0001fffffe00000ffff87ffc00017fdff9ffffbffffe00003e00007ff9fffff80007fffff0001ffffc0ffffc01000001f",
            "000007ffc000ffe00007ff800380000ff800007ffffe00001800fff02001fffe0000600ff0e003fffe003e1ffffc0003ff800000fff8000100000ff3fffc0003ffffe1ffffc1f00000ffffff0000",
            "fffff0000007fffc007f87ffff0000007fffc07fff800003f0ff3fff803007ffff1f8e007fffffc001fffc07f800007ffffc003ff000f8000007ff00000e000fff80007fc001ff8ff8000701ffffff",
            "ff803fff3ffe0000ffffff9ffff83ffff800000ff8000003fe007fffff000fff01fff00fffe0207ffffcff01f80007ffe0007ff8000fff8000007fe0003ff801fe0007fff000007fffffc00001ffffff",
            "007fffe00001fffff800003ffffc007ffe000003fffff003ffe0007f80000fff3ff800007fffff0007801f83f800000ffe3fffc03ffffe1fe00007c003fff00fc00003ffff8000007f800000ffff800000",
            "fe0000200004000fffffc001fff83fc00000ffffc000ffffff80003ff8007ffffe7ff8007fff8007ffc0000ffff8007fffc000ffffc03fffffe00fffffe0e01fff8000007fffc071fffffc0001fffff80000",
            "ffffe0000ffff000003fffffc000ffff00000fffffe00001ff00001fffe03ffc0003e01ff01ff800003fffffc00ffe0000200000fffc000ffffe3fffff00fff0000080001f03e001fffa003fe000007000000f",
            "fdffc0002001fe003ff80003ff000003f8ffcfc3fffffc0003fffffc0000783ffff001ffe00fffff000007fffffcfffff80001ff800007fffffc00001c0001ffff07f800001ffffff00001fe007ffff01ffc0000",
            "0000003fff000007fffffc000001e00fff83fc01fffff00fff0000003fffffc01fffffe0002000003fffff0000fffc03fffff0001ffffc000003ffffc07f8000ffffff000f0fffffe00000fff80000fffe00000fff",
            "fffe03800003ffffc03fffff0003fffff8000001ffffcffc0000e0eff8000fffe3f8003fffff803fbffe0000fffc000001ff0000cfc001fc00007fffffc000107ffffcfe000007c0ffffff8fff00001f9e000001ffff",
            "007fffe00001ffffc3ff800103fc000000fc01fffff87fe7f000007fc03fffffc000001fff800001ffe000007000001c7ffff81ffc000007efe0ffffc1fffc000001ffffffa007ff001e001ffc0000380018c000007fff",
            "000ffff8000007ff00fc000003fffc0007ffffe00000fffc0fff00000ffffe0f8007ff03fffff9fffe000003f8000007e00000c0001ffff07fffffc007fffffc00003fffffe000001ffff81ffe00003fffffe03f06000000",
            "fff00008000feffffffc00007ffff0007ffff800ffff81ffffe0ffffff000000800003ff803ffffc00001fffc00ffffe00000073f01ffe00ffc03fff003fff83fffe01fffff7ffff8000003f00001fe3fffff0000ffff00000",
            "00007ffc007fe0000fffe001f8003fff000078007fe000001f0007fffff8f9f001fff807c00ffff80007f87ffe00000fffe3f00007fffffc031c00007fe000fffffc00000ff3ffe000000ffff9000010003ffffcf87fff000000",
            "0003ffffc07fffffc00003ffffff00000ffff01ffff00007ffffefff81f7fffe0007fff000001fffc00f80000ffffc0000ffffffc003ffe3fffffe001fffff0000ffffff0ffff1f8000001ffffff801ffffe000800007fffff8000",
            "1fe0007c1fc007ffc007fffffe003c000000ffff800007ffff001ff8ffc000ff81ff01fffe00787ffff000018000001fff00001ffff0001fffffe0003c00001fffff8003ffe001fffff9fff800007c0000fe0000ffffff00000fffff",
            "fc0001ff00000c00ffffe3fffff0800e0e00000ffe0003ffc000007fffffe0c0000007e0ffff039fffffc1c00003ffffc3fffffcffffc00001fc000ffc0000007fffff03fffffc0ffffe000003803fffff0000fffff80003ffff800000",
            "ffff80fffff80000fc0003fff8000fffff00030000007ffff0003ffff00001fc010003ff801fffe3fffff8001ffffff801ffdffffbffc000003ffff8000080c7fffff80fff00601fffe00001fffffe0ffffffc000000f00603fffffe0000",
            "ff000ffffc000ffffffc07fffc0000f0000080007ffe00000ffffffc3f00ffffff001ffffff0001fffffe0001fffffc3ff000001fffff000000fffe007fc000000fe0007fffff800003f00000f80003fffc00011ffef0007007ffffc000000",
            "fe00007ff7ffff00000fffffe001ffe0000003ffe000fffe0001fff7fff8000fff000000380007fff807fffc001fffff0fc1ffffc000ffff0ffff001fff80001ffff8000000ff8003ffffe3ffffff00000380fc3ffffff1fffc03fffffe00000",
            "fffff0007fc007ffff81ffc00001ffffffc000001ffffe03c0000ffffffc0003ffffff83ffc00007f000001f8000003fffffe7ff0007fffffc00001ffff80003f000fffc001fffffe003fff00001ffffff8000000ffffff810001e03ffffff8000",
            "0001fffe0000007ffffff000001fff8007ffffff800001fffc03ffff9ffffe000800000600000081ffffc00007f800ffffff000000fffff8003ffffff83ff80000007fffc07fffffc0fffffe000001fff8000003ffc1fff000000307f801fffe0000",
            "f8000001ffff80000fffff8fff001fff0fffc00000fffffc000ffff0007000003fffc000007c00007e000ffc000000ffff8000000ffffffc38000003f00031f01fffffc007ffffe01ffffff3fe000000ffffc0001fe7ffe1ffffdf0000001fff000000",
            "3ffffff800000060000fffffe007ffffff00003ffffff01fffff8000700000010000003ffffe0000001ff8fcc00ffff8003fffc0ffff800003fffff8003ffffc00000f81ffc003ffc03fffff8003fffe00fffffe00001c0000003ffffff8007fffc00000",
            "0000000ffffe0fffff87ffffff0080000fffc00003f01ff7e00000700001ffffff8001fe07f00001fffc0000040001fffe07fffffe0007c00000ffffff87f003fffc00001ff80001ffffc000003fffc000007f8ffff80000007fffe0060e00000fffff8000",
            "03fffffde000001ffff801fffffbffffe001f0f00000ffffff8000007fffffe01ffffff00180ffffffe000007ffff0ffffc0000007fe0000001e001fffffe01fffe001ffc0003fffe000000ff000ffff7fc01ff83fffffc000007fffe0fffc0000ff0fffffff",
            "07fffc03ffffffdfffff87ff1800038001ff0000001fff00003fffffc01fe03ffffffc000001fff800003ffffff8000007e00007fff9ffe0003fe0007feff0000781fffc000000ffe00030000000fffff0000003fffc7f07f803ffffff003ffc000001ffc00000",
            "007ffc000003fff8000061fe7ffffe00001ffffc3fff8001ffffffe000ffffff801ff8007ffffff8000007ffffe0000007ffffff8000ff800ffffffc00007ffffe0000003000007f800007fffff0000003ffc00fffff803fff8003fffffe03ffffff7ffc1ff00000",
            "1ff000007ffffe02000003ffffffd807ffffe001ffff80000007c0000fffc07ff00007ffff800007f000007ffc03ffffffc00001fffff9fffe00001fffc0000003fe3fffff0007fe000003c0003ff8001003fc000fffc0007fffe000fff000007fffe000000fffffff",
            "fffffff8000060000000fffffc03fffc00003c003fe07ff80007fff80ff800007ffffffc007fc20003fffffe0001fffffff003fffff01807c0000fffc000007fffff87e0000007001f800407ffe000001fff81ff800003fffc000007ffffffc000001f8001ffff000000",
            "000ffc1ff8000ffffff807fff1fc001ffffff0000fffdfffffff000003ffffff0001ffffffc0100ff0000000fc001f00070001f000001fe00000307c3fffe000fffc07fffc003ffffff8ffffc1fc1ffffff80001fffc00000fffffff0000fff80c000007ffff0000007fff",
            "ffff80ffff0000007fffff001ffc0006000ff80000018000007fffffe03ffffffc0060000000fe000007fffff07ffffff800008000000fffffffbfffffc007fffe00001c001ffc070001ffff00000080001fff038000003ffffff80007ffffff80001fffffe01fffffc00000",
            "fffffff80000007e0000001fff8007ffffff8000000fffffc3fff00000047fc07ff0003fff80007fe00003ffc00007ff00000fff800000078000000fffffff01ffffffc003c0000003ffffe0000fffffc00003fffe0003fff800000fffffc001ffe00000fffffc00001fffffff",
            "fff0003ffc0000ffffffe01fc3fe0007fff8000ff001fffff00000ffc00fffff800000fffff3ff80000080083800000ffff0001ffffffc000f800070000031fffffe3ffff80000003c3ff00fffff0003fffbffffff000ffffffe000000f0000000fffffc007ffff00001fffffe00",
            "fffff00ff83fffffe00003fffe00003fff80ffffff000000fffff8fffff0000ff1ffff0000000ffffc0000001ff000001ff003ffffffe1ffe000001fffc1fe000007fffc0000001ffe3fc0000001fffc00001fffff0fe00001fc00fe0000007fe0001fffffe07f000ff000fffe0000",
            "007fffc007ffffff8007fffffe0000007e0000000fff801ffffe07fffff003c7fffffe0000007ffe00001ffffe000000fffc001fffc000003fff001e000003ffffff8000007ffff803fffc0001fffffe000fff020007fffffe000000fe01fffff7ffff19ffff000007ffc1ff000007ff",
            "00000040000007fffff81fffffc0003efffff00000007ffffe000000ff8000003ff1ffffffe0000001ffffff00001ffff80007fffff8001fffc1ffffffe001ffffffe0000007ffffffcfffe0003fe0ffffc00007ffffe001fffc3f0001fffffe0001ff0ffffffc000001ffff8000000fff",
            "fffff0ffffffc003800001000003fffffff1ffffffe007fc000003fff00000007e00000007003ffffc000fc7ffff000007ffffc0000003fffc0000ffe00000007ff00000fffffffdff00ffe0ffffe007fffff87ffffe18000001f0001ffffe01c001fffffff80001feffffff80000007ffff",
            "fffff0001fffff00003ffff000ffff0007fffff803ffffe7ffffff81000001ff00003ffffff8000000f007ffc00ff0003fffc0007ff800fffc00001fff801ffc000001ffff00007ffffffe00000fff8000000ffffffc000000fffffc000fff80003ffffe00003fe00fffff000001fff0000000",
            "ffc0000003fffffc00fffffc0000007fffff0000001fe0000fffc0f000007fffffe000201fffffff0000001f80000007fff1ffffffc000001ffffff0003ffff8003ffffffe01fffffe7f9e001ffffc007fe07fffffe0007ffffe000001fffffff801ffc003000ffff800000ff00fff0000000fff",
            "0003ffffffcffff87f8ffffffc01fffffc00001fffffff80000001ffffe1fff0000000fffffff80380003f80000fffffffc00000027ffff803ffc000003fff80000001ffffe0000003800000ffe07ffffffc000001fffffc000000ffff800007fe000007fff000001f8000003e1fffffff9fffffff",
            "fffffe0003ffffff8001ffffffa03ffff8007f03ffffc0000fffc3fff80003ffffffc07ff01fe00fffffc0001ffe0fffffe00007fffffc0000fc003ffffff00000003ffc0000000fffc40000ffc00003ffffff800003fc0ffffff0000003ffffc007fffff80c3ffff0001fff80000001fffe00003fff",
            "0000001fffc3ffff8000003ffffffe0000000fe0007fffe00ffe00ffffffe003fff80000003fe0000001ffffe7ffffffe0000007ffffc0001fe0000001ffff000003ffffffe000001fe003ffff00000007fff03f8000000ffffffe0000ffffff00003fffff800ffffe01fffffff83fffffc00000ffffff",
            "ffffff8000fffffff000001f003ffffe0ff01c00ffffe0000fc01fffc0000001ff80f7fff800003fffc0000001fff00003e3fc0007f800003ffffffe00001f00000018003ffffff80fe0000000600007fffffe0060fffffff800003fff8000003ffffff000000ff000fffff1ff003fffffff01ffe0000000",
            "fffffffc000000fffff001fffff80000ffffffe7fff801f87fffff80003ffffc000001ffffe0003fc000007fffff00000fffffffc0000ffff1fffffff8000ffffffc000007ffffff80fffff807f00000001fffffffc000ffffffc0000effffffc0000003fff8000003ff80000000e000000ff800003fffffff",
            "3f0003c01f0000000ff00007ffffef00fe007ffe00003ff0003fc0000007fc000003ffffff0fffffffc007f80000f800003f9ffffffc00003fffc00003ffffc00000fffc001fffe0000007ffe0070000007ffffe000000fffffe00000ffc0007fff00000007f8003cfff800001ffffe03c00003fffffff800000",
            "30000000fff80000fffc003fffff8000000fcfffcfffffc0ffffff80000001fffffff00000001fff0003fffc00000007ff80007ffffffe0fffc00000007ff0bfffffe00000fff8000001fffff800003e000007ffe00000008000038001fffffff860000000fff0001fffffc7fff040fffffe000007ffdfff800000",
            "ffffff83fff81fff1fffff800fffffe00000003fffffc0f8000078001c0000001fe0000000ffffe03ffffffe000003fffffe0000001ffffc007fff0000001fffff000200003ffffc000000fff01ffeffffc001fffffff0000000fffffe0000000fffc000007f7fc0000001fffffe0fffffffc0000f8000003fffffff",
            "fffffffe000000fff80ffffff0000007fffffbffc00007fc07e0000001ffffe0007ffffff800003ffff80000000fffff00000fc000003ffff0000001fffffe1ffff80000200000003fffbfff9ffffffc3ffffff0000007800000ffffe7fffffff000003fffffff000007ffffe0ffffffe001fffffff80000007fffffff",
            "0000001fffc0000fffc000001fffc0001fc0000003ff80000007ffffffc000000080003ffc00c0000fffff000006003ffc1e001ffffff0003e0ffffff000003ffff00000001fffc00000fffffff800e00000fffffffe00000ffffffe3ffffffc07fe000000c0007ffffffe00fffffffc07ffffe0003fe3ffffc000003fff",
            "0000000fffc0000ff8000000fffc00000ffffffe00000003ff00fffc07fff01ffffe0ffffffdfffffff01ffff00007f8fff8000000ffffc03fffffff8000000fffffff000003fffff00007ffff00003ffff001ffffc001ffffff003ffff81ffffffe1fffffffc000007fe00007fffffe00000003e007ffc003fc0007ffffff",
            "ffffff000003c0000001fffff80000000fffffff00000f0000fffff88000f8000fc0000000e0000000fffffff80ffffffe00001800007fffffff000003ffffff007ffffffc0003c000000ffffffff00007ffff8001ffffffe0000ffffe07fffff800ffffffc0000003e00007fff00ffff00000fffff87fc003c03fffe0000000",
        };
        
        static const std::vector<std::string> MD5_HASHES = {
            "d41d8cd98f00b204e9800998ecf8427e",
            "c3e97dd6e97fb5125688c97f36720cbe",
            "038701ca277a9d4de87bff428dd30a12",
            "bc60c6192e361d99b59d47250668a852",
            "542c3a0ab6b51bc6a88fa7bb567bca3e",
            "e035f9e748a2a09a4fbdcf18c4f58bf1",
            "3b4cc9226a236742d72578c5915b6c3c",
            "35950208a022baac90056636827158ce",
            "84cedff2ed1b78b395cc8651094f4ce3",
            "7badf748f4cb700272a72edfea22e9bf",
            "a1bb6e142739dbdb0925747d95e0a1ad",
            "0cd9b72dfdee8efd2e1515f4c5a62284",
            "ef07c13e75d50578d09052aa21a7cffb",
            "cf3b261af9344bf83b4dd82b30242c78",
            "530710f65fb98fff8eb927e2938cb8c5",
            "4e6d73658b27e19d4bb4500625001e39",
            "c8e5f2f272b1ef88ec62dd0d9d54e902",
            "031cbf1fb05b4ec09f3c93235d0f49ac",
            "8c0e1400df02ba8c4809b705e5f5e114",
            "57ec48278e19f71f54c570a5ab306df7",
            "ecd3dc346a2337b95389a094a031610f",
            "f11d91eae492225cbd82ef356aa96f9f",
            "26bd8b480216c723ce75da98b9bd430c",
            "80999c2d12f623e4f87e0550a8e3523a",
            "00945c1bd739ce389ac24bb93f6f9a85",
            "7ab55f0bd5dca5b17ecaa7fef73ed87b",
            "e3cedd606ad51dd18532abd3079a3e0c",
            "df5ecc6732e22cc25836398a10222e97",
            "863b6d9962ee3761bbb9cd8a8367589e",
            "683c9384e29efe82dd3ac847904c28e8",
            "b3d948e72159ddc9c600d75512c5f115",
            "ce8633a6cf189b07e022147bbbd0f350",
            "8df17372eb32a0afa4fc47837262ff61",
            "62c63ca91890ce6f78a59c0bdb1e7bab",
            "1eda4bb0259a939548ec4ceb39facde4",
            "c4f37a2c450f2a23322513b372e668a5",
            "cab8f06436c5ad45f982490215836f4e",
            "3a43bc720714a2a42a73a76085542f86",
            "03f2f4033b258e6eb1e101f1ed4c24b4",
            "2ceb33cec5ecad4a50f6bd3a831ae77c",
            "dd808f695d28f93562cfcb164bc3cce4",
            "01c6d7a87e94bf685205ec8d7c5196af",
            "ef0e93e8928f8bae1b216da8e661fc9b",
            "c8da55117d7d4b7ee8ddc8dc4ba73aa6",
            "bbfc64583c6d4c2ef4b0358464d4d028",
            "3bb5864481f2e66387419dd1a168aadc",
            "0d725d3a1d3d97d7b5ea8293bbbf32ba",
            "915eb22a15f7673f983672b6c353b6c8",
            "13b51da3e8a1422bfd58b79c4e19de64",
            "e69d6c03102464f22c395f9fa27108de",
            "132fa4cbedaa7bd965b0b5900211be48",
            "e37ff5d9f14249f327a19dd5296e6c7e",
            "4881a65cf107b1d034ff3ecd64ab9cb4",
            "547e92d01c0b699cfdf43f91714cfe2d",
            "aa2b3a055b56845f19109f21d3c783f4",
            "eb1f01cc647ece73b2192537200bb8b9",
            "1db274ef41b1ad71f713df2b05207e1a",
            "d8b4ec343b4310345efc6da9cee8a2ec",
            "082ee3b2be7910f7350368e395a63d90",
            "d247c4070ae1de106bcb438a2dacac23",
            "f8cbc4f3af45befc792679f2b113f1cb",
            "9031006a437019c5dcd987a31731ebd9",
            "a6b62759ee3883258fbdeeb8b56e6283",
            "4933898605b4a1b970b674a2dde92292",
            "f0684ca20de4607232f3e158e81a37f2",
            "c0b3fdecb3bb7b4ff0c936f378ccb027",
            "50652123b5e0e51bb5bc3fdde3c6a750",
            "ed4526ba8226d969f47edbb27b2f1144",
            "80e6f61dff9da8673fa16dbbdb14d03d",
            "1d52744bf1450d7c5cfdf1f0bbf967c1",
            "3438a953124960bcc44611923a8844ee",
            "b2f341296dd7aabbd4fd8e011be68a7d",
            "322dba69658a92e9a9ace4d7177fb97d",
            "b94a434a98efa493fbbc989360671bb9",
            "cd9ce9a01ed810af70999d8ce4c63811",
            "4c639abb75a0ae0f22c3384cb9c68441",
            "fe31ffcced1717988c854c2f3492466e",
            "b56d81337f9bbf0d838df831e9b40216",
            "0be9161adfeb2dd1c3f20338bfb3ec4b",
            "be7b7c9fa1ab09d6578a3f2a82bfafe3",
            "f6bdc04b4611ddf0aa8403bcb04292f7",
            "1c7146a10f3c76b0c1dd4af354b14982",
            "0d3d987f94aee65f84436696bcf33ea4",
            "1a5c9ac3ee859361ad5477ea792506a3",
            "e827d60f27e35d8e5b05af748ba897dd",
            "5b7899bf7a6267d9b3b8c82f241a1d7b",
            "6dc9fe740cf4a4b93cb0953a3c2a6026",
            "27adf814806fd4a51c1ffc84122c5c8a",
            "f74e94ab992c8f27de264993a09ab429",
            "5eee0f1591d10c159763749ec86b9ecb",
            "46898964a3889615d9f7c22a81e0a0e7",
            "8fb58d6770971b0f12e40b31ad65b4a9",
            "eb4ce130268dc13731dcd16ff492d0a9",
            "23532a54e8005860ad5e77f4e3392827",
            "07fedc4dc4891d1a90c501a781a666f2",
            "83e8341035b37dd70a92a6eed5406927",
            "6c9f7b3b25734d58f21f5050642874a5",
            "ef661042e6624f4052ce86d8f233d780",
            "efe794cdfad5cb86656e29854a1f5c92",
            "e5f19a0045481443bae165f03598a9ba",
            "b8fe8691321edbf308a9d60bb817c6af",
            "f31fdd0f1aef106005e6d29b72229fa1",
            "239ed45c3cb734db446adfbbe3dab8a1",
            "2c2303411c7d25617a54106aca18070d",
            "de179c41aca8bcdc388964024948ff8e",
            "ca335b74d59bd50832267d3bf28f81df",
            "dabda7a1cbaa8ea5104c57c8950b703a",
            "076352a22ecea5ebc876812f62c1cb8d",
            "ee0a2bdec712a9413623d8a920714b96",
            "a927c3a99f2843de4133377c690db9b7",
            "1fa98cff485549d49799dc8cf987a8af",
            "74013a076a786a26c7e04217bb51031d",
            "a44ca9661e967bb2e98af65277dac72f",
            "d30897726b635548dbfa5cebffd9cd63",
            "4ad04a250b8029c9a7bf6529ee8793c3",
            "de41e337d96fd23619121ea709861e1a",
            "18e070fd32cf732b9f37a0083320eec2",
            "7dd4b27ca8906182f684d0ee4ddb98c4",
            "70a440a8bd06ff40f6e9135946eb174d",
            "b8d052366e752ce7c803abd24854e934",
            "8ab9dfff746ce3e62c6e04feb7b48528",
            "ecfca8b371616efe78e9916dbf825f5b",
            "5f76da828c37fc4edb4557953539c92a",
            "ecad54f76ce3bc233e02fc6fd7f94628",
            "e8a1cc06bfec7f677f36a693e1342400",
            "9ad0fe040e44a8e7146c3dd8582b6752",
            "4e56f978f94cf72158fd4311831b4f9f",
            "3b95686fe49f50006607d5978aaa3efc",
            "fa354daecc45f14b82b0e7e567d24282",
        };
        
        SUITE(md5)
        {
            TEST(MD5_RFC_1321) {
                //MD5 with test vectors from RFC 1321
                {
                    auto md5_hash = MD5("");
                    auto md5_out = md5_hash.hexdigest();
                    VERIFY_ARE_EQUAL(md5_out, "d41d8cd98f00b204e9800998ecf8427e");
                }
                
                {
                    auto md5_hash = MD5("abc");
                    auto md5_out = md5_hash.hexdigest();
                    VERIFY_ARE_EQUAL((md5_out), "900150983cd24fb0d6963f7d28e17f72");
                }
                
                {
                    auto md5_hash = MD5("message digest");
                    auto md5_out = md5_hash.hexdigest();
                    VERIFY_ARE_EQUAL((md5_out), "f96b697d7cb7938d525a2f31aaf161d0");
                }
                
                {
                    auto md5_hash = MD5("abcdefghijklmnopqrstuvwxyz");
                    auto md5_out = md5_hash.hexdigest();
                    VERIFY_ARE_EQUAL((md5_out), "c3fcd3d76192e4007dfb496cca67e13b");
                }
                
                {
                    auto md5_hash = MD5("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
                    auto md5_out = md5_hash.hexdigest();
                    VERIFY_ARE_EQUAL((md5_out), "d174ab98d277d9f5a5611c2c9f419d9f");
                }
                
                {
                    auto md5_hash = MD5("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
                    auto md5_out = md5_hash.hexdigest();
                    VERIFY_ARE_EQUAL((md5_out), "57edf4a22be3c955ac49da2e2107b67a");
                }
                
                VERIFY_ARE_EQUAL(MD5_BYTES.size(), MD5_HASHES.size());
                for ( unsigned int i = 0; i < MD5_BYTES.size(); ++i ) {
                    auto md5 = MD5(unhexlify(MD5_BYTES[i]));
                    VERIFY_ARE_EQUAL(md5.hexdigest(), MD5_HASHES[i]);
                }
                
                
            }
        }
        
    }
}
