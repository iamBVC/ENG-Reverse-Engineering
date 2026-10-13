/* Movie frame loader: release the previous frame surface, find the frame file, create a
   640 x 480 DDSCAPS_TEXTURE surface, decode the frame into a width*height*3 buffer (or
   read it straight from the file when the decoder declines it) and upload it.

   Every value comes from the listing:
       mov [desc+0], 7Ch / [desc+4], 7 / [desc+8], 1E0h (480) / [desc+0Ch], 280h (640)
       / the caps 40h at +68h, inside a 7Ch-byte zeroed local
       push offset dword_6D91B8 / push &desc / push device / call [vtable + 18h]
       mov eax,[desc+8] / imul eax,[desc+0Ch] / lea eax,[eax+eax*2]   <- height*width*3
       _malloc -> sub_40D3B0(file, buffer) -> fopen(file,"rb") / fread(buffer,1,size,..)
       sub_43B080(surface, &desc, buffer, 0, 3) -> _free(buffer)

   Ghidra's export lost three things here: the file-name argument of the search (EDX), the
   width/height it read back out of the descriptor (its `unaff_ESI`/`unaff_EBX`), and the
   third CreateSurface argument that the caller pushes early.  Hence the hand-written body.

   `DAT_006d91b8` is the frame surface the loader keeps between calls, and the release at
   the top is its vtable slot +8 - `IUnknown::Release`, the interface's AddRef/Release pair
   sitting at +4/+8. */
void sub_43B790(undefined4 param_1)
{
  groove_surface_desc desc;
  void *frame;
  char *path;
  int size;

  if (DAT_006d91b8 != 0) {
    (**(groove_com1 **)(*DAT_006d91b8 + 8))(DAT_006d91b8);
    DAT_006d91b8 = 0;
  }

  path = (char *)sub_415690(0, (char *)param_1);
  if (path == 0) return;

  memset(&desc, 0, sizeof desc);
  desc.dwSize = 0x7C;
  desc.dwFlags = 7;
  desc.dwHeight = 0x1E0;                       /* 480 */
  desc.dwWidth = 0x280;                        /* 640 */
  desc.ddsCaps = 0x40;                         /* DDSCAPS_TEXTURE */
  if ((**(groove_com4 **)(*DAT_00582ccc + 0x18))(DAT_00582ccc, &desc, &DAT_006d91b8, 0) != 0)
    return;

  size = (int)desc.dwHeight * (int)desc.dwWidth * 3;
  frame = malloc(size);
  if (frame == 0) return;

  if (sub_40D3B0(path, frame) == 0) {
    /* the decoder did not handle this file: it is a raw frame */
    void *file = fopen(path, "rb");
    if (file) {
      fread(frame, 1, size, file);
      fclose(file);
    }
  }
  sub_43B080(DAT_006d91b8, &desc, frame, 0, 3);
  sub_5628BC(frame);
  return;
}
