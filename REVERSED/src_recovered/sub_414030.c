/* Hand reconstruction of 0x00414030: append the NUL-terminated text in param_3
   to a copy of the string-like object in param_2, then hand the result to the
   caller's object in param_1 and release the temporary's buffer through its
   one-byte reference count.  Ghidra dropped the ECX object on both sub_414160
   calls and left the SEH slot as pvStack_c, which no declaration covers. */

undefined1 * sub_414030(undefined1 *param_1,undefined1 *param_2,char *param_3)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  undefined1 local_1c [4];
  int local_18;
  int local_14;
  undefined4 local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;

  local_4 = 0xffffffff;
  puStack_8 = &LAB_0056d898;
  local_c = ExceptionList;
  local_1c[0] = *param_2;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  ExceptionList = &local_c;
  sub_414160((int)&local_1c,(int)param_2,0,DAT_0056e1e0);
  uVar3 = 0xffffffff;
  pcVar5 = param_3;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar2 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar2 != '\0');
  uVar3 = ~uVar3 - 1;
  local_4 = 0;
  if (-local_14 - 1U <= uVar3) {
    sub_56D0A0();
  }
  if (uVar3 != 0) {
    iVar1 = local_14 + uVar3;
    cVar2 = sub_413F10((int)&local_1c,iVar1,0);
    if (cVar2 != '\0') {
      pcVar5 = (char *)(local_14 + local_18);
      for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined4 *)pcVar5 = *(undefined4 *)param_3;
        param_3 = param_3 + 4;
        pcVar5 = pcVar5 + 4;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *pcVar5 = *param_3;
        param_3 = param_3 + 1;
        pcVar5 = pcVar5 + 1;
      }
      *(undefined1 *)(local_18 + iVar1) = 0;
      local_14 = iVar1;
    }
  }
  *param_1 = local_1c[0];
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  sub_414160((int)param_1,(int)&local_1c,0,DAT_0056e1e0);
  if (local_18 != 0) {
    cVar2 = *(char *)(local_18 + -1);
    if ((cVar2 != '\0') && (cVar2 != -1)) {
      *(char *)(local_18 + -1) = cVar2 + -1;
      ExceptionList = local_c;
      return param_1;
    }
    sub_562941(local_18 + -1);
  }
  ExceptionList = local_c;
  return param_1;
}
