/* sub_5628EB @ 005628eb   86 bytes */

undefined4 sub_5628EB(FILE *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if ((param_1->_flag & 0x40U) == 0) {
    if ((param_1->_flag & 0x83U) != 0) {
      uVar2 = sub_5638F0(param_1);
      __freebuf(param_1);
      iVar1 = sub_5666EC(param_1->_file);
      if (iVar1 < 0) {
        uVar2 = 0xffffffff;
      }
      else if (param_1->_tmpfname != (char *)0x0) {
        sub_5628BC(param_1->_tmpfname);
        param_1->_tmpfname = (char *)0x0;
      }
    }
  }
  else {
    uVar2 = 0xffffffff;
  }
  param_1->_flag = 0;
  return uVar2;
}

