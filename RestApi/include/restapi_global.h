#ifndef RESTAPI_GLOBAL_H
#define RESTAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef RESTAPI_LIB
# define RESTAPI_EXPORT Q_DECL_EXPORT
#else
# define RESTAPI_EXPORT Q_DECL_IMPORT
#endif

#endif // RESTAPI_GLOBAL_H
