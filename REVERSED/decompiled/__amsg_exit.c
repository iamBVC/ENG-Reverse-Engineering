/* __amsg_exit @ 00563fd6   34 bytes */

/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 2003 Release */

void __cdecl __amsg_exit(int param_1)

{
  if (DAT_006da3b8 == 1) {
    sub_5691E5();
  }
  sub_56921E(param_1);
  (*(code *)PTR___exit_0057c7c0)(0xff);
  return;
}

