/* sub_562C7F @ 00562c7f   67 bytes */

int sub_562C7F(char *param_1,undefined4 param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  size_t sVar3;
  
  sVar1 = _strlen(param_1);
  uVar2 = sub_567475(param_2);
  sVar3 = sub_562B75(param_1,1,sVar1,param_2);
  sub_567502(uVar2,param_2);
  return (sVar3 == sVar1) - 1;
}

