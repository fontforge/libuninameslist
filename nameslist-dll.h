/* Generic helper definitions for shared library support */
/* as explained in - https://gcc.gnu.org/wiki/Visibility */
#if defined (_WIN32) || defined (__CYGWIN__) || (_WIN64) || defined (__CYGWIN64__)
  #ifndef __clang__
    #define UN_DLL_IMPORT __declspec(dllimport)
    #define UN_DLL_EXPORT __declspec(dllexport)
    #define UN_DLL_LOCAL
  #else
    /* CLANG already appears to add this. Turn this off. */
    #define UN_DLL_IMPORT
    #define UN_DLL_EXPORT
    #define UN_DLL_LOCAL
  #endif
#else
  #if __GNUC__ >= 4
    #define UN_DLL_IMPORT __attribute__ ((visibility ("default")))
    #define UN_DLL_EXPORT __attribute__ ((visibility ("default")))
    /* 'internal' to avoid library conflicts. 'hidden' for debugging */
    /* #define UN_DLL_LOCAL  __attribute__ ((visibility ("hidden"))) */
    #define UN_DLL_LOCAL  __attribute__ ((visibility ("internal")))
  #else
    #define UN_DLL_IMPORT
    #define UN_DLL_EXPORT
    #define UN_DLL_LOCAL
  #endif
#endif

#ifdef UNICODE_BLOCK_MAX
/* Definitions used by nameslist.c for functions{16..21} */
UN_DLL_LOCAL int uniNamesList_haveFR(unsigned int lang);
#ifdef WANTLIBOFR
/* make this visible to nameslist.c if adding French lib */
extern UN_DLL_IMPORT const char *uniNamesList_NamesListVersionFR(void);
extern UN_DLL_IMPORT const char *uniNamesList_nameFR(unsigned long uni);
extern UN_DLL_IMPORT const char *uniNamesList_annotFR(unsigned long uni);
extern UN_DLL_IMPORT int uniNamesList_blockCountFR(void);
extern UN_DLL_IMPORT int uniNamesList_blockNumberFR(unsigned long uni);
extern UN_DLL_IMPORT long uniNamesList_blockStartFR(int uniBlock);
extern UN_DLL_IMPORT long uniNamesList_blockEndFR(int uniBlock);
extern UN_DLL_IMPORT const char *uniNamesList_blockNameFR(int uniBlock);
#else
/* make these internal stubs since there's no French lib */
UN_DLL_LOCAL const char *uniNamesList_NamesListVersionFR(void);
UN_DLL_LOCAL const char *uniNamesList_nameFR(unsigned long uni);
UN_DLL_LOCAL const char *uniNamesList_annotFR(unsigned long uni);
UN_DLL_LOCAL int uniNamesList_blockCountFR(void);
UN_DLL_LOCAL int uniNamesList_blockNumberFR(unsigned long uni);
UN_DLL_LOCAL long uniNamesList_blockStartFR(int uniBlock);
UN_DLL_LOCAL long uniNamesList_blockEndFR(int uniBlock);
UN_DLL_LOCAL const char *uniNamesList_blockNameFR(int uniBlock);
#endif
#endif
