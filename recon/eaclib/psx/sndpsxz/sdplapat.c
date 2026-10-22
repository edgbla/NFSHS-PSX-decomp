/* eaclib/psx/sndpsxz/sdplapat.c -- RECONSTRUCTED from nfs4-f.exe. NOT original source.  *** 1/1 ***
 *   Source obj : nfs4\eaclib\psx\sdplapat.obj ; archive C:\nfs4\EACLIB\PSX\SNDPSXZ.LIB (xlsx col11)
 *   1 fn @0x8010BA48.  iSNDplatformplay -- the per-voice SPU launcher for a sound patch (the patch-side
 *   twin of sdpacket's iSNDplatformpacketplay): parse the patch's tag stream into the voice-state table and
 *   key the voice.  Ghidra nfs4-f.exe.c (sdplapat) + the call-site oracle establish an 8-arg ABI
 *   (the callee does not read the eighth argument; Ghidra showed only 3 + in_a3/in_stack_*).
 *   Tags: 0x82 channel count, 0x84 sample rate, 0x85 loop length, 0x8a sample-data ptr, 0x92 output mode.
 *   iSNDgettag is 4-arg (Ghidra dropped to 2).
 */
#include "sdata.h"
#include "sndserverpriv.h"
#include "sndchpriv.h"
#include "sndpacketpriv.h"
#include "sdplapat.h"
#include "sdriver.h"
#include "sgettag.h"

extern unsigned char sndpd[];
extern unsigned char DAT_801479f0;   /* voice-table byte base; retained for exact address materialization */

/* iSNDplatformplay @0x8010BA48 : launch `voice` playing the patch whose tag stream starts at `chan`.
 * MATCH (W31, was 32 diffs): (1) the tag parser is a natural `while` loop, not a goto chain -- loop
 * notes weight the in-loop defs' ref counts, allocating sampleData/voice values in oracle order;
 * (2) channel_count's initial plain store and volatile in-loop re-store let gcc cross-jump the
 * two identical stores without moving the shared store into the tag-0x82 branch delay slot;
 * (3) record fields are read/written through SndPacketVoiceState member views, while `slot` remains
 * the byte cursor that preserves the original manually-scaled voice index/address expression;
 * (4) link_index.vs preserves the signed -1 initialization; `.vu` preserves unsigned volatile
 * reads for linked-channel indexing. The persistent typed-pointer alias was tested and rejected
 * (95 diffs / 176 instructions); per-access typed views retain the exact 171-instruction match. */
int iSNDplatformplay(int chan, int voice, int level, int pitch, int a5, int fx,
                            int volAngle, int pitchOffset)
{
    int           *sampleData = 0;         /* 0x8a tag -> sample-header ptr */
    int           vt;
    unsigned char *slot;
    int           rate = 0x5622;           /* 0x84 tag (default) */
    int           loopVal = 0;             /* 0x85 tag */
    unsigned int  id;
    int           val;
    int           *ptr;
    (void)a5;
    (void)pitchOffset;

    vt = voice << 1;
    vt = vt + voice;
    vt = vt << 2;
    vt = vt - voice;
    vt = vt << 2;
    slot = &DAT_801479f0 + vt;

    ((volatile SndPacketVoiceState *)slot)->link_flag = 0;
    ((volatile SndPacketVoiceState *)slot)->link_index.vs = -1;
    ((SndPacketVoiceState *)slot)->route = 0;
    ((volatile SndPacketVoiceState *)slot)->channel_count = 1;
    while (iSNDgettag(&chan, &id, &val, (int *)&ptr) != 0 && id != 0xfe) {
        if (id == 0x8a) {
            sampleData = ptr;
            continue;
        }
        if (id == 0x85) {
            loopVal = val;
            continue;
        }
        if (id == 0x82) {
            ((volatile SndPacketVoiceState *)slot)->channel_count = *(unsigned char *)&val;
            continue;
        }
        if (id == 0x84) {
            rate = val;
            continue;
        }
        if (id == 0x92)
            ((volatile SndPacketVoiceState *)slot)->route = (unsigned char)val;
    }

    ((volatile SndPacketVoiceState *)slot)->word04 = loopVal;
    ((volatile SndPacketVoiceState *)slot)->level = (char)level;
    ((volatile SndPacketVoiceState *)slot)->volume_angle = (unsigned short)volAngle;
    ((volatile SndPacketVoiceState *)slot)->fx_level = (unsigned char)fx;
    ((volatile SndPacketVoiceState *)slot)->header_word0 = *sampleData;
    ((volatile SndPacketVoiceState *)slot)->byte_position = 0;
    ((volatile SndPacketVoiceState *)slot)->served_position = 0;
    ((volatile SndPacketVoiceState *)slot)->loop_length = loopVal << 0xc;
    ((volatile SndPacketVoiceState *)slot)->initial_pitch.vs = (short)((rate * 0x17c7) >> 0x10);
    if (1 < (unsigned char)((volatile SndPacketVoiceState *)slot)->channel_count) { /* arm linked voice */
        unsigned char *voiceBase = sndpd;
        ((SndPacketVoiceState *)slot)->link_index.u = ((SndChannel *)(unsigned int)((struct SndGlobalServerStateView *)sndgs)->play_records)[voice].linked_tag_view.linked_channels[0];
        voiceBase[(((int)(unsigned)((volatile SndPacketVoiceState *)slot)->link_index.vu << 24) >> 24) * 0x2c + 0xf9] = 1;
        *(int *)(voiceBase + (((int)(unsigned)((volatile SndPacketVoiceState *)slot)->link_index.vu << 24) >> 24) * 0x2c + 0xe4) = 0;
        *(int *)(voiceBase + (((int)(unsigned)((volatile SndPacketVoiceState *)slot)->link_index.vu << 24) >> 24) * 0x2c + 0xe8) = 0;
        *(int *)(voiceBase + (((int)(unsigned)((volatile SndPacketVoiceState *)slot)->link_index.vu << 24) >> 24) * 0x2c + 0xec) = ((SndPacketVoiceState *)slot)->loop_length;
    }
    iSNDplatformpitch(voice, pitch);
    ((SndPacketVoiceState *)slot)->play_state = 1;                                     /* playstate = playing */
    return 0;
}
