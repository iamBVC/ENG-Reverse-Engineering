/* sub_546B50 @ 00546b50   22 bytes */

undefined4 sub_546B50(int param_1)

{
  if (*(int *)(&DAT_006d946c + param_1 * 4) != 0) {
    return *(undefined4 *)(*(int *)(&DAT_006d946c + param_1 * 4) + 0x10);
  }
  return 0;
}

