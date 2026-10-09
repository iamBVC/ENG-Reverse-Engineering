/* sub_547470 @ 00547470   307 bytes */

void sub_547470(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar1 = param_1;
  *param_1 = 0;
  param_1[1] = *(undefined4 *)(param_2 + 4);
  param_1[4] = 0;
  param_1[3] = 0;
  param_1[8] = 0;
  param_1[7] = 0;
  param_1[6] = 0;
  param_1[5] = 0;
  pvVar2 = operator_new(*(int *)(param_2 + 4) * 0xe8);
  param_1[2] = pvVar2;
  param_1 = (undefined4 *)0x0;
  if (0 < *(int *)(param_2 + 4)) {
    puVar4 = (undefined4 *)((int)pvVar2 + 0xc);
    do {
      sub_546E10(puVar4 + -3,puVar1 + 3);
      puVar4[-1] = 0;
      *(undefined2 *)puVar4 = param_1._0_2_;
      *(undefined2 *)((int)puVar4 + 2) = 0;
      puVar5 = puVar4;
      for (iVar3 = 0x36; puVar5 = puVar5 + 1, iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = 0;
      }
      param_1 = (undefined4 *)((int)param_1 + 1);
      puVar4 = puVar4 + 0x3a;
    } while ((int)param_1 < *(int *)(param_2 + 4));
  }
  puVar1[0x11] = 0;
  pvVar2 = operator_new(*(int *)(param_2 + 0xc) << 2);
  puVar1[0x14] = pvVar2;
  pvVar2 = operator_new(*(int *)(param_2 + 0xc) << 2);
  puVar1[0x13] = pvVar2;
  pvVar2 = _malloc(*(int *)(param_2 + 0xc) << 2);
  puVar1[0x12] = pvVar2;
  iVar3 = 0;
  if (0 < *(int *)(param_2 + 0xc)) {
    do {
      iVar3 = iVar3 + 1;
      *(undefined4 *)(puVar1[0x14] + -4 + iVar3 * 4) = 0;
      *(undefined4 *)(puVar1[0x13] + -4 + iVar3 * 4) = 0;
      *(undefined4 *)(puVar1[0x12] + -4 + iVar3 * 4) = 0;
    } while (iVar3 < *(int *)(param_2 + 0xc));
  }
  puVar1[0x15] = 0;
  puVar1[0x16] = DAT_005834f0;
  puVar1[9] = 0;
  puVar1[10] = 0;
  puVar1[0xb] = 0;
  puVar1[0xc] = 0;
  puVar1[0xd] = 0;
  puVar1[0xe] = 0;
  puVar1[0xf] = 0;
  puVar1[0x10] = 0;
  *(undefined2 *)(puVar1 + 0x17) = 0x80;
  *(undefined2 *)(puVar1 + 0x18) = 0x80;
  *(undefined2 *)((int)puVar1 + 0x5e) = 100;
  *(undefined2 *)((int)puVar1 + 0x62) = 0x80;
  return;
}

