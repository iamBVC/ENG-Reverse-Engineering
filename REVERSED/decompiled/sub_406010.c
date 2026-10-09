/* sub_406010 @ 00406010   142 bytes */

void sub_406010(void)

{
  if (-1 < *(int *)PTR_DAT_00570340) {
    *(undefined4 *)PTR_DAT_00570340 = 0xffffffff;
  }
  if (*(int *)(PTR_DAT_00570340 + 0xc) != 0) {
    sub_562941(*(int *)(PTR_DAT_00570340 + 0xc));
    *(undefined4 *)(PTR_DAT_00570340 + 0xc) = 0;
  }
  if (*(int *)(PTR_DAT_00570340 + 0x10) != 0) {
    sub_562941(*(int *)(PTR_DAT_00570340 + 0x10));
    *(undefined4 *)(PTR_DAT_00570340 + 0x10) = 0;
  }
  sub_5628EB(DAT_0058384c);
  DAT_0058384c = 0;
  sub_5628BC(DAT_0057f8c4);
  sub_5628BC(DAT_0057f854);
  sub_41A440(0xc0);
  return;
}

