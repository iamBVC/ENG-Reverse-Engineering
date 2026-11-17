/* sub_21106900 @ 21106900   461 bytes */

undefined4 __thiscall sub_21106900(void *this,int *param_1)

{
  int iVar1;
  uint uVar2;
  undefined2 *puVar3;
  LPSTR lpString1;
  undefined4 uVar4;
  void *pvVar5;
  uint *puVar6;
  uint *puVar7;
  
  puVar7 = (uint *)(param_1 + 1);
  if (*param_1 == 0x20677663) {
    puVar7 = (uint *)(param_1 + 2);
  }
  else if ((((param_1[5] == 0) || (0x7d000 < (uint)param_1[5])) ||
           (0x7f < *(ushort *)((int)param_1 + 10))) || ((*puVar7 == 0 || (100000 < *puVar7)))) {
    return 1;
  }
  if (*(int *)((int)this + 0x18) != 0) {
    return 0;
  }
  puVar3 = operator_new(0x12);
  *(undefined2 **)((int)this + 0x18) = puVar3;
  *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 1;
  *puVar3 = 1;
  *(undefined2 *)(*(int *)((int)this + 0x18) + 2) = 1;
  *(uint *)(*(int *)((int)this + 0x18) + 4) = *puVar7;
  *(undefined2 *)(*(int *)((int)this + 0x18) + 0xe) = 0x10;
  iVar1 = *(int *)((int)this + 0x18);
  *(short *)(iVar1 + 0xc) =
       (short)((int)((uint)*(ushort *)(iVar1 + 0xe) * (uint)*(ushort *)(iVar1 + 2)) >> 3);
  iVar1 = *(int *)((int)this + 0x18);
  *(uint *)(iVar1 + 8) = (uint)*(ushort *)(iVar1 + 0xc) * *(int *)(iVar1 + 4);
  *(undefined2 *)(*(int *)((int)this + 0x18) + 0x10) = 0;
  *(undefined4 *)((int)this + 0x30) = 0xc;
  *(uint **)((int)this + 0x34) = puVar7 + 5;
  uVar2 = puVar7[4];
  *(uint *)((int)this + 0x2c) = uVar2;
  if (uVar2 < 0x100001) {
    *(uint *)((int)this + 0x28) = (uVar2 * 0xf0a) / *(uint *)(*(int *)((int)this + 0x18) + 8);
  }
  else {
    *(uint *)((int)this + 0x28) = (uVar2 / *(uint *)(*(int *)((int)this + 0x18) + 8)) * 0xf0a;
  }
  if (*(int *)this == 0) {
    lpString1 = operator_new(6);
    *(LPSTR *)this = lpString1;
    lstrcpyA(lpString1,s_A_CVG_21114564);
  }
  uVar4 = sub_21109760(DAT_211155b4,s_AAL_codec_21114114,s_Input_file_types_21114544,*(LPCSTR *)this
                      );
  *(undefined4 *)((int)this + 0x38) = uVar4;
  pvVar5 = operator_new(0x18);
  *(void **)((int)this + 0x1c) = pvVar5;
  *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 2;
  *(undefined4 *)((int)pvVar5 + 8) = 0;
  *(undefined4 *)(*(int *)((int)this + 0x1c) + 0xc) = *(undefined4 *)((int)this + 0x2c);
  *(uint *)(*(int *)((int)this + 0x1c) + 0x14) = (uint)(*(short *)((int)puVar7 + 10) == 0);
  puVar6 = operator_new(0x10);
  *(uint **)((int)this + 0x24) = puVar6;
  *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 4;
  *puVar6 = (uint)*(ushort *)((int)puVar7 + 6);
  *(uint *)(*(int *)((int)this + 0x24) + 8) = (uint)(ushort)puVar7[3];
  *(uint *)(*(int *)((int)this + 0x24) + 0xc) = (uint)*(ushort *)((int)puVar7 + 0xe);
  *(uint *)(*(int *)((int)this + 0x24) + 4) = (uint)(ushort)puVar7[2];
  return 0;
}

