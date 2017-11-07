# libuninameslist
#
# Copyright (C) 2017, Shriramana Sharma
#
# This Python wrapper is subject to the same "BSD 3-clause"-type license
# which the wrapped C library is subject to.

__all__ = ["version", "name", "annotation", "blocks", "block", "uplus"]

# connecting to the dynamic library

from ctypes import *
_lib = CDLL("libuninameslist.so.1")

def _setSig(fn, restype, argtypes):
    if restype is not None: fn.restype = restype
    fn.argtypes = argtypes

# const char *uniNamesList_NamesListVersion(void);
_setSig(_lib.uniNamesList_NamesListVersion, c_char_p, [])
# const char *uniNamesList_name(unsigned long uni);
_setSig(_lib.uniNamesList_name, c_char_p, [c_ulong])
# const char *uniNamesList_annot(unsigned long uni);
_setSig(_lib.uniNamesList_annot, c_char_p, [c_ulong])
# int uniNamesList_blockCount(void);
_setSig(_lib.uniNamesList_blockCount, c_int, [])
# int uniNamesList_blockNumber(unsigned long uni);
_setSig(_lib.uniNamesList_blockNumber, c_int, [c_ulong])
# long uniNamesList_blockStart(int uniBlock);
_setSig(_lib.uniNamesList_blockStart, c_long, [c_int])
# long uniNamesList_blockEnd(int uniBlock);
_setSig(_lib.uniNamesList_blockEnd, c_long, [c_int])
# const char *uniNamesList_blockName(int uniBlock);
_setSig(_lib.uniNamesList_blockName, c_char_p, [c_int])

# internal helpers

class _block:

    __slots__ = ["name", "start", "end"]

    def __init__(self, name, start, end):
        self.name = name; self.start = start; self.end = end

    def __str__(self):
        return "<‘{}’: {} - {}>".format(self.name, uplus(self.start), uplus(self.end))

    @staticmethod
    def fromNum(num):
        return _block(_lib.uniNamesList_blockName(num).decode(),
                      _lib.uniNamesList_blockStart(num),
                      _lib.uniNamesList_blockEnd(num))

_blockCount = _lib.uniNamesList_blockCount()

# public symbols

version = _lib.uniNamesList_NamesListVersion().decode()

def name(char):
    return _lib.uniNamesList_name(ord(char)).decode()

def annotation(char):
    annot = _lib.uniNamesList_annot(ord(char))
    return "" if annot is None else annot.decode()

def blocks():
    for blockNum in range(_blockCount):
        yield _block.fromNum(blockNum)

def block(char):
    return _block.fromNum(_lib.uniNamesList_blockNumber(ord(char)))

def uplus(char):
    if type(char) is int:
        if not (0 <= char <= 0x10FFFF):
            raise ValueError("Invalid Unicode codepoint: U+{:X}".format(char))
        val = char
    else:
        val = ord(char)
    return ("U+{:06X}" if val > 0xFFFF else "U+{:04X}").format(val)

# test

def _test():
    print("Using libuninameslist version :", version)
    print("The Unicode name of 😃 is      :", name("😃"))
    print("The Unicode annotation of 😃 is:")
    print(annotation("😃"))
    print("The Unicode block of 😃 is     :", block("😃"))
    print("The Unicode codepoint of 😃 is :", uplus("😃"))
    print()
    print("A complete list of blocks:")
    print("\n".join(str(block) for block in blocks()))

if __name__ == "__main__":
    _test()
