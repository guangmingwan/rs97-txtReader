/*
 *
 *
 *
 *
 */

#if QT_VERSION >= 0x050000
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#else
#include <QApplication>
#include <QDialog>
#endif

#include "qtxtreader.h"
#include <iostream>
#include <QDir>
#include <QFile>
#include <QTextCodec>
#include <QtPlugin>
#include <QDebug>
#include <QDesktopWidget>
#include "charsetdetect.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>
using namespace std;
#define Q_OS_DARWIN
//Q_IMPORT_PLUGIN(qwslinuxinputkbddriver);
#define BUFFER_SIZE 4096
const char *detect_charset(const char *fileName)
{
    FILE *fd = fopen(fileName, "r");
    csd_t csd = csd_open();
    if (csd == (csd_t)-1)
    {
        qDebug("csd_open failed: %s", fileName);
        return NULL;
    }

    int size;
    char buf[BUFFER_SIZE] = {0};

    while ((size = fread(buf, 1, sizeof(buf), fd)) != 0)
    {
        int result = csd_consider(csd, buf, size);
        if (result < 0)
        {
            qDebug("csd_consider failed");
            return NULL;
        }
        else if (result > 0)
        {
            // Already have enough data
            break;
        }
    }

    const char *result = csd_close(csd);
    if (result == NULL)
    {
        qDebug("Unknown character set");
        return NULL;
    }
    else
    {
        qDebug("%s", result);
        return result;
    }
}
int main(int argc, char **argv)
{

QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//this->setFont(QFont("wenquanyi", 12, QFont::Bold));
    QApplication app(argc, argv);
#ifdef __APPLE__
    QString appPath = QDir::currentPath();
    qDebug("appPath %s", qPrintable(appPath));
    app.setStyleSheet(
        "QTextEdit"
        "{"
        "background-image: url(" + appPath + "/bin/background.png);"
        //"background2:rgb(253, 230, 224);"
        "}");
#else
    app.setStyleSheet(
        "QTextEdit"
        "{"
        "background-image: url(./background.png);"
        //"background2:rgb(253, 230, 224);"
        "}");
#endif

    qtxtReader *reader = new qtxtReader;
    //QGridLayout *gl = new QGridLayout(dialog);
    //gl->addWidget(rte,0,0,1,1);

    reader->setWindowTitle(QObject::tr("rs97 text reader"));

#ifdef __APPLE__
    reader->setFixedSize(320, 240);
#else
    QDesktopWidget desktop;
    QRect rec = desktop.geometry();
    int height = rec.height();
    int width = rec.width();
    reader->setMinimumWidth(width);
    reader->setMinimumHeight(height);
    reader->setFixedSize(width, height);
#endif

    reader->show();
#ifdef __APPLE__
#else
    QApplication::setOverrideCursor(Qt::BlankCursor); //隐藏鼠标
#endif

    if (argc > 1)
    {
        QString fileName = QString::fromUtf8(argv[1]);
        //QTextCodec *codec = QTextCodec::codecForName("utf-8");
        QFile file(argv[1]);
        const char *code = detect_charset(argv[1]);
        const wchar_t *encodedName = reinterpret_cast<const wchar_t *>(fileName.utf16());
        if (file.open(QIODevice::ReadOnly))
        {
            reader->fileName = argv[1];
            reader->setWindowTitle(fileName);
            QTextStream stream(&file);
            stream.setCodec(code);
            reader->setCode(code);
            QString str = stream.readAll();

            qDebug("open file : %ls", encodedName);
            reader->setText(str);
        }
        else
        {
            QString str = QString("open file fail:%1 \n %2").arg(fileName, file.errorString());
            reader->setText(str);
        }
    }

    return app.exec();
}
