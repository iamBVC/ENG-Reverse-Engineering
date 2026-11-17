/* sub_410330 @ 00410330   248 bytes */

void sub_410330(void)

{
  undefined4 uVar1;
  
  if (DAT_00583420 != 0) {
    uVar1 = sub_405720(*(undefined4 *)(DAT_00583420 + 0xc),0);
    sub_405800(s_DisplayDevice_00571784,uVar1);
  }
  if (DAT_00583424 != 0) {
    uVar1 = sub_405720(*(undefined4 *)(DAT_00583424 + 0xc),0);
    sub_405800(s_D3DDevice_00571778,uVar1);
    if ((DAT_00583424 != 0) && (*(char *)(DAT_00583424 + 0x10) != '\0')) {
      if (DAT_00583428 != 0) {
        sub_405870(s_SoftwareScreenBPP_00571748,*(undefined4 *)(DAT_00583428 + 0xc),0);
      }
      if (DAT_0058342c == 0) {
        return;
      }
      sub_405870(s_SoftwareScreenW_00571738,*(undefined4 *)(DAT_0058342c + 0xc),0);
      sub_405870(s_SoftwareScreenH_00571728,*(undefined4 *)(DAT_0058342c + 0x10),0);
      return;
    }
  }
  if (DAT_00583428 != 0) {
    sub_405870(s_ScreenBPP_0057176c,*(undefined4 *)(DAT_00583428 + 0xc),0);
  }
  if (DAT_0058342c != 0) {
    sub_405870(s_ScreenW_00571764,*(undefined4 *)(DAT_0058342c + 0xc),0);
    sub_405870(s_ScreenH_0057175c,*(undefined4 *)(DAT_0058342c + 0x10),0);
  }
  return;
}

