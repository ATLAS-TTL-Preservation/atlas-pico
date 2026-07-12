#!/usr/bin/env python3
"""
convert_ttf_font.py

Convert a TrueType font into the ATLAS bitmap font format.

Requires:
    pip install pillow

Usage:
    python convert_ttf_font.py font.ttf Output.cpp --size 8
"""

import argparse
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont


def pack_bitmap(mask, w, h):
    data = []
    byte = 0
    bits = 0

    for y in range(h):
        for x in range(w):
            byte <<= 1
            if mask.getpixel((x, y)):
                byte |= 1
            bits += 1
            if bits == 8:
                data.append(byte)
                byte = 0
                bits = 0

    if bits:
        byte <<= (8 - bits)
        data.append(byte)

    return data


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("font")
    parser.add_argument("output")
    parser.add_argument("--size", type=int, default=8)
    parser.add_argument("--first", type=int, default=32)
    parser.add_argument("--last", type=int, default=126)

    args = parser.parse_args()

    font = ImageFont.truetype(args.font, args.size)

    bitmap_bytes = []
    glyphs = []

    offset = 0
    max_height = 0

    for codepoint in range(args.first, args.last + 1):
        ch = chr(codepoint)

        bbox = font.getbbox(ch)

        if bbox is None:
            glyphs.append((offset, 0, 0, 0, 0, 0))
            continue

        left, top, right, bottom = bbox

        width = max(0, right - left)
        height = max(0, bottom - top)

        max_height = max(max_height, height)

        advance = int(round(font.getlength(ch)))

        if width == 0 or height == 0:
            glyphs.append((offset, width, height, advance, left, top))
            continue

        img = Image.new("1", (width, height), 0)
        draw = ImageDraw.Draw(img)
        draw.text((-left, -top), ch, font=font, fill=1)

        packed = pack_bitmap(img, width, height)

        bitmap_bytes.extend(packed)

        glyphs.append(
            (
                offset,
                width,
                height,
                advance,
                left,
                top,
            )
        )

        offset += len(packed)

    out = []

    out.append('#include <atlas/graphics/fonts/IBMBios.hpp>')
    out.append("")
    out.append("namespace atlas::graphics::fonts")
    out.append("{")
    out.append("")
    out.append("namespace")
    out.append("{")
    out.append("")
    out.append("constexpr std::uint8_t Bitmaps[] =")
    out.append("{")

    line = []
    for i, b in enumerate(bitmap_bytes):
        line.append(f"0x{b:02X}")
        if len(line) == 16:
            out.append("    " + ", ".join(line) + ",")
            line = []

    if line:
        out.append("    " + ", ".join(line) + ",")

    out.append("};")
    out.append("")
    out.append("constexpr atlas::graphics::Glyph Glyphs[] =")
    out.append("{")

    for g in glyphs:
        out.append(
            f"    {{ Bitmaps, {g[0]}, {g[1]}, {g[2]}, {g[3]}, {g[4]}, {g[5]} }},"
        )

    out.append("};")
    out.append("")
    out.append("}")
    out.append("")
    out.append("const atlas::graphics::Glyph& IBMBios::GetGlyph(char c) const")
    out.append("{")
    out.append("    static constexpr atlas::graphics::Glyph Invalid{nullptr,0,0,0,0,0,0};")
    out.append(f"    if(c<{args.first}||c>{args.last}) return Invalid;")
    out.append(f"    return Glyphs[c-{args.first}];")
    out.append("}")
    out.append("")
    out.append("std::uint8_t IBMBios::GetHeight() const")
    out.append("{")
    out.append(f"    return {max_height};")
    out.append("}")
    out.append("")
    out.append("}")

    Path(args.output).write_text("\n".join(out), encoding="utf-8")
    print("Generated", args.output)


if __name__ == "__main__":
    main()
