/* Original stack layout: 0x3c bytes of constructor context followed by a
   0x154-byte temporary actor. Both are addressed by the constructor. */

void sub_54CFC0(int param_1)
{
  uint block[100] = {0};
  uint *actor = block + 15;
  uint *record = *(uint **)(param_1 + 0x38);
  uint index;

  block[0] = (uint)actor;
  DAT_006d9dc8 = 0;
  fprintf(stderr, "[actors] instantiate records=%u\n", *(uint *)(param_1 + 4));
  for (index = 0; index < *(uint *)(param_1 + 4); ++index, record += 18) {
    if ((record[17] & 2) != 0) continue;
    block[1] = record[9];
    block[2] = record[12];
    block[3] = record[13];
    block[4] = record[14];
    block[6] = (uint)record;
    block[7] = record[0] << 12;
    block[8] = record[1] << 12;
    block[9] = record[2] << 12;
    block[11] = record[4];
    block[12] = record[5];
    block[13] = record[6];
    block[14] = record[7];
    actor[65] = record[10] + record[9] * 4;
    actor[70] = record[15];
    actor[71] = record[16];
    actor[72] = record[15];
    sub_54BFC0(block, block + 7, record[8], record[11], 0);
  }
  sub_41E1B0();
  fprintf(stderr, "[actors] created=%u main=%p head=%p\n",
          DAT_006d9dc8, (void *)DAT_006d9e28, (void *)DAT_006d9e38);
}
