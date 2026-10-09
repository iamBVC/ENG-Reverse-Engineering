/* sub_5689BA @ 005689ba   144 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_5689BA(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  
  lVar3 = CONCAT44(param_3,param_2);
  if (((*(uint *)(param_1 + 0xc) & 0x83) == 0) ||
     (((param_4 != 0 && (param_4 != 1)) && (param_4 != 2)))) {
    _DAT_006da364 = 0x16;
  }
  else {
    *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffef;
    if (param_4 == 1) {
      lVar2 = sub_568A4A(param_1);
      lVar3 = lVar2 + lVar3;
      param_4 = 0;
    }
    sub_5638F0(param_1);
    uVar1 = *(uint *)(param_1 + 0xc);
    if ((uVar1 & 0x80) == 0) {
      if ((((uVar1 & 1) != 0) && ((uVar1 & 8) != 0)) && ((uVar1 & 0x400) == 0)) {
        *(undefined4 *)(param_1 + 0x18) = 0x200;
      }
    }
    else {
      *(uint *)(param_1 + 0xc) = uVar1 & 0xfffffffc;
    }
    lVar3 = sub_56BBB3(*(undefined4 *)(param_1 + 0x10),lVar3,param_4);
    if (lVar3 != -1) {
      return 0;
    }
  }
  return 0xffffffff;
}

