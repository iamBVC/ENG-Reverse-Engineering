/* sub_558DB0 @ 00558db0   222 bytes */

void sub_558DB0(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined1 local_4 [4];
  
  iVar1 = param_2;
  sub_415AB0(param_2,&DAT_006da338);
  sub_415AB0(iVar1,&param_2);
  sub_415AB0(iVar1,local_4);
  DAT_006da338 = DAT_006da338 + 1;
  DAT_006da334 = sub_41EF00(DAT_006da338 * param_2 * 4);
  puVar2 = (undefined4 *)sub_41EF00(DAT_006da338 * param_2 * 4);
  uVar4 = 0;
  puVar5 = puVar2;
  if (DAT_006da338 * param_2 != 0) {
    do {
      sub_415AB0(iVar1,puVar5);
      uVar3 = sub_41EF00(*puVar5);
      *(undefined4 *)(DAT_006da334 + uVar4 * 4) = uVar3;
      uVar4 = uVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (uVar4 < (uint)(DAT_006da338 * param_2));
  }
  uVar4 = 0;
  if (DAT_006da338 * param_2 != 0) {
    do {
      sub_415A90(iVar1,*(undefined4 *)(DAT_006da334 + uVar4 * 4),puVar2[uVar4]);
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)(DAT_006da338 * param_2));
  }
  return;
}

