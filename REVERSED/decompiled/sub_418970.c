/* sub_418970 @ 00418970   89 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_418970(void)

{
  if (DAT_00585219 == '\0') {
    _DAT_00584510 = (&PTR_s_Default_0057baa4)[DAT_00584f04];
  }
  else {
    _DAT_00584510 = (&PTR_s_Invertita_0057baa8)[DAT_00584f04];
  }
  if (DAT_00585218 != '\0') {
    _DAT_005844e0 = (&PTR_s_Attivato_0057bbbc)[DAT_00584f04];
    return 0;
  }
  _DAT_005844e0 = (&PTR_s_Disattivato_0057bbc0)[DAT_00584f04];
  return 0;
}

