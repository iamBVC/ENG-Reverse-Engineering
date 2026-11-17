/* sub_56D188 @ 0056d188   61 bytes */

void sub_56D188(void)

{
  exception *this;
  int unaff_EBP;
  
  sub_56D674();
  *(exception **)(unaff_EBP + -0x10) = this;
  *(undefined ***)this = &PTR_sub_56D1C5_0056ed68;
  *(undefined4 *)(unaff_EBP + -4) = 0;
  sub_413BF0(1);
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  exception::~exception(this);
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

