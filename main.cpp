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
using namespace std;
Q_IMPORT_PLUGIN(qwslinuxinputkbddriver);
int main(int argc, char **argv)
{
    
    QApplication app(argc, argv);

    QDialog *dialog = new QDialog(0);
    qtxtReader *rte = new qtxtReader(dialog);
    QGridLayout *gl = new QGridLayout(dialog);
    gl->addWidget(rte,0,0,1,1);
    dialog->setWindowTitle(QObject::tr("Rich text editor"));
    dialog->setMinimumWidth (320);
    dialog->setMinimumHeight(240);
    dialog->setFixedSize(320,240);
    dialog->show();

    if(argc>1) {
        QString filename = QString::fromUtf8(argv[1]);
        QTextCodec *codec = QTextCodec::codecForName("utf-8");
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QByteArray arr = file.readLine();
        QString str = codec->toUnicode(arr);
        qDebug( "open file : %s", qPrintable(filename));
        rte->setText(str);
    }

    return app.exec();
}
