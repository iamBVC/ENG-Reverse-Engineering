/* sub_21106750 @ 21106750   425 bytes */

undefined4 __thiscall sub_21106750(void *this,int param_1)

{
  int iVar1;
  uint uVar2;
  undefined2 *puVar3;
  void *pvVar4;
  LPSTR lpString1;
  undefined4 uVar5;
  int iVar6;
  
  iVar6 = param_1 + 0x2c;
  if (*(int *)(param_1 + 0x2c) == 0x20736461) {
    *(int *)((int)this + 0x24) = iVar6;
    iVar6 = param_1 + 0x3c;
  }
  if (*(int *)((int)this + 0x18) == 0) {
    puVar3 = operator_new(0x12);
    *(undefined2 **)((int)this + 0x18) = puVar3;
    *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 1;
    *puVar3 = 1;
    *(ushort *)(*(int *)((int)this + 0x18) + 2) = ((ushort)(*(uint *)(param_1 + 0x28) >> 1) & 1) + 1
    ;
    *(uint *)(*(int *)((int)this + 0x18) + 4) = (uint)*(ushort *)(param_1 + 0x24);
    *(ushort *)(*(int *)((int)this + 0x18) + 0xe) = (*(byte *)(param_1 + 0x28) & 1) * 8 + 8;
    iVar1 = *(int *)((int)this + 0x18);
    *(short *)(iVar1 + 0xc) =
         (short)((int)((uint)*(ushort *)(iVar1 + 0xe) * (uint)*(ushort *)(iVar1 + 2)) >> 3);
    iVar1 = *(int *)((int)this + 0x18);
    *(uint *)(iVar1 + 8) = (uint)*(ushort *)(iVar1 + 0xc) * *(int *)(iVar1 + 4);
    *(undefined2 *)(*(int *)((int)this + 0x18) + 0x10) = 0;
    *(undefined4 *)((int)this + 0x30) = 2;
    *(int *)((int)this + 0x34) = iVar6;
    iVar6 = *(int *)(param_1 + 8) * *(int *)(param_1 + 0x18) <<
            ((byte)(*(uint *)(param_1 + 0x28) >> 1) & 1);
    uVar2 = iVar6 * 0x11;
    *(uint *)((int)this + 0x2c) = uVar2;
    if (uVar2 < 0x100001) {
      *(uint *)((int)this + 0x28) =
           (uint)(iVar6 * 0xffaa) / *(uint *)(*(int *)((int)this + 0x18) + 8);
    }
    else {
      *(uint *)((int)this + 0x28) = (uVar2 / *(uint *)(*(int *)((int)this + 0x18) + 8)) * 0xf0a;
    }
    *(int *)((int)this + 0x3c) = *(int *)(param_1 + 8) + -1;
    *(int *)((int)this + 0x40) = *(int *)(param_1 + 0x18);
    pvVar4 = operator_new(0x18);
    *(void **)((int)this + 0x1c) = pvVar4;
    *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 2;
    *(uint *)((int)pvVar4 + 8) = *(uint *)(param_1 + 0x20) >> 0x10;
    *(uint *)(*(int *)((int)this + 0x1c) + 0xc) = *(uint *)(param_1 + 0x20) & 0xffff;
    iVar6 = *(int *)((int)this + 0x1c);
    if (*(int *)(iVar6 + 0xc) == 0) {
      *(undefined4 *)(iVar6 + 0x14) = 1;
      *(undefined4 *)(*(int *)((int)this + 0x1c) + 0xc) = *(undefined4 *)((int)this + 0x2c);
    }
    else {
      *(undefined4 *)(iVar6 + 0x14) = 0;
    }
    if (*(int *)this == 0) {
      lpString1 = operator_new(6);
      *(LPSTR *)this = lpString1;
      lstrcpyA(lpString1,s_A_ASF_2111455c);
    }
    uVar5 = sub_21109760(DAT_211155b4,s_AAL_codec_21114114,s_Input_file_types_21114544,
                         *(LPCSTR *)this);
    *(undefined4 *)((int)this + 0x38) = uVar5;
  }
  return 0;
}

