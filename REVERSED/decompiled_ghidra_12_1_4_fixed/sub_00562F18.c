/* sub_562F18 @ 00562f18   45 bytes */

void sub_562F18(code *UNRECOVERED_JUMPTABLE)

{
  ExceptionList = *(void **)ExceptionList;
                    /* WARNING: Could not recover jumptable at 0x00562f43. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

