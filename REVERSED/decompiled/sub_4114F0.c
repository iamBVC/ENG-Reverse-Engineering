/* sub_4114F0 @ 004114f0   300 bytes */

void sub_4114F0(undefined4 param_1,int param_2,int param_3,int param_4,undefined1 param_5)

{
  DAT_00583420 = param_1;
  DAT_00583424 = param_2;
  DAT_00583428 = param_3;
  DAT_0058342c = param_4;
  DAT_00583430 = param_5;
  if ((param_2 != 0) && (*(char *)(param_2 + 0x10) != '\0')) {
    if (param_3 != 0) {
      DAT_00583440 = *(undefined4 *)(param_3 + 0xc);
    }
    if (param_4 != 0) {
      DAT_00583444 = *(undefined4 *)(param_4 + 0xc);
      DAT_00583448 = *(undefined4 *)(param_4 + 0x10);
    }
    sub_4057C0(s_ScreenBPP_0057176c,0x41800000,0);
    DAT_00583434 = __ftol();
    sub_4057C0(s_ScreenW_00571764,0x44200000,0);
    DAT_00583438 = __ftol();
    sub_4057C0(s_ScreenH_0057175c,0x43f00000,0);
    DAT_0058343c = __ftol();
    return;
  }
  if (param_3 != 0) {
    DAT_00583434 = *(undefined4 *)(param_3 + 0xc);
  }
  if (param_4 != 0) {
    DAT_00583438 = *(undefined4 *)(param_4 + 0xc);
    DAT_0058343c = *(undefined4 *)(param_4 + 0x10);
  }
  sub_4057C0(s_SoftwareScreenBPP_00571748,0x41800000,0);
  DAT_00583440 = __ftol();
  sub_4057C0(s_SoftwareScreenW_00571738,0x43a00000,0);
  DAT_00583444 = __ftol();
  sub_4057C0(s_SoftwareScreenH_00571728,0x43480000,0);
  DAT_00583448 = __ftol();
  return;
}

