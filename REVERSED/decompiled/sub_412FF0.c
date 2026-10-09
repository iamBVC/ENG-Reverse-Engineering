/* sub_412FF0 @ 00412ff0   183 bytes */

bool sub_412FF0(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = *(uint *)(param_2 + 4);
  if (((byte)uVar1 & 0x41) != 0x41) {
    return false;
  }
  iVar2 = *(int *)(param_2 + 0xc);
  if (((iVar2 != 8) && (iVar2 != 0x10)) && (iVar2 != 0x20)) {
    return false;
  }
  if ((uVar1 & 0x2000) != 0) {
    return false;
  }
  if ((uVar1 & 0x80) != 0) {
    return false;
  }
  if (*param_1 == 0) {
    return true;
  }
  iVar2 = sub_412E50(param_1[4],param_1[5],param_1[6],param_1[7],5,5,5,1);
  iVar3 = sub_412E50(*(undefined4 *)(param_2 + 0x10),*(undefined4 *)(param_2 + 0x14),
                     *(undefined4 *)(param_2 + 0x18),*(undefined4 *)(param_2 + 0x1c),5,5,5,1);
  if (iVar3 < iVar2) {
    return true;
  }
  if (iVar2 < iVar3) {
    return false;
  }
  return *(uint *)(param_2 + 0xc) < (uint)param_1[3];
}

