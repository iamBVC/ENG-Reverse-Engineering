/* __fassign @ 00564158   62 bytes */

/* Library Function - Single Match
    __fassign
   
   Library: Visual Studio 2003 Release */

void __cdecl __fassign(int flag,char *argument,char *number)

{
  undefined4 local_c;
  undefined4 local_8;
  
  if (flag != 0) {
    sub_569934(&local_c);
    *(undefined4 *)argument = local_c;
    *(undefined4 *)(argument + 4) = local_8;
    return;
  }
  sub_569961(&number,number);
  *(char **)argument = number;
  return;
}

