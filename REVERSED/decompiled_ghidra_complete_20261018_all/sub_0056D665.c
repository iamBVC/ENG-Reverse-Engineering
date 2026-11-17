/* sub_56D665 @ 0056D665 13 bytes */
/* Selected Ghidra export at 0056d665. */

char * __fastcall sub_56D665(int param_1)

{
  char *pcVar1;
  
  pcVar1 = *(char **)(param_1 + 4);
  if (pcVar1 == (char *)0x0) {
    pcVar1 = "Unknown exception";
  }
  return pcVar1;
}

