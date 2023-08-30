#pragma once

#if defined(_WIN32)
// Windows
#define EXPORT_SYMBOLS __declspec(dllexport)
#define IMPORT_SYMBOLS __declspec(dllimport)
#else
//  do nothing and hope for the best?
#define EXPORT_SYMBOLS
#define IMPORT_SYMBOLS
#pragma warning Unknown dynamic link import / export semantics.
#endif
