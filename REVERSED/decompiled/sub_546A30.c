/* sub_546A30 @ 00546a30   277 bytes */

undefined4 sub_546A30(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iStack_14;
  char *pcStack_10;
  
  if (DAT_005834dc == 0) {
    return 0;
  }
  if (*(int *)(&DAT_006d946c + param_2 * 4) != 0) {
    pcStack_10 = s_Stream__Music_is_already_playing_00578e58;
    iStack_14 = 0x546a63;
    sub_426500();
    return 0;
  }
  pcStack_10 = (char *)param_1;
  iStack_14 = 0;
  iStack_14 = sub_415690();
  if (iStack_14 == 0) {
    return 0;
  }
  if (param_3 == 0) {
    pcStack_10 = (char *)0x0;
  }
  else {
    pcStack_10 = (char *)0x40;
  }
  iVar3 = param_2 * 0x18;
  iVar1 = _AAL_LoadFile_8();
  *(int *)(&DAT_006d940c + iVar3) = iVar1;
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = _AAL_GetDataSize_4(iVar1);
  *(undefined4 *)(&DAT_006d93f8 + iVar3) = uVar2;
  iVar1 = _AAL_GetSampleRate_4(*(undefined4 *)(&DAT_006d940c + iVar3));
  iVar1 = iVar1 << 0xc;
  *(short *)(&DAT_006d93fc + iVar3) =
       ((short)(iVar1 / 0xac44) + (short)(iVar1 >> 0x1f)) -
       (short)((longlong)iVar1 * 0x2f8df18f >> 0x3f);
  *(undefined2 *)(&DAT_006d93fe + iVar3) = 0x7f;
  *(undefined2 *)(&DAT_006d9400 + iVar3) = 0x2400;
  *(undefined2 *)(&DAT_006d9402 + iVar3) = 1;
  iVar1 = sub_5487A0(&DAT_006d93f8 + iVar3,0,0x2400,&iStack_14);
  *(int *)(&DAT_006d946c + param_2 * 4) = iVar1;
  if (iVar1 == 0) {
    return 0;
  }
  sub_5489C0(DAT_006d9498 + 0x10,iVar1);
  return 1;
}

