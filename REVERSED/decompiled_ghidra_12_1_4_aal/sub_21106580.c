/* sub_21106580 @ 21106580   287 bytes */

undefined4 __thiscall sub_21106580(void *this,int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined2 *puVar2;
  void *pvVar3;
  LPSTR lpString1;
  undefined4 uVar4;
  
  if ((param_1 != 0) && (param_2 != 0)) {
    puVar2 = operator_new(0x12);
    *(undefined2 **)((int)this + 0x18) = puVar2;
    *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 1;
    *puVar2 = 1;
    *(undefined2 *)(*(int *)((int)this + 0x18) + 2) = 1;
    *(undefined4 *)(*(int *)((int)this + 0x18) + 4) = 0xac44;
    *(undefined2 *)(*(int *)((int)this + 0x18) + 0xe) = 0x10;
    iVar1 = *(int *)((int)this + 0x18);
    *(short *)(iVar1 + 0xc) =
         (short)((int)((uint)*(ushort *)(iVar1 + 0xe) * (uint)*(ushort *)(iVar1 + 2)) >> 3);
    iVar1 = *(int *)((int)this + 0x18);
    *(uint *)(iVar1 + 8) = (uint)*(ushort *)(iVar1 + 0xc) * *(int *)(iVar1 + 4);
    *(undefined2 *)(*(int *)((int)this + 0x18) + 0x10) = 0;
    *(int *)((int)this + 0x30) = param_3;
    *(int *)((int)this + 0x34) = param_1;
    *(int *)((int)this + 0x2c) = param_2;
    *(undefined4 *)((int)this + 0x28) = 0;
    pvVar3 = operator_new(0x18);
    *(void **)((int)this + 0x1c) = pvVar3;
    *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 2;
    *(undefined4 *)((int)pvVar3 + 8) = 0;
    *(undefined4 *)(*(int *)((int)this + 0x1c) + 0xc) = *(undefined4 *)((int)this + 0x2c);
    *(undefined4 *)(*(int *)((int)this + 0x1c) + 0x14) = 1;
    lpString1 = operator_new(6);
    *(LPSTR *)this = lpString1;
    lstrcpyA(lpString1,&DAT_21114558);
    lstrcatA(*(LPSTR *)this,&DAT_211144d4 + param_3 * 4);
    uVar4 = sub_21109760(DAT_211155b4,s_AAL_codec_21114114,s_Input_file_types_21114544,
                         *(LPCSTR *)this);
    *(undefined4 *)((int)this + 0x38) = uVar4;
    return 0;
  }
  return 1;
}

