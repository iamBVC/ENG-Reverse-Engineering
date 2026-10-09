/* caseD_2d @ 00551a4b   62 bytes */

void switchD_00550e72::caseD_2d(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000014;
  int in_stack_00000018;
  
  if (*(int *)(in_stack_00000018 + 0x1c) == 0) {
    uVar1 = __ftol();
    *(undefined4 *)(in_stack_00000018 + 0x1c) = uVar1;
  }
  sub_54BBD0(in_stack_00000014,*(undefined4 *)(in_stack_00000018 + 0x1c));
  return;
}

