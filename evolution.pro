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
    src/evolution/Gene.cpp \
    src/evolution/Individual.cpp \
    src/evolution/Generation.cpp \
    src/gui/GraphicsGridView.cpp \
    src/gui/GridView.cpp \
    src/gui/GenerationView.cpp \
    src/game/Player.cpp \
    src/gui/ScoreTableView.cpp

HEADERS += \
    src/game/Grid.h \
    src/game/Cell.h \
    src/Global.h \
    src/game/Game.h \
    src/game/Player.h \
    src/game/Unit.h \
    src/game/Match.h \
    src/game/ScoreTable.h \
    src/game/Score.h \
    src/game/Tournament.h \
    src/game/Route.h \
    src/evolution/Gene.h \
    src/evolution/Individual.h \
    src/evolution/Generation.h \
    src/gui/GraphicsGridView.h \
    src/gui/GridView.h \
    src/gui/GenerationView.h \
    src/gui/ScoreTableView.h

QT += core widgets gui
CONFIG += c++11

INCLUDEPATH += src/

FORMS += \
    src/gui/GraphicsGridView.ui \
    src/gui/GridView.ui \
    src/gui/GenerationView.ui \
    src/gui/ScoreTableView.ui
