/* __amsg_exit @ 2110d8f6   48 bytes */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 2003 Release */

void __cdecl __amsg_exit(int param_1)

{
  if ((DAT_21115608 == 1) || ((DAT_21115608 == 0 && (DAT_2111560c == 1)))) {
    sub_2110E637();
  }
  sub_2110E670(param_1);
  (*(code *)PTR___exit_21114e10)(0xff);
  return;
}

