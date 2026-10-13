/* Texture loader: LoadImageA the named bitmap, describe a source surface of cx x cy with
   DDSCAPS_TEXTURE, create it through the device's own vtable slot +0x18, copy the bitmap
   into it with sub_40D020, release the DIB and return the surface (0 on failure).

   Four arguments - the caller hoists two of them:
       mov ecx, dword_583378      (the height, pushed first, so it is the last argument)
       mov edx, dword_583374      (the width)
       push ecx / push edx        <- before the file search, they stay on the stack
       ... sub_415690 finds the file, then push eax / push edx (name, device) ...
       call sub_40CF10
       add esp, 10h               (four dwords)
   Ghidra's export passed only two arguments and read the returned surface out of EDI -
   a register `rep stosd` had just clobbered - which is why this body is hand-written.
   The descriptor is the one the original builds: `mov [desc+0], 7Ch` (the size it
   declares), `+4 = 7` (CAPS|HEIGHT|WIDTH), `+8 = height`, `+0Ch = width`, and the caps
   dword 0x40 (DDSCAPS_TEXTURE) at +68h, inside a 7Ch-byte zeroed local. */

typedef struct {
  unsigned int dwSize;      /* 0x00  007Ch */
  unsigned int dwFlags;     /* 0x04  7 */
  unsigned int dwHeight;    /* 0x08  cy */
  unsigned int dwWidth;     /* 0x0C  cx */
  unsigned char  unused[0x68 - 0x10];
  unsigned int ddsCaps;     /* 0x68  40h */
  unsigned char  tail[0x7C - 0x6C];
} groove_surface_desc;

void *sub_40CF10(int *device, LPCSTR name, int cx, int cy)
{
  groove_surface_desc desc;
  unsigned char bitmap[0x18];
  HANDLE image;
  void *surface;

  if (device == 0) return 0;

  image = LoadImageA(GetModuleHandleA(0), name, 0, cx, cy, 0x2000);
  if (image == 0) {
    image = LoadImageA(0, name, 0, cx, cy, 0x2010);
    if (image == 0) return 0;
  }
  GetObjectA(image, 0x18, bitmap);

  memset(&desc, 0, sizeof desc);
  desc.dwSize = 0x7C;
  desc.dwFlags = 7;
  desc.dwHeight = (unsigned int)cy;
  desc.dwWidth = (unsigned int)cx;
  desc.ddsCaps = 0x40;

  surface = 0;
  if ((**(code **)(*device + 0x18))(device, &desc, &surface, 0) != 0) return 0;
  sub_40D020(surface, image, 0, 0, 0, 0);
  DeleteObject(image);
  return surface;
}
