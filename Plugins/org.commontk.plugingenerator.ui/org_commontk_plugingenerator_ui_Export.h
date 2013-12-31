#ifndef _org_commontk_plugingenerator_ui_Export_h_
#define _org_commontk_plugingenerator_ui_Export_h_

#include <QtGlobal>

#if defined(Q_OS_WIN) || defined(Q_OS_SYMBIAN)
#  if defined(org_commontk_plugingenerator_ui_BUILD)
#    define org_commontk_plugingenerator_ui_EXPORT Q_DECL_EXPORT
#  else
#    define org_commontk_plugingenerator_ui_EXPORT Q_DECL_IMPORT
#  endif
#endif

#if !defined(org_commontk_plugingenerator_ui_EXPORT)
#    define org_commontk_plugingenerator_ui_EXPORT Q_DECL_EXPORT
#endif

#endif /* _org_commontk_plugingenerator_ui_Export_h_ */
