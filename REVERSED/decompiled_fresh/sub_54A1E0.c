/* sub_54A1E0 @ 0054a1e0   144 bytes */

void sub_54A1E0(int param_1)

{
  if (DAT_005855b0 != 0) {
    DAT_00584700 = (-(uint)(param_1 != 0) & 0xfffffff6) + 0xc;
    return;
  }
  DAT_00584eb8 = DAT_00584c24;
  DAT_00584eb4 = DAT_00585588;
  DAT_00584ebc = DAT_00584c20;
  DAT_00584ec0 = DAT_0058557c;
  if (DAT_006d94b0 == '\x01') {
    if ((DAT_0058500c == 8) && (DAT_00585010 == 6)) {
      DAT_00584700 = 10;
      return;
    }
    DAT_00584700 = 0xc;
    return;
  }
  DAT_00584700 = 3;
  DAT_00584638 = 7;
  return;
}

