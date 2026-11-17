/* ~exception @ 0056d64f   22 bytes */

/* Library Function - Single Match
    public: virtual __thiscall exception::~exception(void)
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

void __thiscall exception::~exception(exception *this)

{
  *(undefined ***)this = &PTR_sub_56D5AC_0056eda0;
  if (*(int *)(this + 8) != 0) {
    sub_562941(*(undefined4 *)(this + 4));
  }
  return;
}

