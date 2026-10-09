/* sub_4071D0 @ 004071d0   106 bytes */

undefined4 sub_4071D0(void)

{
  char cVar1;
  int local_4;
  
  if (DAT_00581140 == 0) {
    return 0;
  }
  local_4 = DAT_00581140;
  cVar1 = sub_406880(&local_4);
  if (cVar1 != '\0') {
    cVar1 = sub_406AB0(&local_4);
    if (cVar1 != '\0') {
      cVar1 = sub_406D30(&local_4);
      if (cVar1 != '\0') {
        cVar1 = sub_406E40(&local_4);
        if (cVar1 != '\0') {
          cVar1 = sub_407240();
          if (cVar1 != '\0') {
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

