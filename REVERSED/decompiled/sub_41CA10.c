/* sub_41CA10 @ 0041ca10   238 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41CA10(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (param_1 == 0x100) {
    sub_41C9D0();
  }
  else {
    sub_41C9F0();
  }
  DAT_00584e6c = 0x5000;
  DAT_00584e70 = 0x5000;
  DAT_00584ffc = 0;
  _DAT_00584ff8 = 0;
  DAT_00584ff4 = 0;
  (&DAT_00584f1c)[DAT_00584ebc + DAT_00584eb8 * 6] = 0;
  _DAT_00584f18 = 0;
  DAT_00585008 = 0;
  DAT_00584638 = 0;
  puVar2 = (undefined4 *)&DAT_00584ec8;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined2 *)puVar2 = 0;
  sub_41CD70();
  DAT_00584ec0 = 0;
  DAT_00585014 = 0;
  DAT_0058557c = 0;
  DAT_00584e50 = 0;
  DAT_00584e64 = 0;
  DAT_00584c0c = 0;
  DAT_00584eb4 = 1;
  DAT_00584eb8 = 1;
  DAT_00584ebc = 1;
  DAT_00585008 = 1;
  DAT_0058500c = 1;
  DAT_00585010 = 1;
  DAT_00585588 = 1;
  DAT_00584c24 = 1;
  DAT_00584c20 = 1;
  DAT_00585018._0_1_ = 1;
  DAT_00585018._1_1_ = 1;
  DAT_006d94b4 = 0xffffffff;
  DAT_0057235a = 1;
  return;
}

