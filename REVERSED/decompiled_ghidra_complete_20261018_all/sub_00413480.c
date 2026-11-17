/* sub_413480 @ 00413480 50 bytes */
/* Selected Ghidra export at 00413480. */

int sub_413480(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x10) != *(char *)(param_2 + 0x10)) {
    return (-(uint)(*(char *)(param_1 + 0x10) != '\0') & 0xfffffffe) + 1;
  }
  if (*(char *)(param_1 + 0x11) != *(char *)(param_2 + 0x11)) {
    return (-(uint)(*(char *)(param_1 + 0x11) != '\0') & 2) - 1;
  }
  return 0;
}

