/* Original 004170A0: push a 32-bit menu state on the eight-slot stack. */
void sub_4170A0(undefined4 state)
{
  DAT_005839d4[DAT_00583910] = state;
  DAT_00583910 = DAT_00583910 + 1;
}
