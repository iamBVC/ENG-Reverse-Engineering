/* sub_405830 @ 00405830   59 bytes */

bool sub_405830(undefined4 param_1,float param_2)

{
  char cVar1;
  
  sub_562717(&DAT_0057f7f4,&DAT_005702fc,(double)param_2);
  cVar1 = sub_405BA0(0x80000002,"Software\\Disney Interactive\\Emperors New Groove\\1.0",param_1,
                     &DAT_0057f7f4);
  return cVar1 != '\0';
}

