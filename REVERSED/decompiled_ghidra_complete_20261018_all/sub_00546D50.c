/* sub_546D50 @ 00546d50   81 bytes */

void sub_546D50(void)

{
  uint *puVar1;
  int iVar2;
  
  if (DAT_006d9498 != 0) {
    iVar2 = *(int *)(DAT_006d9498 + 0x48);
    if (iVar2 != 0) {
      puVar1 = (uint *)(*(int *)(DAT_006d9498 + 0x44) + 0x3c);
      do {
        if (((puVar1[-0xb] != 0) && ((*puVar1 & 0x2400) == 0x2400)) && (puVar1[0x13] != 0)) {
          _AAL_ResumeVoice_4(*(undefined4 *)(puVar1[0x13] + 0x14));
        }
        puVar1 = puVar1 + 0x27;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  return;
}

