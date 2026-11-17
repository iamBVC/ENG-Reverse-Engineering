/* sub_427E40 @ 00427e40   70 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_427E40(int param_1)

{
  uint uVar1;
  
  uVar1 = param_1 >> 1 & 7;
  DAT_00573668 = 0x8a;
  _DAT_0057365c = uVar1 + 10;
  DAT_00573664 = (byte)(&DAT_00573810)[uVar1] + 200;
  DAT_0057366d = 1;
  sub_425D40(&DAT_00573650,0);
  return;
}

