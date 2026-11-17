/* sub_21106AD0 @ 21106ad0   436 bytes */

undefined4 __thiscall sub_21106AD0(void *this,int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined2 *puVar4;
  undefined4 uVar5;
  void *pvVar6;
  uint uVar7;
  
  iVar3 = param_1;
  uVar7 = *(uint *)(param_1 + 0x10);
  if ((uVar7 != 0) &&
     (((uVar7 & 0xff0000 | uVar7 >> 0x10) >> 8 | (uVar7 << 0x10 | uVar7 & 0xff00) << 8) < 0x186a1))
  {
    uVar7 = *(uint *)(param_1 + 0xc);
    param_1._3_1_ = (undefined1)(uVar7 >> 0x18);
    param_1._2_1_ = (undefined1)(uVar7 >> 0x10);
    uVar7 = (uint)CONCAT11(param_1._2_1_,param_1._3_1_) | (uVar7 << 0x10 | uVar7 & 0xff00) << 8;
    if (uVar7 != 0) {
      if (*(int *)((int)this + 0x18) != 0) {
        return 0;
      }
      puVar4 = operator_new(0x12);
      *(undefined2 **)((int)this + 0x18) = puVar4;
      *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 1;
      *puVar4 = 1;
      *(undefined2 *)(*(int *)((int)this + 0x18) + 2) = 1;
      uVar1 = *(uint *)(iVar3 + 0x10);
      *(uint *)(*(int *)((int)this + 0x18) + 4) =
           (uVar1 & 0xff0000 | uVar1 >> 0x10) >> 8 | (uVar1 << 0x10 | uVar1 & 0xff00) << 8;
      *(undefined2 *)(*(int *)((int)this + 0x18) + 0xe) = 0x10;
      iVar2 = *(int *)((int)this + 0x18);
      *(short *)(iVar2 + 0xc) =
           (short)((int)((uint)*(ushort *)(iVar2 + 0xe) * (uint)*(ushort *)(iVar2 + 2)) >> 3);
      iVar2 = *(int *)((int)this + 0x18);
      *(uint *)(iVar2 + 8) = (uint)*(ushort *)(iVar2 + 0xc) * *(int *)(iVar2 + 4);
      *(undefined2 *)(*(int *)((int)this + 0x18) + 0x10) = 0;
      *(undefined4 *)((int)this + 0x30) = 0x15;
      *(int *)((int)this + 0x34) = iVar3 + 0x30;
      *(uint *)((int)this + 0x2c) = uVar7;
      if (uVar7 < 0x100001) {
        *(uint *)((int)this + 0x28) = (uVar7 * 0xf0a) / *(uint *)(*(int *)((int)this + 0x18) + 8);
      }
      else {
        *(uint *)((int)this + 0x28) = (uVar7 / *(uint *)(*(int *)((int)this + 0x18) + 8)) * 0xf0a;
      }
      uVar5 = sub_21109760(DAT_211155b4,s_AAL_codec_21114114,s_Input_file_types_21114544,
                           *(LPCSTR *)this);
      *(undefined4 *)((int)this + 0x38) = uVar5;
      pvVar6 = operator_new(0x18);
      *(uint *)((int)this + 4) = *(uint *)((int)this + 4) | 2;
      *(void **)((int)this + 0x1c) = pvVar6;
      *(undefined4 *)((int)pvVar6 + 8) = 0;
      *(uint *)(*(int *)((int)this + 0x1c) + 0xc) = uVar7;
      *(uint *)(*(int *)((int)this + 0x1c) + 0x14) =
           ((ushort)~*(ushort *)(iVar3 + 0x40) & 0x200) >> 9;
      return 0;
    }
  }
  return 1;
}

