/* Selected Ghidra export at 0056b57c. */

float10 sub_56B57C(void)

{
  float10 in_ST0;
  float10 fVar1;
  float10 in_ST1;
  
  if (((uint)((unkuint10)in_ST1 >> 0x30) & 0x7fff0000) != 0) {
    fVar1 = (float10)sub_56B376();
    return fVar1;
  }
  if (SUB104(in_ST1,0) != 0 || (int)((unkuint10)in_ST1 >> 0x20) != 0) {
    fVar1 = (float10)sub_56B376(in_ST1 * (float10)dRam0057d064);
    return fVar1;
  }
  return in_ST0 - (float10)(unkint10)(in_ST0 / in_ST1) * in_ST1;
}

