/* Selected Ghidra export at 00418d00. */

undefined4 sub_418D00(void)

{
  int *piVar1;
  
  for (piVar1 = DAT_00582260; (*piVar1 != 0 || (piVar1[1] == 0)); piVar1 = (int *)*piVar1) {
    sub_40ECD0(piVar1);
    sub_419A60(piVar1);
    sub_40F290(piVar1,0,0xff,1000);
  }
  sub_418C10();
  return 0;
}

