/* sub_419BD0 @ 00419bd0   552 bytes */

undefined4 sub_419BD0(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  char *pcVar5;
  uint local_110;
  undefined1 local_10c;
  undefined1 local_108 [4];
  undefined1 local_104 [260];
  
  local_110 = DAT_0057228c;
  local_10c = DAT_00572290;
  if (param_1 == (int *)0x0) {
    sub_562717(local_104,s_InputDevice__s_00572234,&DAT_00582b50);
    pcVar5 = (char *)sub_405790(local_104,0,0);
    if (pcVar5 != (char *)0x0) {
      puVar4 = &DAT_00584758;
      while( true ) {
        _strncpy((char *)&local_110,pcVar5,4);
        iVar1 = sub_562769(&local_110,&DAT_0057224c,puVar4);
        if (iVar1 < 1) break;
        puVar4 = puVar4 + 1;
        pcVar5 = pcVar5 + 4;
        if (0x58478f < (int)puVar4) {
          _strncpy((char *)&local_110,pcVar5,2);
          local_110 = local_110 & 0xffffff;
          iVar1 = sub_562769(&local_110,&DAT_00572244,local_108);
          if (iVar1 < 1) {
            *(undefined1 *)(DAT_005fcf70 + 0xb) = 0x7f;
            return 1;
          }
          *(undefined1 *)(DAT_005fcf70 + 0xb) = local_108[0];
          return 1;
        }
      }
    }
  }
  else {
    sub_562717(local_104,s_InputDevice__s__s_00572278,param_1 + 0x34,param_1 + 0x20);
    iVar1 = sub_405790(local_104,0,0);
    if (iVar1 == 0) {
      return 0;
    }
    iVar2 = sub_562769(iVar1,s_X1__08X_Y1__08X_X2__08X_Y2__08X_00572254,param_1 + 0x17,
                       param_1 + 0x18,param_1 + 0x19,param_1 + 0x1a);
    if (iVar2 < 4) {
      return 0;
    }
    pcVar5 = (char *)(iVar1 + 0x30);
    iVar1 = 0;
    while( true ) {
      _strncpy((char *)&local_110,pcVar5,4);
      iVar2 = sub_562769(&local_110,&DAT_0057224c,param_1[0x1c] + iVar1);
      if (iVar2 < 1) break;
      iVar1 = iVar1 + 4;
      pcVar5 = pcVar5 + 4;
      if (0x37 < iVar1) {
        iVar1 = 1;
        piVar3 = DAT_00582260;
        while ((((int *)*piVar3 != (int *)0x0 || (piVar3[1] == 0)) && (piVar3 != param_1))) {
          iVar1 = iVar1 + 1;
          piVar3 = (int *)*piVar3;
        }
        _strncpy((char *)&local_110,pcVar5,2);
        local_110 = local_110 & 0xffffff;
        iVar2 = sub_562769(&local_110,&DAT_00572244,local_108);
        if (iVar2 < 1) {
          *(undefined1 *)(DAT_005fcf70 + 0xb + iVar1 * 0xc) = 0x7f;
          return 1;
        }
        *(undefined1 *)(DAT_005fcf70 + 0xb + iVar1 * 0xc) = local_108[0];
        return 1;
      }
    }
  }
  return 0;
}

