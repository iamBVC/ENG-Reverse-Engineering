/*
 * Recovered from Game/groove.exe.asm, sub_5458D0 (005458D0-00545BFA).
 *
 * Each entry in DAT_006d949c+0xA4 is a 0x28-byte sound-track record:
 *   +0x10 start tick, +0x14 end tick, +0x18 channel/flags,
 *   +0x1C target volume, +0x20 active-group bit mask, +0x24 applied volume.
 * The routine updates each track's envelope, arbitrates tracks that share a
 * channel, and updates the device-wide distance/range value when it changes.
 */
void sub_5458D0(void)
{
  int context;
  int device;
  short track_count;
  unsigned int range;
  unsigned int index;

  context = DAT_006d949c;
  if (context == 0 || *(int *)(context + 0xA4) == 0 ||
      (*(unsigned char *)(context + 0x54) & 1) != 0)
    return;

  device = *(int *)(context + 0x10);
  track_count = *(short *)(context + 0xA0);
  range = *(unsigned int *)(device + 0x3C);

  for (index = 0; track_count > 0 && (short)index < track_count; ++index) {
    int track = *(int *)(*(int *)(context + 0xA4) + index * 4);
    unsigned int tick = (unsigned int)sub_547C00(track);
    unsigned int target_volume;
    unsigned int volume;
    unsigned int state;
    unsigned int channel_flags;
    unsigned int bit;
    unsigned int other_index;

    if (*(unsigned int *)(track + 0x10) < tick) {
      unsigned int end_tick = *(unsigned int *)(track + 0x14);
      unsigned int remaining = end_tick - *(unsigned int *)(track + 0x10);
      if (tick < end_tick && (int)remaining > 0)
        target_volume = ((end_tick - tick) * *(int *)(track + 0x1C)) / remaining;
      else
        target_volume = 0;
    } else {
      target_volume = *(unsigned int *)(track + 0x1C);
    }

    /* Signed IMUL followed by SAR, matching the original 32-bit instructions. */
    {
      unsigned int product = (unsigned int)*(int *)(DAT_006d9490 + 0x100) * target_volume;
      volume = (unsigned int)(((int)product) >> 12);
    }
    channel_flags = *(unsigned int *)(track + 0x18);
    state = *(unsigned int *)(track + 0x20);

    if ((channel_flags & 0x10000) != 0) {
      if (range < volume)
        range = volume;
      continue;
    }

    if (volume != 0 && state == 0) {
      unsigned short channel = *(unsigned short *)(track + 0x18);
      if (sub_5499A0(context, channel) == 0) {
        sub_549A00(context, channel, 0);
        sub_549AC0(context, channel);
      }

      bit = 1u << (index & 31);
      state |= bit;
      *(unsigned int *)(track + 0x20) = state;

      for (other_index = 0; (short)other_index < track_count; ++other_index) {
        int other = *(int *)(*(int *)(context + 0xA4) + other_index * 4);
        unsigned int other_state = *(unsigned int *)(other + 0x20);
        if (other_state != 0 &&
            *(unsigned int *)(track + 0x18) == *(unsigned int *)(other + 0x18)) {
          unsigned int other_bit = 1u << (other_index & 31);
          *(unsigned int *)(other + 0x20) = other_state | other_bit | bit;
          state |= other_bit | bit;
          *(unsigned int *)(track + 0x20) = state;
        }
      }
    }

    state = *(unsigned int *)(track + 0x20);
    if (state == 0)
      continue;

    if (*(unsigned int *)(track + 0x24) != volume) {
      unsigned int highest_shared_volume = volume;

      for (other_index = 0; (short)other_index < track_count; ++other_index) {
        int other;
        unsigned int other_state;
        unsigned int other_volume;
        if (other_index == index)
          continue;
        other = *(int *)(*(int *)(context + 0xA4) + other_index * 4);
        other_state = *(unsigned int *)(other + 0x20);
        if ((state & other_state) == 0)
          continue;
        other_volume = *(unsigned int *)(other + 0x24);
        if (volume < other_volume)
          highest_shared_volume = other_volume;
      }

      if (highest_shared_volume != volume) {
        /* A louder track sharing this channel already controls the channel. */
        *(unsigned int *)(track + 0x24) = volume;
      } else {
        int channel_limit = 0;
        unsigned short channel = *(unsigned short *)(track + 0x18);
        unsigned int applied_volume;

        sub_5499D0(context, channel, &channel_limit);
        applied_volume = (unsigned int)((short)channel_limit + 1);
        if ((int)volume <= (int)applied_volume) {
          unsigned int lower_limit = (unsigned int)((short)channel_limit - 1);
          applied_volume = volume;
          if ((int)volume < (int)lower_limit)
            applied_volume = lower_limit;
        }

        *(unsigned int *)(track + 0x24) = applied_volume;
        sub_549A00(context, channel, applied_volume);
      }

      if (*(unsigned int *)(track + 0x24) == 0) {
        for (other_index = 0; (short)other_index < track_count; ++other_index) {
          int other = *(int *)(*(int *)(context + 0xA4) + other_index * 4);
          unsigned int other_state = *(unsigned int *)(other + 0x20);
          if ((state & other_state) != 0)
            *(unsigned int *)(other + 0x20) =
                other_state & ~(1u << (other_index & 31));
        }

        state = *(unsigned int *)(track + 0x20);
        if (state == 0 && sub_5499A0(context, *(unsigned short *)(track + 0x18)) != 0)
          sub_549A70(context, *(unsigned short *)(track + 0x18));
        *(unsigned int *)(track + 0x20) = 0;
      }
    }
  }

  if (range != *(unsigned int *)(device + 0x38)) {
    *(unsigned int *)(device + 0x38) = range;
    if (DAT_005834f4 != 0) {
      int converted_range;
      converted_range = (int)sub_544FC0(0, 50.0f, (float)range);
      *(unsigned int *)(DAT_006d9490 + 0x68) |= 3;
      *(int *)(DAT_006d9490 + 0x6C) = converted_range;
      *(int *)(DAT_006d9490 + 0x70) = converted_range;
    }
  }
}
