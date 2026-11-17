/* sub_437620 @ 00437620   408 bytes */

float10 sub_437620(undefined4 param_1,undefined4 param_2,int param_3,int param_4,int *param_5,
                  int param_6,int param_7,int param_8,int param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  float local_18;
  
  iVar7 = sub_4377C0(param_1,param_2,&DAT_006913c0);
  iVar8 = sub_4377C0(param_1,param_2,&DAT_0066e23c);
  iVar9 = sub_4377C0(param_1,param_2,&DAT_0064b0b8);
  iVar10 = sub_4377C0(param_1,param_2,&DAT_006b4544);
  local_18 = 0.0;
  *param_5 = -1;
  if (param_4 <= param_3) {
    return (float10)0.0;
  }
  do {
    iVar11 = sub_437910(param_1,param_2,param_3,&DAT_006913c0);
    iVar12 = sub_437910(param_1,param_2,param_3,&DAT_0066e23c);
    iVar13 = sub_437910(param_1,param_2,param_3,&DAT_0064b0b8);
    iVar14 = sub_437910(param_1,param_2,param_3,&DAT_006b4544);
    iVar14 = iVar14 + iVar10;
    if (iVar14 != 0) {
      fVar3 = (float)(iVar13 + iVar9);
      fVar2 = (float)(iVar12 + iVar8);
      fVar1 = (float)(iVar11 + iVar7);
      if ((param_9 - iVar14 != 0) &&
         (fVar6 = (float)(param_8 - (iVar13 + iVar9)), fVar5 = (float)(param_7 - (iVar12 + iVar8)),
         fVar4 = (float)(param_6 - (iVar11 + iVar7)),
         fVar1 = (fVar6 * fVar6 + fVar5 * fVar5 + fVar4 * fVar4) / (float)(param_9 - iVar14) +
                 (fVar3 * fVar3 + fVar2 * fVar2 + fVar1 * fVar1) / (float)iVar14, local_18 < fVar1))
      {
        *param_5 = param_3;
        local_18 = fVar1;
      }
    }
    param_3 = param_3 + 1;
  } while (param_3 < param_4);
  return (float10)local_18;
}

