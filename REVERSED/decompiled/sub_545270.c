/* sub_545270 @ 00545270   210 bytes */

void sub_545270(void)

{
  sub_545190(0x36000);
  sub_547100(DAT_006d9494);
  DAT_006d9494 = 0;
  if (DAT_006d9498 != 0) {
    if (*(int *)(DAT_006d9498 + 0x20) != 0) {
      sub_562941(*(int *)(DAT_006d9498 + 0x20));
      *(undefined4 *)(DAT_006d9498 + 0x20) = 0;
    }
    if (*(int *)(DAT_006d9498 + 0x44) != 0) {
      sub_5628BC(*(int *)(DAT_006d9498 + 0x44));
      *(undefined4 *)(DAT_006d9498 + 0x44) = 0;
    }
    if (DAT_006d9498 != 0) {
      sub_562941(DAT_006d9498);
      DAT_006d9498 = 0;
    }
  }
  if (DAT_006d949c != 0) {
    if (*(int *)(DAT_006d949c + 0x24) != 0) {
      sub_562941(*(int *)(DAT_006d949c + 0x24));
      *(undefined4 *)(DAT_006d949c + 0x24) = 0;
    }
    if (*(int *)(DAT_006d949c + 0x58) != 0) {
      sub_5628BC(*(int *)(DAT_006d949c + 0x58));
      *(undefined4 *)(DAT_006d949c + 0x58) = 0;
    }
    if (DAT_006d949c != 0) {
      sub_562941(DAT_006d949c);
      DAT_006d949c = 0;
    }
  }
  return;
}

