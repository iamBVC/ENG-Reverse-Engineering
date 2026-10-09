/* sub_54DE00 @ 0054de00   192 bytes */

void sub_54DE00(int param_1,int param_2)

{
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 6) = 0;
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0xc) = 0xfffe;
  *(undefined2 *)(*(int *)(param_1 + 0xc0) + 0x10) = 0xffff;
  DAT_00586424 = 0xffff0000;
  DAT_0058641c = 0;
  if ((*(byte *)(param_2 + 0x20) & 4) == 0) {
    *(uint *)(param_1 + 0x30) = *(uint *)(param_2 + 0xc) & 0xfffff00;
    *(uint *)(param_1 + 0x34) = *(uint *)(param_2 + 0x10) & 0xfffff00;
    *(uint *)(param_1 + 0x38) = *(uint *)(param_2 + 0x14) & 0xfffff00;
    *(uint *)(param_1 + 0x24) = (*(uint *)(param_2 + 0x1c) & 0xff0) << 0xc;
  }
  sub_41E1C0(0);
  if (((DAT_005846e4 == 3) && (*(int *)(DAT_00584644 + 0x58) != 0)) &&
     (*(int *)(DAT_00584644 + 0x58) != DAT_00586430)) {
    sub_546CC0();
    DAT_00586430 = *(int *)(DAT_00584644 + 0x58);
    sub_546B70(DAT_00586430,0);
  }
  return;
}

