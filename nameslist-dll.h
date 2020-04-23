/* Generic helper definitions for shared library support */
/* as explained in - https://gcc.gnu.org/wiki/Visibility */
#if defined _WIN32 || defined __CYGWIN__
  #define UN_DLL_IMPORT __declspec(dllimport)
  #define UN_DLL_EXPORT __declspec(dllexport)
  #define UN_DLL_LOCAL
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
int uniNamesList_haveFR(unsigned int lang);
#ifdef WANTLIBOFR
/* make this visible to nameslist.c if adding French lib */
extern const char *uniNamesList_NamesListVersionFR(void);
extern const char *uniNamesList_nameFR(unsigned long uni);
extern const char *uniNamesList_annotFR(unsigned long uni);
extern int uniNamesList_blockCountFR(void);
extern int uniNamesList_blockNumberFR(unsigned long uni);
extern long uniNamesList_blockStartFR(int uniBlock);
extern long uniNamesList_blockEndFR(int uniBlock);
extern const char *uniNamesList_blockNameFR(int uniBlock);
#else
/* make these internal stubs since there's no French lib */
const char *uniNamesList_NamesListVersionFR(void);
const char *uniNamesList_nameFR(unsigned long uni);
const char *uniNamesList_annotFR(unsigned long uni);
int uniNamesList_blockCountFR(void);
int uniNamesList_blockNumberFR(unsigned long uni);
long uniNamesList_blockStartFR(int uniBlock);
long uniNamesList_blockEndFR(int uniBlock);
const char *uniNamesList_blockNameFR(int uniBlock);
#endif
#endif