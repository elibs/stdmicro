#!/usr/bin/python3

from svg.path import parse_path
from svg.path.path import *
from xml.dom import minidom
import sys

# read the SVG file
doc = minidom.parse('/home/jblades/DejaVuSans.svg')
pathArray = [path for path in doc.getElementsByTagName('glyph')]

# print the line draw commands
for path in pathArray:
    gName = path.getAttribute("glyph-name")
    if gName[0] == '.' or path.getAttribute("unicode") is None:
        continue
    print("static em {}(EmBox* box)\n{{".format(path.getAttribute("glyph-name")))
    child=0
    p = parse_path(path.getAttribute("d"))
    for e in p:
        if isinstance(e, Move):
            print("    Path pathSegment{} = Path::start({{{}, {}}});".format(child, e.start.real, e.start.imag))
            print("    pathSegment{}.".format(child))
        elif isinstance(e, Line):
            print("        line({{{}, {}}})->".format(e.end.real, e.end.imag))
        elif isinstance(e, QuadraticBezier):
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

print("")
for path in pathArray:
    gName = path.getAttribute("glyph-name")
    if gName[0] == '.' or path.getAttribute("unicode") is None:
        continue
    print("case '{}': return {};".format(path.getAttribute("unicode"), gName))
