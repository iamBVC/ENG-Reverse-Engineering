/* sub_405790 @ 00405790   42 bytes */

undefined * sub_405790(undefined4 param_1,undefined *param_2)

{
  char cVar1;
  undefined *puVar2;
  
  cVar1 = sub_4058A0(&DAT_0057ddc4,0x80000002,
                     "Software\\Disney Interactive\\Emperors New Groove\\1.0",param_1);
  puVar2 = &DAT_0057ddc4;
  if (cVar1 == '\0') {
    puVar2 = param_2;
  }
  return puVar2;
}

