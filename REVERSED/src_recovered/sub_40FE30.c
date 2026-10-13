/* Reload graphics settings using typed float calls and contiguous size pairs. */
undefined1 sub_40FE30(void)
{
  char *adapter = (char *)sub_56D4ED(sub_405790(s_DisplayDevice_00571784, &DAT_0057f834));
  char *device = (char *)sub_56D4ED(sub_405790(s_D3DDevice_00571778, &DAT_0057f834));
  float10 (__cdecl *read)(undefined4, float) = (float10 (__cdecl *)(undefined4, float))sub_4057C0;
  int hardware[2];
  int software[2];
  int bpp = (int)read((undefined4)s_ScreenBPP_0057176c, 32.0f);
  int software_bpp;
  undefined1 result;
  hardware[0] = (int)read((undefined4)s_ScreenW_00571764, 640.0f);
  hardware[1] = (int)read((undefined4)s_ScreenH_0057175c, 480.0f);
  software_bpp = (int)read((undefined4)s_SoftwareScreenBPP_00571748, 32.0f);
  software[0] = (int)read((undefined4)s_SoftwareScreenW_00571738, 320.0f);
  software[1] = (int)read((undefined4)s_SoftwareScreenH_00571728, 200.0f);
  result = sub_40FFD0(adapter, device, bpp, software_bpp, hardware, software);
  sub_5628BC(adapter);
  sub_5628BC(device);
  return result;
}
