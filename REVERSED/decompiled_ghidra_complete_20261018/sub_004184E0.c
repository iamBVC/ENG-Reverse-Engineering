/* sub_4184E0 @ 004184e0   168 bytes */

undefined4 sub_4184E0(undefined4 param_1)

{
  undefined *puVar1;
  
  switch(param_1) {
  case 1:
    puVar1 = (&PTR_s_Cuffie_0057bb00)[DAT_00584f04];
    goto LAB_00418573;
  case 2:
    puVar1 = (&PTR_DAT_0057bb14)[DAT_00584f04];
LAB_00418573:
    *(undefined **)(PTR_DAT_00571e70 + 0x78) = puVar1;
    DAT_006da2fc = 0x3000;
switchD_004184ee_default:
    return 0;
  case 3:
    puVar1 = (&PTR_DAT_0057bb04)[DAT_00584f04];
    break;
  case 4:
    *(undefined **)(PTR_DAT_00571e70 + 0x78) = (&PTR_s_Stereo_0057bb08)[DAT_00584f04];
    DAT_006da2fc = 0x4000;
    return 0;
  case 5:
    puVar1 = (&PTR_s_Surround_0057bb0c)[DAT_00584f04];
    break;
  case 6:
    puVar1 = (&PTR_s_Punto_5_0057bb10)[DAT_00584f04];
    break;
  default:
    goto switchD_004184ee_default;
  }
  *(undefined **)(PTR_DAT_00571e70 + 0x78) = puVar1;
  DAT_006da2fc = 0x5000;
  return 0;
}

