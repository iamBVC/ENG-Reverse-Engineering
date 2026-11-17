/* _AAL_SetSpeakerMode@4 @ 21101f20   25 bytes */

undefined4 _AAL_SetSpeakerMode_4(int param_1)

{
  undefined4 uVar1;
  
                    /* 0x1f20  68  _AAL_SetSpeakerMode@4 */
  uVar1 = 0;
  if (DAT_211155ac != (void *)0x0) {
    uVar1 = sub_211047F0(DAT_211155ac,param_1);
  }
  return uVar1;
}

