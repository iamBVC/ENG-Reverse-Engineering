/* sub_41C820 @ 0041c820   395 bytes */

void sub_41C820(void)

{
  undefined2 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined2 *puVar6;
  int iVar7;
  undefined1 *puVar8;
  undefined *puVar9;
  
  iVar4 = DAT_00584c28;
  DAT_00584e50 = (undefined1)DAT_00584c28;
  iVar7 = DAT_00584c28 * 0x100;
  puVar8 = &DAT_00584ec8;
  (&DAT_00585274)[iVar7] = 1;
  (&DAT_00585275)[iVar7] = (char)(DAT_00584e6c >> 0xc);
  uVar2 = (undefined1)DAT_00585588;
  puVar9 = &DAT_0058527c + iVar7;
  (&DAT_00585276)[iVar7] = (char)(DAT_00584e70 >> 0xc);
  uVar3 = (undefined1)DAT_00584c24;
  (&DAT_00585277)[iVar7] = uVar2;
  uVar2 = (undefined1)DAT_00584c20;
  *(undefined1 *)(&DAT_00585278 + iVar4 * 0x40) = uVar3;
  uVar3 = (undefined1)DAT_0058557c;
  *(undefined1 *)((int)&DAT_00585278 + iVar7 + 1) = uVar2;
  *(undefined1 *)((int)&DAT_00585278 + iVar7 + 2) = uVar3;
  *(undefined1 *)((int)&DAT_00585278 + iVar7 + 3) = DAT_00584ec4;
  do {
    iVar4 = 0;
    do {
      puVar9[iVar4] = puVar8[iVar4];
      iVar4 = iVar4 + 1;
    } while (iVar4 < 6);
    puVar8 = puVar8 + 6;
    puVar9 = puVar9 + 6;
  } while ((int)puVar8 < 0x584efe);
  (&DAT_005852b2)[iVar7] = (undefined1)DAT_00585008;
  (&DAT_005852b3)[iVar7] = (undefined1)DAT_0058500c;
  (&DAT_005852b4)[iVar7] = (undefined1)DAT_00585010;
  (&DAT_005852b5)[iVar7] = (undefined1)DAT_00585014;
  (&DAT_005852b6)[iVar7] = (undefined1)DAT_00585018;
  (&DAT_005852b7)[iVar7] = DAT_00585018._1_1_;
  puVar5 = &DAT_00584f1c;
  puVar6 = (undefined2 *)(&DAT_005852b8 + iVar7);
  do {
    iVar4 = 6;
    do {
      uVar1 = *(undefined2 *)puVar5;
      puVar5 = puVar5 + 1;
      *puVar6 = uVar1;
      puVar6 = puVar6 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  } while ((int)puVar5 < 0x584ff4);
  iVar4 = 0;
  do {
    (&DAT_00585324)[iVar4 + iVar7] = (&DAT_00584e80)[iVar4];
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x20);
  (&DAT_00585344)[iVar7] = (undefined1)DAT_00584ea0;
  (&DAT_00585345)[iVar7] = (undefined1)DAT_00584ea2;
  (&DAT_00585346)[iVar7] = DAT_00584ea4;
  (&DAT_00585347)[iVar7] = (undefined1)DAT_00584ea6;
  (&DAT_00585348)[iVar7] = DAT_00584ea8;
  (&DAT_00585349)[iVar7] = DAT_00584eac;
  (&DAT_0058534a)[iVar7] = DAT_00584f08;
  (&DAT_0058534d)[iVar7] = DAT_00585218;
  (&DAT_0058534c)[iVar7] = DAT_00584f18;
  (&DAT_0058534b)[iVar7] = DAT_00585219;
  return;
}

