//
// Created by ebalo on 10/08/22.
//

#ifndef ABYSS_MACRO_H
#define ABYSS_MACRO_H

#ifndef INCLUDE_QT_SINK
#define INCLUDE_QT_SINK (false)
#endif

#ifndef INCLUDE_SYSTEMD_SINK
#define INCLUDE_SYSTEMD_SINK (false)
#endif

#ifndef INCLUDE_MONGO_DB_SINK
#define INCLUDE_MONGO_DB_SINK (false)
#endif

#define includes_qt() (defined(INCLUDE_QT_SINK) && INCLUDE_QT_SINK)
#define includes_systemd() (defined(INCLUDE_SYSTEMD_SINK) && INCLUDE_SYSTEMD_SINK)
#define includes_mongo_db() (defined(INCLUDE_MONGO_DB_SINK) && INCLUDE_MONGO_DB_SINK)

#define ABYSS_LOGGER_ALL_CHANNEL ("__all__")

#endif //ABYSS_MACRO_H
