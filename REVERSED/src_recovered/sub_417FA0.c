/* Original groove.exe 00417FA0-00418014: display the remaining menu timeout.
 * The assembly stores timeGetTime's full DWORD at 005839D0 and formats into
 * the eight-byte BSS buffer at 00583988. Ghidra lost the latter's symbol and
 * labelled the call to 00418050 as an unresolved register artifact.
 */
uint sub_417FA0(void)
{
  DWORD now;
  uint elapsed;

  now = timeGetTime();
  sub_562717((char *)DAT_00583988, DAT_00570300,
             0xf - (now - (uint)DAT_005839d0) / 1000);
  DAT_00571DE8 = (int)DAT_00583988;
  elapsed = timeGetTime() - (uint)DAT_005839d0;
  if (elapsed > 15000) {
    if (DAT_00571e3c == 1)
      sub_418020();
    else
      sub_418050();
    return 0;
  }
  return elapsed;
}

