/* sub_437460 @ 00437460   442 bytes */

undefined4 sub_437460(int *param_1,int *param_2)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  float10 fVar8;
  int local_c;
  int local_8;
  int local_4;
  
  piVar3 = param_1;
  uVar4 = sub_437290(param_1,&DAT_006913c0);
  uVar5 = sub_437290(param_1,&DAT_0066e23c);
  uVar6 = sub_437290(param_1,&DAT_0064b0b8);
  uVar7 = sub_437290(param_1,&DAT_006b4544);
  fVar8 = (float10)sub_437620(param_1,2,*param_1 + 1,param_1[1],&local_c,uVar4,uVar5,uVar6,uVar7);
  fVar1 = (float)fVar8;
  fVar8 = (float10)sub_437620(param_1,1,param_1[2] + 1,param_1[3],&local_8,uVar4,uVar5,uVar6,uVar7);
  fVar2 = (float)fVar8;
  fVar8 = (float10)sub_437620(param_1,0,param_1[4] + 1,param_1[5],&local_4,uVar4,uVar5,uVar6,uVar7);
  if ((fVar1 < fVar2) || (fVar1 < (float)fVar8)) {
    if ((fVar2 < fVar1) || (param_1 = (int *)0x1, fVar2 < (float)fVar8)) {
      param_1 = (int *)0x0;
    }
  }
  else {
    param_1 = (int *)0x2;
    if (local_c < 0) {
      return 0;
    }
  }
  param_2[1] = piVar3[1];
  param_2[3] = piVar3[3];
  param_2[5] = piVar3[5];
  if (param_1 == (int *)0x0) {
    piVar3[5] = local_4;
    param_2[4] = local_4;
    *param_2 = *piVar3;
    param_2[2] = piVar3[2];
  }
  else if (param_1 == (int *)0x1) {
    piVar3[3] = local_8;
    param_2[2] = local_8;
    *param_2 = *piVar3;
    param_2[4] = piVar3[4];
  }
  else if (param_1 == (int *)0x2) {
    piVar3[1] = local_c;
    *param_2 = local_c;
    param_2[2] = piVar3[2];
    param_2[4] = piVar3[4];
  }
  piVar3[6] = (piVar3[1] - *piVar3) * (piVar3[5] - piVar3[4]) * (piVar3[3] - piVar3[2]);
  param_2[6] = (param_2[3] - param_2[2]) * (param_2[5] - param_2[4]) * (param_2[1] - *param_2);
  return 1;
}

