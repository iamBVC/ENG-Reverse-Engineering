/* sub_546A30 @ 00546a30   277 bytes */

undefined4 sub_546A30(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  if (DAT_005834dc == 0) {
    return 0;
  }
  if (*(int *)(&DAT_006d946c + param_2 * 4) != 0) {
    sub_426500(s_Stream__Music_is_already_playing_00578e58);
    return 0;
  }
  iVar1 = sub_415690(0,param_1);
  if (iVar1 == 0) {
    return 0;
  }
  if (param_3 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0x40;
  }
  iVar2 = param_2 * 0x18;
  iVar1 = _AAL_LoadFile_8(iVar1,uVar3);
  *(int *)(&DAT_006d940c + iVar2) = iVar1;
  if (iVar1 == 0) {
    return 0;
  }
  uVar3 = _AAL_GetDataSize_4(iVar1);
  *(undefined4 *)(&DAT_006d93f8 + iVar2) = uVar3;
  iVar1 = _AAL_GetSampleRate_4(*(undefined4 *)(&DAT_006d940c + iVar2));
  iVar1 = iVar1 << 0xc;
  *(short *)(&DAT_006d93fc + iVar2) =
       ((short)(iVar1 / 0xac44) + (short)(iVar1 >> 0x1f)) -
       (short)((longlong)iVar1 * 0x2f8df18f >> 0x3f);
  *(undefined2 *)(&DAT_006d93fe + iVar2) = 0x7f;
  *(undefined2 *)(&DAT_006d9400 + iVar2) = 0x2400;
  *(undefined2 *)(&DAT_006d9402 + iVar2) = 1;
  iVar1 = sub_5487A0(&DAT_006d93f8 + iVar2,0,0x2400,&local_4);
  *(int *)(&DAT_006d946c + param_2 * 4) = iVar1;
  if (iVar1 == 0) {
    return 0;
  }
  sub_5489C0(DAT_006d9498 + 0x10,iVar1);
  return 1;
}

