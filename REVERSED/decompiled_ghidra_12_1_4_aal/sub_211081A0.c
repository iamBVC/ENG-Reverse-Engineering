/* sub_211081A0 @ 211081a0   215 bytes */

undefined4 __thiscall
sub_211081A0(void *this,int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int local_24 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (*(int *)((int)this + 0x14) == 0) {
    piVar4 = local_24;
    for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar4 = 0;
      piVar4 = piVar4 + 1;
    }
    local_24[0] = 0x24;
    switch(*(undefined4 *)((int)this + 0x30)) {
    case 1:
      local_24[2] = *(int *)((int)this + 0x2c);
      break;
    case 2:
      local_24[2] = (uint)*(ushort *)(*(int *)((int)this + 0x18) + 2) * *(int *)((int)this + 0x40) *
                    0x40;
      break;
    default:
      local_24[2] = 0;
      break;
    case 0xc:
    case 0x15:
      local_24[2] = (*(uint *)((int)this + 0x2c) >> 4) * 0x38;
    }
    local_14 = *(undefined4 *)((int)this + 0x18);
    local_10 = param_2;
    local_8 = param_4;
    local_4 = param_5;
    local_c = param_3;
    local_24[1] = param_6;
    puVar1 = sub_21107D10(this,param_1,(uint)local_24,(undefined4 *)0x4);
    *(undefined4 **)((int)this + 0x14) = puVar1;
  }
  uVar2 = sub_211080C0(*(int **)((int)this + 0x14));
  if (uVar2 != 0) {
    return *(undefined4 *)(uVar2 + 4);
  }
  return 0;
}

