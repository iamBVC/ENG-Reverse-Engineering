/* sub_4388D0 @ 004388d0   433 bytes */

void sub_4388D0(undefined4 *param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  char cVar2;
  
  *param_2 = *param_1;
  if ((*(char *)(param_1 + 1) == '\0') || (DAT_00573d4c == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)(param_2 + 1) = uVar1;
  if ((*(char *)((int)param_1 + 5) == '\0') || (DAT_00573d4d == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)((int)param_2 + 5) = uVar1;
  if ((*(char *)((int)param_1 + 6) == '\0') || (DAT_00573d4e == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)((int)param_2 + 6) = uVar1;
  if ((*(char *)((int)param_1 + 7) == '\0') || (DAT_00573d4f == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)((int)param_2 + 7) = uVar1;
  if ((*(char *)(param_1 + 2) == '\0') || (DAT_00573d50 == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)(param_2 + 2) = uVar1;
  if ((*(char *)((int)param_1 + 9) == '\0') || (DAT_00573d51 == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)((int)param_2 + 9) = uVar1;
  if ((*(char *)((int)param_1 + 10) == '\0') || (DAT_00573d52 == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)((int)param_2 + 10) = uVar1;
  if ((*(char *)((int)param_1 + 0xb) == '\0') || (DAT_00573d53 == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)((int)param_2 + 0xb) = uVar1;
  if ((*(char *)(param_1 + 3) == '\0') || (DAT_00573d54 == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)(param_2 + 3) = uVar1;
  if ((*(char *)((int)param_1 + 0xd) == '\0') || (DAT_00573d55 == '\0')) {
    cVar2 = '\0';
  }
  else {
    cVar2 = '\x01';
  }
  *(char *)((int)param_2 + 0xd) = cVar2;
  if ((*(char *)((int)param_1 + 0xe) == '\0') || (DAT_00573d56 == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)((int)param_2 + 0xe) = uVar1;
  if ((*(char *)((int)param_1 + 0xf) == '\0') || (DAT_00573d57 == '\0')) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  *(undefined1 *)((int)param_2 + 0xf) = uVar1;
  param_2[4] = param_1[4];
  param_2[5] = param_1[5];
  param_2[6] = param_1[6];
  if (DAT_005833ea == '\0') {
    *(undefined1 *)((int)param_2 + 9) = 1;
  }
  if (*(char *)((int)param_2 + 9) != '\0') {
    *(undefined1 *)((int)param_2 + 0xb) = 0;
    *(undefined1 *)(param_2 + 3) = 0;
  }
  if (*(char *)(param_2 + 3) != '\0') {
    *(undefined1 *)((int)param_2 + 7) = 1;
    *(undefined1 *)((int)param_2 + 0xb) = 1;
  }
  if (cVar2 != '\0') {
    *(undefined1 *)((int)param_2 + 10) = 1;
  }
  return;
}

