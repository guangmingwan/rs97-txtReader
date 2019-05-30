#############################################################################
# Makefile for building: qtxtReader
# Generated by qmake (2.01a) (Qt 4.8.7) on: Thu May 30 18:41:25 2019
# Project:  qtxtReader.pro
# Template: app
# Command: /opt/buildroot-2018.02.11/output/build/qt-4.8.7/bin/qmake -o Makefile qtxtReader.pro
#############################################################################

####### Compiler, tools and options

CC            = /opt/buildroot-2018.02.11/output/host/bin/mipsel-buildroot-linux-uclibc-gcc
CXX           = /opt/buildroot-2018.02.11/output/host/bin/mipsel-buildroot-linux-uclibc-g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB
CFLAGS        = -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -Os -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -Os -std=gnu++98 -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/default -I. -I/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/include/QtCore -I/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/include/QtNetwork -I/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/include/QtGui -I/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/include -I. -I. -I.
LINK          = /opt/buildroot-2018.02.11/output/host/bin/mipsel-buildroot-linux-uclibc-g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot//usr/lib -L/opt/buildroot-2018.02.11/output/build/qt-4.8.7/plugins/kbddrivers/ -L/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot//usr/lib/qt/plugins/kbddrivers -lqlinuxinputkbddriver -lQtGui -L/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot//usr/lib -lfreetype -lQtNetwork -lQtCore -lz -lm -ldl -lrt -lpthread 
AR            = /opt/buildroot-2018.02.11/output/host/bin/mipsel-buildroot-linux-uclibc-ar cqs
RANLIB        = /opt/buildroot-2018.02.11/output/host/bin/mipsel-buildroot-linux-uclibc-ranlib
QMAKE         = /opt/buildroot-2018.02.11/output/build/qt-4.8.7/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = /opt/buildroot-2018.02.11/output/host/bin/mipsel-buildroot-linux-uclibc-strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = qtxtreader.cpp \
		mtextedit.cpp \
		main.cpp moc_qtxtreader.cpp \
		moc_mtextedit.cpp
OBJECTS       = qtxtreader.o \
		mtextedit.o \
		main.o \
		moc_qtxtreader.o \
		moc_mtextedit.o
DIST          = /opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/unix.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/linux.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/gcc-base.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/gcc-base-unix.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/g++-base.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/g++-unix.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/qws.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/qconfig.pri \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/qt_functions.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/qt_config.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/exclusive_builds.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/default_pre.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/release.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/default_post.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/static.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/warn_on.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/qt.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/unix/thread.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/moc.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/resources.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/uic.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/yacc.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/lex.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/include_source_dir.prf \
		qtxtReader.pro
QMAKE_TARGET  = qtxtReader
DESTDIR       = 
TARGET        = qtxtReader

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_qtxtreader.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: qtxtReader.pro  /opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/default/qmake.conf /opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/unix.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/linux.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/gcc-base.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/gcc-base-unix.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/g++-base.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/g++-unix.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/qws.conf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/qconfig.pri \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/qt_functions.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/qt_config.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/exclusive_builds.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/default_pre.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/release.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/default_post.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/static.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/warn_on.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/qt.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/unix/thread.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/moc.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/resources.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/uic.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/yacc.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/lex.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/include_source_dir.prf \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/lib/libQtGui.prl \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/lib/libQtNetwork.prl \
		/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/lib/libQtCore.prl
	$(QMAKE) -o Makefile qtxtReader.pro
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/unix.conf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/linux.conf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/gcc-base.conf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/gcc-base-unix.conf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/g++-base.conf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/g++-unix.conf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/common/qws.conf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/qconfig.pri:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/qt_functions.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/qt_config.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/exclusive_builds.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/default_pre.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/release.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/default_post.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/static.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/warn_on.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/qt.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/unix/thread.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/moc.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/resources.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/uic.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/yacc.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/lex.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/mkspecs/features/include_source_dir.prf:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/lib/libQtGui.prl:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/lib/libQtNetwork.prl:
/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile qtxtReader.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/qtxtReader1.0.0 || $(MKDIR) .tmp/qtxtReader1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/qtxtReader1.0.0/ && $(COPY_FILE) --parents qtxtreader.h mtextedit.h .tmp/qtxtReader1.0.0/ && $(COPY_FILE) --parents qtxtreader.cpp mtextedit.cpp main.cpp .tmp/qtxtReader1.0.0/ && $(COPY_FILE) --parents qtxtreader.ui .tmp/qtxtReader1.0.0/ && (cd `dirname .tmp/qtxtReader1.0.0` && $(TAR) qtxtReader1.0.0.tar qtxtReader1.0.0 && $(COMPRESS) qtxtReader1.0.0.tar) && $(MOVE) `dirname .tmp/qtxtReader1.0.0`/qtxtReader1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/qtxtReader1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_qtxtreader.cpp moc_mtextedit.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_qtxtreader.cpp moc_mtextedit.cpp
moc_qtxtreader.cpp: ui_qtxtReader.h \
		mtextedit.h \
		qtxtreader.h
	/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot//usr/bin/moc $(DEFINES) $(INCPATH) qtxtreader.h -o moc_qtxtreader.cpp

moc_mtextedit.cpp: mtextedit.h
	/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot//usr/bin/moc $(DEFINES) $(INCPATH) mtextedit.h -o moc_mtextedit.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_qtxtreader.h
compiler_uic_clean:
	-$(DEL_FILE) ui_qtxtreader.h
ui_qtxtreader.h: qtxtreader.ui
	/opt/buildroot-2018.02.11/output/host/mipsel-buildroot-linux-uclibc/sysroot/usr/bin/uic qtxtreader.ui -o ui_qtxtreader.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

qtxtreader.o: qtxtreader.cpp qtxtReader.h \
		ui_qtxtReader.h \
		mtextedit.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qtxtreader.o qtxtreader.cpp

mtextedit.o: mtextedit.cpp mtextedit.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mtextedit.o mtextedit.cpp

main.o: main.cpp qtxtReader.h \
		ui_qtxtReader.h \
		mtextedit.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

moc_qtxtreader.o: moc_qtxtreader.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qtxtreader.o moc_qtxtreader.cpp

moc_mtextedit.o: moc_mtextedit.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mtextedit.o moc_mtextedit.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

