/* Recovered callback at 0x0040ED80 from the original DirectDraw enumeration path. */
#include <stdint.h>
#include <string.h>

static const unsigned char ddraw_format_guid_a_ed80[16] = {
    0xe0, 0x02, 0x6d, 0xa3, 0xf3, 0xc9, 0xcf, 0x11,
    0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00
};
static const unsigned char ddraw_format_guid_b_ed80[16] = {
    0xe1, 0x02, 0x6d, 0xa3, 0xf3, 0xc9, 0xcf, 0x11,
    0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00
};

static uint32_t groove_read_u32_40ed80(const unsigned char *address)
{
    uint32_t value;
    memcpy(&value, address, sizeof(value));
    return value;
}

static void groove_write_u32_40ed80(unsigned char *address, uint32_t value)
{
    memcpy(address, &value, sizeof(value));
}

int __stdcall sub_40ED80(const void *surface_format, void *enumeration_context)
{
    const unsigned char *format = (const unsigned char *)surface_format;
    unsigned char *context = (unsigned char *)enumeration_context;
    uint32_t type_flags;
    uint32_t value;

    if ((groove_read_u32_40ed80(format + 0x1c) & 0x0f00u) != 0x0100u)
        return 1;

    value = groove_read_u32_40ed80(format + 0x14);
    if (memcmp(format + 4, ddraw_format_guid_a_ed80,
               sizeof(ddraw_format_guid_a_ed80)) == 0) {
        type_flags = groove_read_u32_40ed80(context + 0x5c);
        if (type_flags & 0x80000000u)
            groove_write_u32_40ed80(context + 0x5c, value);
        else if (groove_read_u32_40ed80(context + 0x64) & 0x80000000u)
            groove_write_u32_40ed80(context + 0x64, value);
    } else if (memcmp(format + 4, ddraw_format_guid_b_ed80,
                      sizeof(ddraw_format_guid_b_ed80)) == 0) {
        if (groove_read_u32_40ed80(context + 0x60) & 0x80000000u)
            groove_write_u32_40ed80(context + 0x60, value);
        else if (groove_read_u32_40ed80(context + 0x68) & 0x80000000u)
            groove_write_u32_40ed80(context + 0x68, value);
    }
    return 1;
}
