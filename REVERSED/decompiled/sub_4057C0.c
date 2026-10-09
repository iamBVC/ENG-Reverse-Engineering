/* sub_4057C0 @ 004057c0   53 bytes */

float10 sub_4057C0(undefined4 param_1,float param_2)

{
  char cVar1;
  float local_4;
  
  local_4 = 0.0;
  cVar1 = sub_405B00(&local_4,0x80000002,"Software\\Disney Interactive\\Emperors New Groove\\1.0",
                     param_1);
  if (cVar1 != '\0') {
    return (float10)local_4;
  }
  return (float10)param_2;
}

