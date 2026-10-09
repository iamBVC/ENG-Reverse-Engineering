/* sub_436D40 @ 00436d40   229 bytes */

void sub_436D40(ushort *param_1,int param_2)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  if (0 < param_2) {
    do {
      uVar2 = *param_1;
      param_1 = param_1 + 1;
      if ((DAT_006d76c8 == 0) || (uVar2 != 0)) {
        uVar6 = uVar2 >> 10 & 0x1f;
        uVar7 = uVar2 >> 5 & 0x1f;
        uVar8 = uVar2 & 0x1f;
        iVar1 = (uVar7 + uVar6 * 0x21) * 0x21 + 0x463 + uVar8;
        (&DAT_006b4544)[iVar1] = (&DAT_006b4544)[iVar1] + 1;
        (&DAT_006913c0)[iVar1] = (&DAT_006913c0)[iVar1] + uVar8;
        iVar3 = (&DAT_0061fb34)[uVar6];
        (&DAT_0066e23c)[iVar1] = (&DAT_0066e23c)[iVar1] + uVar7;
        iVar4 = (&DAT_0061fb34)[uVar7];
        iVar5 = (&DAT_0061fb34)[uVar8];
        (&DAT_0064b0b8)[iVar1] = (&DAT_0064b0b8)[iVar1] + uVar6;
        (&DAT_00627f34)[iVar1] = (float)(iVar3 + iVar4 + iVar5) + (float)(&DAT_00627f34)[iVar1];
      }
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}

