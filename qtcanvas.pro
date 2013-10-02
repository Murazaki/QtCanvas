QT += widgets opengl qml quick

HEADERS += voreenapplicationqt5.h \
    ext/tgt/include/tgt/qt/qttimer.h \
    ext/tgt/include/tgt/qt/qtcanvas.h
SOURCES += main.cpp \
    voreenapplicationqt5.cpp \
    ext/tgt/include/tgt/qt/qttimer.cpp \
    ext/tgt/include/tgt/qt/qtcanvas.cpp

RESOURCES += qtcanvas.qrc

OTHER_FILES += \
    main.qml

# Voreen implementation

INCLUDEPATH += $$PWD/ext/boost/include \
    $$PWD/ext/glew/include \
    $$PWD/ext/glut/include \
    $$PWD/ext/tgt/include \
    $$PWD/ext/voreen/include \
    $$PWD/ext/voreen/include/voreen \
    $$PWD/ext

DEPENDPATH += $$PWD/ext/boost/include \
    $$PWD/ext/glew/include \
    $$PWD/ext/glut/include \
    $$PWD/ext/tgt/include \
    $$PWD/ext/voreen/include \
    $$PWD/ext/voreen/include/voreen \
    $$PWD/ext

unix {
    DEFINES += LINUX
    LIBS += -L/usr/lib/ -Lext/boost/lib
    LIBS += -Lext/glew/lib -Lext/glut/lib -lGL -lGLU -lGLEW
    LIBS += -Lext/tgt/lib -Lext/voreen/lib -lopengl -lvoreen_core # -lvoreen_qt
#   LIBS += -lvoreen_core -lziparch
#   LIBS += -lIL -lILU -lILUT
}

win32 {
    LIBS += -L$$PWD/ext/glew/lib/win32/ \
    -L$$PWD/ext/glut/lib/win32/ \
    -L$$PWD/ext/tgt/lib/win32/ \
    -L$$PWD/ext/voreen/lib/win32/ \
    -lopengl32 -lglew32 -lglu32 -ltgt -lvoreen_core # -lvoreen_qt

    PRE_TARGETDEPS += $$PWD/ext/glew/lib/win32/glew32.lib \
    $$PWD/ext/glut/lib/win32/glut32.lib \
    $$PWD/ext/tgt/lib/win32/tgt.lib \
    $$PWD/ext/voreen/lib/win32/voreen_core.lib #\
#    $$PWD/ext/voreen/lib/win32/voreen_qt.lib
}

win32-msvc* {
    LIBS += -lnetapi32 -lversion

    # no libc for vc++ since we build a multithreaded executable
    #LIBS += /NODEFAULTLIB:libc.lib

    # for CoInitializeSecurity() to be defined
    #DEFINES += _WIN32_DCOM _WINDOWS

    #TGT
    DEFINES += NOMINMAX WIN32_LEAN_AND_MEAN

    #TinyXML
    DEFINES += _CRT_SECURE_NO_DEPRECATE TIXML_USE_STL

    #Eigen
    DEFINES += EIGEN_PERMANENTLY_DISABLE_STUPID_WARNINGS

    #Boost
    DEFINES += BOOST_ALL_NO_LIB

    DEFINES += VRN_MODULE_BASE VRN_MODULE_CORE

    QMAKE_CXXFLAGS += /wd4305 /wd4800 /wd4290 /wd4068 /wd4251 /wd4355 /wd4390 /wd4100 /MP /MD /bigobj
}

win32 {
    # Copy required DLLs to output directory
        EXTRA_BINFILES += \
            $$PWD/ext/dlls/*.dll \
            $$PWD/ext/glew/lib/win32/glew32.dll \
            $$PWD/ext/glut/lib/win32/glut32.dll \
            $$PWD/ext/tgt/lib/win32/tgt.dll \
            $$PWD/ext/voreen/lib/win32/voreen_core.* \
#            $$PWD/ext/voreen/lib/win32/voreen_qt.*
        EXTRA_BINFILES_WIN = $${EXTRA_BINFILES}
        EXTRA_BINFILES_WIN ~= s,/,\\,g

    CONFIG(debug, debug|release) {
        DESTDIR_WIN = $$OUT_PWD/debug
        DESTDIR_WIN ~= s,/,\\,g
        for(FILE,EXTRA_BINFILES_WIN){
                    QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DESTDIR_WIN}$$escape_expand(\\n\\t))
        }

#        POST_TARGETDEPS += $$OUT_PWD/debug/glew32.dll \
#                        $$OUT_PWD/debug/glut32.dll \
#                        $$OUT_PWD/debug/tgt.dll \
#                        $$OUT_PWD/debug/voreen_core.dll \
#                        $$OUT_PWD/debug/voreen_qt.dll
    } else:CONFIG(release, debug|release) {
        DESTDIR_WIN = $$OUT_PWD/release
        DESTDIR_WIN ~= s,/,\\,g
        for(FILE,EXTRA_BINFILES_WIN){
                    QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DESTDIR_WIN}$$escape_expand(\\n\\t))
        }

#        POST_TARGETDEPS += $$OUT_PWD/release/glew32.dll \
#                        $$OUT_PWD/release/glut32.dll \
#                        $$OUT_PWD/release/tgt.dll \
#                        $$OUT_PWD/release/voreen_core.dll \
#                        $$OUT_PWD/release/voreen_qt.dll
    } else {
        error(Unknown set of dependencies.)
    }
}

# End Voreen implementation
