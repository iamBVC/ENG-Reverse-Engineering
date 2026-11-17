/* sub_56D326 @ 0056d326   61 bytes */

void sub_56D326(void)

{
  exception *this;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  
  sub_56D674();
  *(exception **)(unaff_EBP + -0x10) = this;
  *(undefined ***)this = &PTR_sub_56D1C5_0056ed68;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  sub_413BF0(1);
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  exception::~exception(this);
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0xc);
  return;
}

