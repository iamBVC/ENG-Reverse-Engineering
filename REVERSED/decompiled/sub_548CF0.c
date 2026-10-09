/* sub_548CF0 @ 00548cf0   274 bytes */

void sub_548CF0(undefined4 *param_1,uint *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  void *pvVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined2 local_10 [6];
  undefined4 local_4;
  
  iVar1 = DAT_006d9490;
  *(char *)(param_1 + 0x1c) = (char)param_2[3];
  *(char *)((int)param_1 + 0x71) = (char)*param_2;
  param_1[0x12] = param_2[2];
  *(undefined1 *)((int)param_1 + 0x73) = *(undefined1 *)((int)param_2 + 0xd);
  *(undefined2 *)((int)param_1 + 0x6e) = *(undefined2 *)(iVar1 + 0x60);
  param_1[4] = iVar1;
  *(undefined2 *)(param_1 + 0x1b) = 0;
  param_1[0x13] = 2;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x14] = 0;
  *(undefined1 *)((int)param_1 + 0x72) = 0;
  param_1[0x29] = 0;
  param_1[0x15] = 0;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  puVar2 = _malloc(*param_2 * 0xb8);
  param_1[0x16] = puVar2;
  param_1[0x1f] = 0;
  uVar5 = 0;
  if (*param_2 != 0) {
    do {
      puVar2[5] = uVar5;
      *puVar2 = param_1[0x1f];
      param_1[0x1f] = puVar2;
      uVar5 = uVar5 + 1;
      puVar2 = puVar2 + 0x27;
    } while (uVar5 < *param_2);
  }
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  pvVar3 = operator_new(param_2[1] * 0x1c);
  sub_547CE0(param_1 + 5,pvVar3,param_2[1]);
  param_1[4] = iVar1;
  *param_1 = 0;
  param_1[2] = sub_548E10;
  param_1[1] = param_1;
  sub_547450(iVar1,param_1,0);
  local_10[0] = 8;
  local_4 = 0;
  sub_547D70(param_1 + 5,local_10,param_1[0x12]);
  uVar4 = sub_547D20(param_1 + 5,param_1 + 0xc);
  param_1[0x10] = uVar4;
  return;
}

