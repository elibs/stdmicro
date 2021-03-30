#!/usr/bin/python3

from svg.path import parse_path
from svg.path.path import *
from xml.dom import minidom
import sys
import os
import math

# read the SVG file
doc = minidom.parse(os.environ["HOME"] + "/DejaVuSans.svg")
pathArray = [path for path in doc.getElementsByTagName('glyph')]

DPI = 125
fontSize = 100
bitsPerPixel = 1

totalGlyphArea = 0
totalGlyphPixels = 0
PointPerInch = 72
PPI = (fontSize * (DPI / PointPerInch))

def size(value):
    suffixes = ["B", "KB", "MB", "GB"]
    i = 0;
    while value > 1024 and i < len(suffixes):
        value /= 1024
        i += 1

    return "{} {}".format(math.ceil(value), suffixes[i])

# print the line draw commands
for path in pathArray:
    gName = path.getAttribute("glyph-name")
    if gName[0] == '.' or path.getAttribute("unicode") is None:
        continue
    print("static em {}(EmBox* box)\n{{".format(path.getAttribute("glyph-name")))
    child=0
    p = parse_path(path.getAttribute("d"))

    maxX = -99999
    maxY = -99999
    minX =  99999
    minY =  99999
    hasPath = False

    for e in p:
        hasPath = True
        if isinstance(e, Move):
            x = e.start.real
            y = e.start.imag
            maxX = x if x > maxX else maxX
            minX = x if x < minX else minX
            maxY = y if y > maxY else maxY
            minY = y if y < minY else minY

            print("    Path pathSegment{} = Path::start({{{}, {}}});".format(child, e.start.real, e.start.imag))
            print("    pathSegment{}.".format(child))
        elif isinstance(e, Line):
            x = e.end.real
            y = e.end.imag
            maxX = x if x > maxX else maxX
            minX = x if x < minX else minX
            maxY = y if y > maxY else maxY
            minY = y if y < minY else minY
            print("        line({{{}, {}}})->".format(e.end.real, e.end.imag))
        elif isinstance(e, QuadraticBezier):
            x = e.control.real
            y = e.control.imag
            maxX = x if x > maxX else maxX
            minX = x if x < minX else minX
            maxY = y if y > maxY else maxY
            minY = y if y < minY else minY

            x = e.end.real
            y = e.end.imag
            maxX = x if x > maxX else maxX
            minX = x if x < minX else minX
            maxY = y if y > maxY else maxY
            minY = y if y < minY else minY
            print("        quadratic({{{}, {}}}, {{{}, {}}})->".format(e.control.real, e.control.imag, e.end.real, e.end.imag))
        elif isinstance(e, Close):
            print("        close(&pathSegment{});".format(child))
            print("    pathSegment{}.drawTo(box);".format(child))
            print("")
            child += 1
        else:
            print(e)
            sys.exit(1)
    print("    return {};".format(path.getAttribute("horiz-adv-x") if path.hasAttribute("horiz-adv-x") else 2000))
    print("}\n")

    if hasPath:
        dx = maxX - minX
        dy = maxY - minY
        area = dx * dy

        pdx = math.ceil(PPI * (dx / 2048))
        pdy = math.ceil(PPI * (dy / 2048))
        pxArea = pdx * pdy
        print("Character: {}; X: ({}, {}); Y: ({}, {}); Area: {}; Pixel Area: {}".format(path.getAttribute("glyph-name"), minX, maxX, minY, maxY, area, pxArea), file=sys.stderr)
        totalGlyphArea += area
        totalGlyphPixels += pxArea

print("Total glyph area: {}; pixels: {}; RAM: {}".format(totalGlyphArea, totalGlyphPixels, size(totalGlyphPixels / (8 / bitsPerPixel))), file=sys.stderr)

print("")
for path in pathArray:
    gName = path.getAttribute("glyph-name")
    if gName[0] == '.' or path.getAttribute("unicode") is None:
        continue
    print("case '{}': return {};".format(path.getAttribute("unicode"), gName))
