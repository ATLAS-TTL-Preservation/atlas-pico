#!/usr/bin/env python3

import argparse
from pathlib import Path
from PIL import Image


def rgb888_to_rgb565(r, g, b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


def sanitize_name(name: str) -> str:
    result = []

    for c in name:
        if c.isalnum():
            result.append(c)
        else:
            result.append("_")

    identifier = "".join(result)

    if identifier and identifier[0].isdigit():
        identifier = "_" + identifier

    return identifier


def main():
    parser = argparse.ArgumentParser(
        description="Convert PNG to ATLAS Image Header")

    parser.add_argument("input", help="Input PNG")
    parser.add_argument("output", help="Output header")
    parser.add_argument(
        "--name",
        help="Asset name (defaults to filename)")

    args = parser.parse_args()

    image = Image.open(args.input).convert("RGBA")

    width, height = image.size

    asset_name = sanitize_name(
        args.name if args.name else Path(args.input).stem)

    pixels = []

    for y in range(height):
        for x in range(width):
            r, g, b, a = image.getpixel((x, y))

            # Alpha gegen schwarzen Hintergrund mischen
            if a != 255:
                r = (r * a) // 255
                g = (g * a) // 255
                b = (b * a) // 255

            pixels.append(rgb888_to_rgb565(r, g, b))

    with open(args.output, "w", encoding="utf-8") as f:
        f.write("#pragma once\n\n")
        f.write("#include <cstdint>\n")
        f.write("#include <atlas/graphics/Image.hpp>\n\n")

        f.write("namespace atlas::assets\n")
        f.write("{\n\n")

        f.write(
            f"constexpr std::uint16_t {asset_name}Data[{len(pixels)}] =\n")
        f.write("{\n")

        for i, pixel in enumerate(pixels):
            if i % 12 == 0:
                f.write("    ")

            f.write(f"0x{pixel:04X}")

            if i != len(pixels) - 1:
                f.write(", ")

            if i % 12 == 11:
                f.write("\n")

        if len(pixels) % 12 != 0:
            f.write("\n")

        f.write("};\n\n")

        f.write(f"constexpr atlas::graphics::Image {asset_name}(\n")
        f.write(f"    {asset_name}Data,\n")
        f.write(f"    {width},\n")
        f.write(f"    {height});\n\n")

        f.write("}\n")

    print(f"Generated {args.output}")


if __name__ == "__main__":
    main()