/* sub_548650 @ 00548650   261 bytes */

void sub_548650(undefined4 *param_1,uint *param_2)

{
  void *pvVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined2 local_10 [6];
  undefined4 local_4;
  
  uVar3 = DAT_006d9490;
  uVar4 = *param_2;
  param_1[0x10] = 0xffffffff;
  param_1[0x12] = uVar4;
  param_1[0x13] = param_2[2];
  param_1[0x17] = param_2[3];
  param_1[0x16] = 0x80;
  pvVar1 = _malloc(*param_2 * 0xb8);
  param_1[0x11] = pvVar1;
  param_1[0x15] = 0;
  param_1[0x1a] = 0x1000;
  param_1[0x18] = 0x1000;
  param_1[0x19] = 0;
  uVar4 = 0;
  if (*param_2 != 0) {
    puVar2 = (undefined4 *)((int)pvVar1 + 0x88);
    do {
      puVar2[-0x1e] = 0;
      *puVar2 = 0;
      puVar2[3] = 0;
      puVar2[-0x21] = 0;
      *(undefined2 *)(puVar2 + -7) = 0;
      *(undefined2 *)((int)puVar2 + -0x1a) = 0;
      puVar2[-0x1d] = uVar4;
      uVar4 = uVar4 + 1;
      puVar2 = puVar2 + 0x27;
    } while (uVar4 < *param_2);
  }
  pvVar1 = operator_new(param_2[1] * 0x1c);
  puVar2 = param_1 + 4;
  sub_547CE0(puVar2,pvVar1,param_2[1]);
  param_1[0xf] = uVar3;
  *param_1 = 0;
  param_1[2] = &LAB_00548600;
  param_1[1] = param_1;
  sub_547450(uVar3,param_1,0);
  local_10[0] = 8;
  local_4 = 0;
  sub_547D70(puVar2,local_10,param_1[0x13]);
  uVar3 = sub_547D20(puVar2,param_1 + 0xb);
  param_1[0x14] = uVar3;
  return;
}

