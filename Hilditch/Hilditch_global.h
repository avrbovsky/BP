#ifndef HILDITCH_GLOBAL_H
#define HILDITCH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HILDITCH_LIBRARY)
#  define HILDITCH_EXPORT Q_DECL_EXPORT
#else
#  define HILDITCH_EXPORT Q_DECL_IMPORT
#endif

#endif // HILDITCH_GLOBAL_H
