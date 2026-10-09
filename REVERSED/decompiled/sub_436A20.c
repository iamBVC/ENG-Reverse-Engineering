/* sub_436A20 @ 00436a20   43 bytes */

undefined2 sub_436A20(char param_1)

{
  if (param_1 == '#') {
    return 3;
  }
  if (param_1 == ' ') {
    return 10;
  }
  return *(undefined2 *)(DAT_006da354 + 4 + param_1 * 8);
}

