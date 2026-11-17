/* Recovered from Game/groove.exe.asm, sub_549270 (00549270-00549620).
 *
 * IDA shows three stack arguments and a plain near return.  This is cdecl:
 * context, track, and the event record.  The Ghidra export's
 * four-parameter __thiscall declaration is an ABI recovery error.
 */
void sub_549270(int context, int track, int event_record)
{
  unsigned char *event = (unsigned char *)event_record;
  unsigned char status = event[10];
  unsigned int channel = status & 0x0f;
  unsigned char command = status & 0xf0;
  int *voice;
  int *node;
  int instrument;
  int handle;
  int value;
  int local_4;
  int bend;

  switch (command) {
  case 0x90: /* note on */
    if (event[12] == 0)
      goto note_off;

    instrument = sub_549830(track, event[11], event[12], channel);
    if (instrument == 0)
      return;
    voice = (int *)sub_549710(context, event[11], event[12], channel);
    if (voice == 0)
      return;

    handle = (int)(voice + 0x20);
    voice[0x25] = 0;
    sub_547750(*(int *)(context + 0x10), handle,
               *(unsigned char *)(track + 0x53 + channel * 12), 0);
    if (voice[0x22] == 0)
      return;

    *(unsigned short *)((char *)voice + 0x6c) =
        (unsigned short)sub_5498C0(event[11],
                                   *(signed char *)(track + channel * 12 + 0x57),
                                   *(unsigned char *)(instrument + 4),
                                   *(unsigned char *)(instrument + 5));
    voice[2] = instrument;
    voice[3] = track;
    voice[4] = 2;
    sub_5479B0(voice[0x22], *(unsigned char *)(instrument + 1) & 4);
    sub_547900(voice[0x22], *(unsigned short *)((char *)voice + 0x6c));
    sub_5478C0(voice[0x22], sub_5490C0(context, track, (int)voice));
    local_4 = 0;
    value = sub_5497B0(track, (int)voice, &local_4);
    sub_547950(voice[0x22], value);
    sub_426500(voice[0x22], *(unsigned short *)(instrument + 0x10),
               *(unsigned short *)(instrument + 0x12));
    if (local_4 != 0)
      sub_547970(voice[0x22], local_4);
    sub_547840(*(int *)(context + 0x10), voice[0x22]);
    return;

  case 0x80: /* note off */
  note_off:
    handle = sub_549880(context, track, event[11], channel);
    if (handle != 0)
      sub_549760(context, handle + 0x80, 0);
    return;

  case 0xb0: /* control change */
    switch (event[11]) {
    case 6: /* data entry MSB */
    case 99: /* NRPN MSB */
      if (event[12] == 0x1e) {
        *(int *)(track + 0x34) = *(int *)(track + 0x14);
        *(unsigned short *)(track + 0x48) = *(unsigned short *)(track + 0x20);
        *(int *)(track + 0x44) = *(int *)(track + 0x18);
      }
      return;

    case 7: /* channel volume */
    case 11: /* expression */
      *(unsigned char *)(track + (channel + 7) * 12) = event[12];
      for (node = *(int **)(context + 0x74); node != 0; node = (int *)node[0]) {
        if (node[3] == track && *((signed char *)node + 0x7d) == (signed char)channel)
          sub_5478C0(node[0x22], sub_5490C0(context, track, (int)node));
      }
      return;

    case 10: /* pan */
      *(unsigned char *)(track + 0x52 + channel * 12) = event[12];
      for (node = *(int **)(context + 0x74); node != 0; node = (int *)node[0]) {
        if (node[3] == track && *((signed char *)node + 0x7d) == (signed char)channel)
          sub_5478C0(node[0x22], sub_5490C0(context, track, (int)node));
      }
      return;

    case 16: /* bank/program data retained on the track */
      *(unsigned char *)(track + 0x53 + channel * 12) = event[12];
      return;
    }
    return;

  case 0xc0: /* program change */
    sub_5497F0(track, (unsigned int)event[11] * 16 +
                        *(int *)(*(int *)(track + 0x38) + 4), channel);
    return;

  case 0xe0: /* pitch bend */
    bend = ((int)event[12] - 0x40) * 0x80 + (int)event[11];
    bend = (bend * 0x960 + ((bend * 0x960) >> 31 & 0x1fff)) >> 13;
    *(signed char *)(track + 0x57 + channel * 12) = (signed char)bend;
    for (node = *(int **)(context + 0x74); node != 0; node = (int *)node[0]) {
      if (node[3] == track && *((signed char *)node + 0x7d) == (signed char)channel) {
        instrument = node[2];
        value = sub_5498C0(*(unsigned char *)((char *)node + 0x7c), bend,
                           *(unsigned char *)(instrument + 4),
                           *(unsigned char *)(instrument + 5));
        *(unsigned short *)((char *)node + 0x6c) = (unsigned short)value;
        sub_547900(node[0x22], value);
      }
    }
    return;
  }
}
