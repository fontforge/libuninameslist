# libuninameslist
#
# Copyright (c) 2019, Shriramana Sharma
#
# This Python wrapper is subject to the same "BSD 3-clause"-type license
# which the wrapped C library is subject to.


'''
provides access to Unicode character names, annotations and block data

This Python wrapper implements:

1) three functions:
   name, annotation, block
2) one generator:
   blocks
3) one variable:
   version
4) two convenience functions:
   name2, uplus

`version` points to the internal version string of the library.
Run help() on the rest of the symbols for more info.
'''


__all__ = ["version",
           "name", "name2", "charactersWithName2",
           "annotation",
           "block", "blocks",
           "valid", "uplus"]


# connecting to the dynamic library

from ctypes import *
from ctypes.util import find_library
_lib = CDLL(find_library("uninameslist"))

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

# int uniNamesList_names2cnt(void);
_setSig(_lib.uniNamesList_names2cnt, c_int, [])
# long uniNamesList_names2val(int count);
_setSig(_lib.uniNamesList_names2val, c_long, [c_int])
# int uniNamesList_names2getU(unsigned long uni);
_setSig(_lib.uniNamesList_names2getU, c_int, [c_ulong])
# int uniNamesList_names2lnC(int count);
_setSig(_lib.uniNamesList_names2lnC, c_int, [c_int])
# const char *uniNamesList_names2anC(int count);
_setSig(_lib.uniNamesList_names2anC, c_char_p, [c_int])


# internal helpers


class _block:
    '''Provides the name, start and end codepoints of a Unicode block and provides iteration over the valid codepoints in it'''
    __slots__ = ["name", "start", "end"]

    def __init__(self, name, start, end):
        self.name = name; self.start = start; self.end = end

    def __repr__(self):
        return "<‘{}’: {} - {}>".format(self.name, uplus(self.start), uplus(self.end))

    def __iter__(self):
        for cp in range(self.start, self.end + 1):
            if _lib.uniNamesList_name(cp) is None:
                continue
            yield chr(cp)

    @staticmethod
    def _fromNum(num):
        return _block(_lib.uniNamesList_blockName(num).decode(),
                      _lib.uniNamesList_blockStart(num),
                      _lib.uniNamesList_blockEnd(num))


_blockCount = _lib.uniNamesList_blockCount()


# public symbols


'''documents the version of libuninameslist'''
version = _lib.uniNamesList_NamesListVersion().decode()


def name(char):
    '''returns the Unicode character name'''
    name = _lib.uniNamesList_name(ord(char))
    return "" if name is None else name.decode()


def name2(char):
    '''returns the Unicode normative alias if defined for correcting a character name, else just the name'''
    name2Index = _lib.uniNamesList_names2getU(ord(char))
    if name2Index < 0:  # no normative alias
        return name(char)
    annotationBytes = _lib.uniNamesList_names2anC(name2Index)
    normativeAliasLength = _lib.uniNamesList_names2lnC(name2Index)
    return annotationBytes[:normativeAliasLength].decode()


def annotation(char):
    '''returns all Unicode annotations including aliases and cross-references as provided by NamesList.txt'''
    annot = _lib.uniNamesList_annot(ord(char))
    return "" if annot is None else annot.decode()


def blocks():
    '''a generator for iterating through all defined Unicode blocks'''
    for blockNum in range(_blockCount):
        yield _block._fromNum(blockNum)


def block(char):
    '''returns the Unicode block a character is in, or by block name'''
    if len(char) == 1:
        return _block._fromNum(_lib.uniNamesList_blockNumber(ord(char)))
    else:  # assuming input is a block name
        name = char.upper()
        for b in blocks():
            if b.name.upper() == name:
                return b
        raise ValueError("Invalid Unicode block name: ‘{}’".format(name))


# apart from what C library provides


charactersWithName2 = "".join(chr(_lib.uniNamesList_names2val(i)) for i in range(_lib.uniNamesList_names2cnt()))


def valid(char):
    '''returns whether a character is valid (defined in Unicode)'''
    return _lib.uniNamesList_name(ord(char)) is not None


def uplus(char):
    '''returns the Unicode codepoint for a character in the format U+XXXX for BMP and U+XXXXXX beyond that'''
    if type(char) is int:
        if not (0 <= char <= 0x10FFFF):
            raise ValueError("Invalid Unicode codepoint: U+{:X}".format(char))
        val = char
    else:
        val = ord(char)
    return ("U+{:06X}" if val > 0xFFFF else "U+{:04X}").format(val)


# test


def _test():
    print("Using libuninameslist version:\n\t", version)
    print("The Unicode name of ೞ is:\n\t", name("ೞ"))
    print("The Unicode annotation of ೞ is:")
    print(annotation("ೞ"))
    print("The corrected Unicode name of ೞ is:\n\t", name2("ೞ"))
    print("The Unicode block of ೞ is:\n\t", block("ೞ"))
    print("The Unicode codepoint of ೞ is:\n\t", uplus("ೞ"))
    print("The next character to ೞ is valid:\n\t", valid(chr(ord("ೞ") + 1)))
    print()
    print("The characters in the Tamil block:\n\t", " ".join(c for c in block("Tamil")))
    print()
    from random import sample
    print("A sample list of ten blocks:")
    for b in sample(tuple(blocks()), 10):
        print("\t", b)

if __name__ == "__main__":
    _test()
