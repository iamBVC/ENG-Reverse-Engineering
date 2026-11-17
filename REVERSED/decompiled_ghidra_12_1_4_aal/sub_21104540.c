/* sub_21104540 @ 21104540   430 bytes */

undefined4 * __thiscall sub_21104540(void *this,int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 local_10 [4];
  
  *(undefined4 **)((int)this + 0x10) = (undefined4 *)((int)this + 8);
  *(undefined4 *)((int)this + 8) = (undefined4 *)((int)this + 0xc);
  *(undefined4 *)((int)this + 0xc) = 0;
  *(int **)((int)this + 0x1c) = (int *)((int)this + 0x14);
  *(undefined4 *)((int)this + 0x18) = 0;
  *(int *)((int)this + 0x14) = (int)this + 0x18;
  *(undefined ***)this = &PTR_sub_211046F0_21112338;
  *(undefined4 *)((int)this + 0x48) = 0;
  *(undefined4 *)((int)this + 0xcc) = 4;
  *(undefined4 *)((int)this + 0xa8) = 0x80;
  *(undefined4 *)((int)this + 0x84) = 0;
  *(undefined4 *)((int)this + 0x88) = 0;
  *(undefined4 *)((int)this + 0xb4) = 0;
  *(undefined4 *)((int)this + 0xb8) = 0;
  *(undefined4 *)((int)this + 0x60) = 0;
  *(undefined4 *)((int)this + 0x74) = 0;
  *(undefined4 *)((int)this + 0x68) = 0;
  *(undefined4 *)((int)this + 0x7c) = 0;
  *(undefined4 *)((int)this + 0xb0) = 0;
  *(undefined4 *)((int)this + 0xac) = 0;
  *(undefined4 *)((int)this + 0x58) = 0;
  *(undefined4 *)((int)this + 4) = 0;
  puVar4 = (undefined4 *)sub_211011A0((void *)0x0,local_10);
  uVar1 = puVar4[1];
  uVar2 = puVar4[2];
  uVar3 = puVar4[3];
  *(undefined4 *)((int)this + 0xbc) = *puVar4;
  *(undefined4 *)((int)this + 0xc0) = uVar1;
  *(undefined4 *)((int)this + 0xc4) = uVar2;
  *(undefined4 *)((int)this + 200) = uVar3;
  *(undefined4 *)((int)this + 0x78) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)((int)this + 0x44) = *(undefined4 *)(param_1 + 4);
  *(uint *)((int)this + 0xcc) = *(uint *)((int)this + 0xcc) | *(uint *)(param_1 + 0xc) & 0xffff0000;
  *(undefined4 *)((int)this + 0x30) = 0;
  *(undefined4 *)((int)this + 0x34) = 0;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)((int)this + 0x3c) = 0;
  *(undefined4 *)((int)this + 0x40) = 0;
  puVar4 = _AAL_GetDeviceInfo_8(1,*(int *)((int)this + 0x44));
  if (puVar4 != (undefined4 *)0x0) {
    *(undefined4 *)((int)this + 0x34) = puVar4[1];
    *(undefined4 *)((int)this + 0x38) = puVar4[2];
    *(undefined4 *)((int)this + 0x3c) = puVar4[3];
    *(undefined4 *)((int)this + 0x40) = puVar4[4];
    puVar4[5] = 1;
  }
  if (*(short *)(param_1 + 0x14) == 1) {
    *(undefined4 *)((int)this + 0x20) = *(undefined4 *)(param_1 + 0x14);
    *(undefined4 *)((int)this + 0x24) = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 *)((int)this + 0x28) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)((int)this + 0x2c) = *(undefined4 *)(param_1 + 0x20);
    if ((((*(short *)((int)this + 0x20) != 1) || (*(ushort *)((int)this + 0x22) == 0)) ||
        (2 < *(ushort *)((int)this + 0x22))) ||
       ((*(short *)((int)this + 0x2e) != 8 && (*(short *)((int)this + 0x2e) != 0x10)))) {
      AAL_SetError(s_Unsupported_PCM_data_format__21114378);
      return this;
    }
  }
  else {
    *(undefined2 *)((int)this + 0x20) = 1;
    *(undefined2 *)((int)this + 0x22) = 2;
    *(undefined4 *)((int)this + 0x24) = 0xac44;
    *(undefined2 *)((int)this + 0x2c) = 4;
    *(undefined2 *)((int)this + 0x2e) = 0x10;
    *(uint *)((int)this + 0xcc) = *(uint *)((int)this + 0xcc) | 1;
  }
  return this;
}

