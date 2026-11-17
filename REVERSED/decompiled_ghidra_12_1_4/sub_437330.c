/* sub_437330 @ 00437330   297 bytes */

float10 sub_437330(int *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  
  iVar13 = sub_437290(param_1,&DAT_006913c0);
  iVar14 = sub_437290(param_1,&DAT_0066e23c);
  iVar15 = sub_437290(param_1,&DAT_0064b0b8);
  iVar16 = *param_1;
  iVar9 = (param_1[3] + param_1[5] * 0x21) * 0x21;
  iVar10 = (param_1[2] + param_1[5] * 0x21) * 0x21;
  iVar11 = (param_1[4] * 0x21 + param_1[3]) * 0x21;
  iVar12 = (param_1[2] + param_1[4] * 0x21) * 0x21;
  fVar1 = (float)(&DAT_00627f34)[param_1[1] + iVar9];
  fVar2 = (float)(&DAT_00627f34)[iVar9 + iVar16];
  iVar9 = param_1[1];
  fVar3 = (float)(&DAT_00627f34)[iVar10 + iVar9];
  fVar4 = (float)(&DAT_00627f34)[iVar10 + iVar16];
  fVar5 = (float)(&DAT_00627f34)[iVar11 + iVar9];
  fVar6 = (float)(&DAT_00627f34)[iVar11 + iVar16];
  fVar7 = (float)(&DAT_00627f34)[iVar9 + iVar12];
  fVar8 = (float)(&DAT_00627f34)[iVar12 + iVar16];
  iVar16 = sub_437290(param_1,&DAT_006b4544);
  return (float10)((((((fVar1 - fVar2) - fVar3) + fVar4) - fVar5) + fVar6 + fVar7) - fVar8) -
         (float10)((float)iVar13 * (float)iVar13 +
                  (float)iVar14 * (float)iVar14 + (float)iVar15 * (float)iVar15) / (float10)iVar16;
}

