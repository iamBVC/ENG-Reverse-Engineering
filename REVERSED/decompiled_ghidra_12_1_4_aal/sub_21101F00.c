/* _AAL_GetSpeakerMode@0 @ 21101f00   18 bytes */

undefined4 * _AAL_GetSpeakerMode_0(void)

{
  undefined4 *puVar1;
  
                    /* 0x1f00  39  _AAL_GetSpeakerMode@0 */
  if (DAT_211155ac != 0) {
    puVar1 = sub_211047B0(DAT_211155ac);
    return puVar1;
  }
  return (undefined4 *)0x0;
}

