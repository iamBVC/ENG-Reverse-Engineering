/* sub_41C640 @ 0041c640   468 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41C640(void)

{
  ushort uVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  ushort *puVar5;
  int iVar6;
  undefined2 extraout_var;
  undefined1 *puVar7;
  undefined *puVar8;
  
  DAT_00584e50 = (undefined1)DAT_00584c28;
  iVar6 = DAT_00584c28 * 0x100;
  puVar7 = &DAT_00584ec8;
  DAT_00584e6c = (uint)(byte)(&DAT_00585275)[iVar6] << 0xc;
  DAT_00584e70 = (uint)(byte)(&DAT_00585276)[iVar6] << 0xc;
  DAT_00584eb4 = (uint)(byte)(&DAT_00585277)[iVar6];
  DAT_00584eb8 = (uint)*(byte *)(&DAT_00585278 + DAT_00584c28 * 0x40);
  DAT_00584ebc = (uint)*(byte *)((int)&DAT_00585278 + iVar6 + 1);
  DAT_00584ec0._0_1_ = *(undefined1 *)((int)&DAT_00585278 + iVar6 + 2);
  DAT_00584ec0._1_3_ = 0;
  _DAT_00584ec4 = (uint)*(byte *)((int)&DAT_00585278 + iVar6 + 3);
  puVar8 = &DAT_0058527c + iVar6;
  do {
    iVar2 = 0;
    do {
      puVar7[iVar2] = puVar8[iVar2];
      iVar2 = iVar2 + 1;
    } while (iVar2 < 6);
    puVar7 = puVar7 + 6;
    puVar8 = puVar8 + 6;
  } while ((int)puVar7 < 0x584efe);
  DAT_00585008 = (uint)(byte)(&DAT_005852b2)[iVar6];
  DAT_0058500c = (uint)(byte)(&DAT_005852b3)[iVar6];
  DAT_00585010 = (uint)(byte)(&DAT_005852b4)[iVar6];
  DAT_00585014 = (uint)(byte)(&DAT_005852b5)[iVar6];
  DAT_00585018._0_1_ = (&DAT_005852b6)[iVar6];
  DAT_00585018._1_1_ = (&DAT_005852b7)[iVar6];
  puVar3 = &DAT_00584f1c;
  puVar5 = (ushort *)(&DAT_005852b8 + iVar6);
  do {
    iVar2 = 6;
    puVar4 = puVar3;
    do {
      puVar3 = puVar4 + 1;
      uVar1 = *puVar5;
      puVar5 = puVar5 + 1;
      *puVar4 = (uint)uVar1;
      iVar2 = iVar2 + -1;
      puVar4 = puVar3;
    } while (iVar2 != 0);
  } while ((int)puVar3 < 0x584ff4);
  iVar2 = 0;
  do {
    (&DAT_00584e80)[iVar2] = (&DAT_00585324)[iVar2 + iVar6];
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x20);
  DAT_00584ea6 = (short)(char)(&DAT_00585347)[iVar6];
  _DAT_00584ea8 = (int)(char)(&DAT_00585348)[iVar6];
  _DAT_00584eac = (int)(char)(&DAT_00585349)[iVar6];
  _DAT_00584f08 = (uint)(byte)(&DAT_0058534a)[iVar6];
  DAT_00585218 = (&DAT_0058534d)[iVar6];
  _DAT_00584f18 = (uint)(byte)(&DAT_0058534c)[iVar6];
  DAT_00585219 = (&DAT_0058534b)[iVar6];
  sub_545F90(DAT_00584ea0,0x80);
  sub_5460A0((int)DAT_00584ea6);
  sub_546000(CONCAT22(extraout_var,DAT_00584ea2),0x80);
  DAT_00584c0c = (byte)DAT_00585018 - 1;
  DAT_0057235a = (ushort)DAT_00585018._1_1_;
  return;
}

