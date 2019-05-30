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

#include "qtxtReader.h"
#include <iostream>
#include <QFile>
#include <QTextCodec>
#include <QtPlugin>
#include <QDebug>
#include <QDesktopWidget>
using namespace std;
#define Q_OS_DARWIN
//Q_IMPORT_PLUGIN(qwslinuxinputkbddriver);
int main(int argc, char **argv)
{
    
    QApplication app(argc, argv);
    qtxtReader *reader = new qtxtReader;
    //QGridLayout *gl = new QGridLayout(dialog);
    //gl->addWidget(rte,0,0,1,1);
    QDesktopWidget desktop;
    QRect rec = desktop.geometry();
    int height = rec.height();
    int width = rec.width();

    reader->setWindowTitle(QObject::tr("rs97 text reader"));
    reader->setMinimumWidth (width);
    reader->setMinimumHeight(height);
    reader->setFixedSize(width,height);


    reader->show();

    if(argc>1) {
        QString fileName = QString::fromUtf8(argv[1]);
        //QTextCodec *codec = QTextCodec::codecForName("utf-8");
        QFile file(argv[1]);
        const wchar_t * encodedName = reinterpret_cast<const wchar_t *>(fileName.utf16());
        if(file.open(QIODevice::ReadOnly))
        {
            reader->fileName = argv[1];
            reader->setWindowTitle(fileName);
            QTextStream stream(&file);
            stream.setCodec("UTF-8");
            
            QString str = stream.readAll();
            
            qDebug( "open file : %ls", encodedName);
            reader->setText(str);
        }
        else {
            QString str = QString("open file fail:%1 \n %2").arg(fileName, file.errorString());
            reader->setText(str);
        }
    }

    return app.exec();
}
