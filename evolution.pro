SOURCES += \
    src/main.cpp \
    src/game/Grid.cpp \
    src/game/Cell.cpp \
    src/game/Game.cpp \
    src/game/Unit.cpp \
    src/game/Match.cpp \
    src/game/ScoreTable.cpp \
    src/game/Score.cpp \
    src/game/Tournament.cpp \
    src/game/Route.cpp \
    src/evolution/AiIndividual.cpp \
    src/evolution/Gene.cpp

HEADERS += \
    src/game/Grid.h \
    src/game/Cell.h \
    src/Global.h \
    src/game/Game.h \
    src/game/Player.h \
    src/game/Unit.h \
    src/game/Match.h \
    src/game/game/ScoreTable.h \
    src/game/Score.h \
    src/game/Tournament.h \
    src/game/Route.h \
    src/evolution/AiIndividual.h \
    src/evolution/Gene.h

QT += core
CONFIG += c++11

INCLUDEPATH += src/
