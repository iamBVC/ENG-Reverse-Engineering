/* sub_5460A0 @ 005460a0   30 bytes */

void sub_5460A0(undefined4 param_1)

{
  undefined4 uVar1;
  
  if (DAT_006d9490 != 0) {
    uVar1 = _AAL_SetSpeakerMode_4(param_1);
    *(undefined4 *)(DAT_006d9490 + 0x58) = uVar1;
  }
  return;
}

