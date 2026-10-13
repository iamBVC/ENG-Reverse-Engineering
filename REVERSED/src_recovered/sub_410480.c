/* Gamma ramp: 256 entries of `start + scale * pow(i/255, gamma)`, clamped to [0, 1) and
   scaled to 16 bits, the same value written to all three channels, then handed to the
   gamma control - the vtable slot at +0x10 of the interface at 00582CEC, which is
   IDirectDrawGammaControl::SetGammaRamp (a 3 x 256 word ramp, so the local is one).

   The listing is explicit about the shape, and about the third argument:
       arg_0, arg_4, arg_8 are all `dword ptr` floats (a cdecl call, three floats),
       fild [i] / fmul 0.0039215686 (that is i/255) / fld [arg_8] / call __CIpow,
       fmul [arg_4] / fadd [arg_0], then the two comparisons against 0.0f and 1.0f,
       fmul 65535.0 / __ftol, and `mov ds:0FFFFh` for the saturated case.
   Ghidra's export instead read the value back through a register it could not model
   (`in_EAX`) and passed two arguments, which is why this body is hand-written. */
uint sub_410480(float start, float scale, float gamma)
{
  undefined2 ramp[3][256];
  int *control;
  int index;

  control = DAT_00582cec;
  if (control == 0) return 0;

  for (index = 0; index < 256; ++index) {
    float value = start + scale * (float)pow((float)index * 0.003921568627450980f, gamma);
    undefined2 entry;

    if (value <= 0.0f) {
      entry = 0;
    } else if (value < 1.0f) {
      entry = (undefined2)(int)(value * 65535.0f);
    } else {
      entry = 0xffff;
    }
    ramp[0][index] = entry;
    ramp[1][index] = entry;
    ramp[2][index] = entry;
  }
  return (uint)((**(code **)(*control + 0x10))(control, 0, ramp) == 0);
}
