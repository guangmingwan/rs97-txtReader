/*
** Copyright (C) 2013 Jiří Procházka (Hobrasoft)
** Contact: http://www.hobrasoft.cz/
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file is under the terms of the GNU Lesser General Public License
** version 2.1 as published by the Free Software Foundation and appearing
** in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the
** GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
*/

#include "qtxtreader.h"
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QFontDatabase>
#include <QInputDialog>
#include <QColorDialog>
#include <QTextList>
#include <QtDebug>
#include <QFileDialog>
#include <QImageReader>
#include <QSettings>
#include <QBuffer>
#include <QUrl>
#include <QPlainTextEdit>
#include <QString>
#include <QFont>
#include <QMenu>
#include <QDialog>
#include<QScrollBar>
#include <stdlib.h>
#include <math.h>

QString qtxtReader::styleSheetFromFile(QString file, QString folderForUrl)
{
    qDebug("styleSheetFromFile %ls %ls", reinterpret_cast<const wchar_t *>(file.utf16()), reinterpret_cast<const wchar_t *>(folderForUrl.utf16()));
    QFile f(file);
    f.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(f.readAll());
    f.close();
    styleSheet.replace("url(","url("+folderForUrl+"/");
    return styleSheet;
}
qtxtReader::qtxtReader(QWidget *parent) : QWidget(parent) , scrollValue(0), fontSize(12), textColor(QString("#000000"))
{
    setupUi(this);
    #ifdef __APPLE__
    #else
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    #endif
    //this->setGeometry(QRect(0, 0, 320, 240));//可设置窗口显示的方位与大小
    m_lastBlockList = 0;
    f_textedit->setTabStopWidth(40);

    connect(f_textedit->verticalScrollBar(),SIGNAL(valueChanged(int)),this, SLOT(setValue(int)));

    f_textedit->installEventFilter(this);
    
    f_textedit->verticalScrollBar()->setStyleSheet(
                                                   
                                                   "QScrollBar:vertical"
                                                   "{"
                                                   "width:4px;"
                                                   "background:rgba(0,0,0,0%);"
                                                   "margin:0px,0px,0px,0px;"
                                                   "padding-top:9px;"
                                                   "padding-bottom:9px;"
                                                   "}"
                                                   "QScrollBar::handle:vertical"
                                                   "{"
                                                   "width:4px;"
                                                   "background:rgba(0,0,0,25%);"
                                                   " border-radius:4px;"
                                                   "min-height:20;"
                                                   "}"
                                                   "QScrollBar::handle:vertical:hover"
                                                   "{"
                                                   "width:4px;"
                                                   "background:rgba(0,0,0,50%);"
                                                   " border-radius:4px;"
                                                   "min-height:20;"
                                                   "}"
                                                   "QScrollBar::add-line:vertical"
                                                   "{"
                                                   "height:9px;width:4px;"
                                                   "border-image:url(:/images/a/3.png);"
                                                   "subcontrol-position:bottom;"
                                                   "}"
                                                   "QScrollBar::sub-line:vertical"
                                                   "{"
                                                   "height:9px;width:4px;"
                                                   "border-image:url(:/images/a/1.png);"
                                                   "subcontrol-position:top;"
                                                   "}"
                                                   "QScrollBar::add-line:vertical:hover"
                                                   "{"
                                                   "height:9px;width:4px;"
                                                   "border-image:url(:/images/a/4.png);"
                                                   "subcontrol-position:bottom;"
                                                   "}"
                                                   "QScrollBar::sub-line:vertical:hover"
                                                   "{"
                                                   "height:9px;width:4px;"
                                                   "border-image:url(:/images/a/2.png);"
                                                   "subcontrol-position:top;"
                                                   "}"
                                                   "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                                                   "{"
                                                   "background:rgba(0,0,0,10%);"
                                                   "border-radius:4px;"
                                                   "}"
                                                   );
    m_fontsize_h1 = 18;
    m_fontsize_h2 = 16;
    m_fontsize_h3 = 14;
    m_fontsize_h4 = 12;

   
    m_paragraphItems << tr("Standard")
                     << tr("Heading 1")
                     << tr("Heading 2")
                     << tr("Heading 3")
                     << tr("Heading 4")
                     << tr("Monospace");

    // undo & redo

    // cut, copy & paste

#ifndef QT_NO_CLIPBOARD
    //connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(slotClipboardDataChanged()));
#endif

    // link

    // bold, italic & underline

    QAction *actFullscreen = new QAction(QString::fromUtf8("全屏"), this);
    //actReloadByUTF8->setShortcut(QKeySequence("CTRL+M"));
    connect(actFullscreen, SIGNAL(triggered()), this, SLOT(fullscreen()));
    //f_textedit->addAction(actFullscreen);
    

    QAction *actReloadByUTF8 = new QAction(QString::fromUtf8("强制使用UTF8编码"), this);
    //actReloadByUTF8->setShortcut(QKeySequence("CTRL+M"));
    connect(actReloadByUTF8, SIGNAL(triggered()), this, SLOT(reloadByUtf8()));
    //f_textedit->addAction(actReloadByUTF8);

    QAction *actReloadByGBK = new QAction(QString::fromUtf8("强制使用GBK编码"), this);
    connect(actReloadByGBK, SIGNAL(triggered()), this, SLOT(reloadByGBK()));
    //f_textedit->addAction(actReloadByGBK);

    QAction *textsource = new QAction(QString::fromUtf8("退出"), this);
    textsource->installEventFilter(this);
    //textsource->setShortcut(QKeySequence("CTRL+O"));
    connect(textsource, SIGNAL(triggered()), this, SLOT(slotQuit()));
    //f_textedit->addAction(textsource);

    f_textedit->setFocus();

    f_textedit->setFrameStyle(QFrame::NoFrame);

    menu = new QMenu(this);
    menu->installEventFilter(this);
    menu->addAction(actFullscreen);

    QMenu *menuReload = menu->addMenu(QString::fromUtf8("编码"));
    menuReload->installEventFilter(this);
    
    //menu->addAction(actReloadByGBK);
    menuReload->addAction(actReloadByGBK);
    menuReload->addAction(actReloadByUTF8);

    QMenu *subMenu = menu->addMenu(QString::fromUtf8("字体"));

    QAction *actFontMini = new QAction(QString::fromUtf8("微(12)"), this);
    connect(actFontMini, SIGNAL(triggered()), this, SLOT(actFontMini()));

    QAction *actFontSmall = new QAction(QString::fromUtf8("小(13)"), this);
    connect(actFontSmall, SIGNAL(triggered()), this, SLOT(actFontSmall()));

    QAction *actFontMedium = new QAction(QString::fromUtf8("中(14)"), this);
    connect(actFontMedium, SIGNAL(triggered()), this, SLOT(actFontMedium()));

    QAction *actFontBig = new QAction(QString::fromUtf8("大(15)"), this);
    connect(actFontBig, SIGNAL(triggered()), this, SLOT(actFontBig()));

    subMenu->addAction(actFontMini);
    subMenu->addAction(actFontSmall);
    subMenu->addAction(actFontMedium);
    subMenu->addAction(actFontBig);
    subMenu->installEventFilter(this);
    //menu->addAction(menuReload);
    menu->addAction(textsource);
    f_menu->setMenu(menu);
    f_menu->setPopupMode(QToolButton::InstantPopup);
    f_menu->setShortcut(QKeySequence(Qt::Key_Escape));
    f_menu->setFocusPolicy(Qt::NoFocus);

    f_toolbar->setWindowOpacity(0.5);

    QFontDatabase db;
}

void qtxtReader::setValue(int v) {
    this->scrollValue = v;
    //qDebug("setValue %d",v);
}
void qtxtReader::readConfig() {
    QString appPath = QDir::currentPath();
    QString iniFileName = appPath +"/qtxtreader.ini";
    qDebug("read from ini: %s", qPrintable(iniFileName));
    QSettings *settings = new QSettings(iniFileName, QSettings::IniFormat);
    //向ini文件中写入内容,setValue函数的两个参数是键值对
    //向ini文件的第一个节写入内容,ip节下的第一个参数
    //QString scrollValue = settings->getValue(tr("/progress/")+ tr(this->fileName));
    
    QString textColor = settings->value("/skin/textcolor").toString();
    int scrollValuel = settings->value(tr("/book_progress/")+ tr(this->fileName)).toInt();
    
    int book_fontsize = settings->value(tr("/book_fontsize/")+ tr(this->fileName)).toInt();

    if(textColor.length() >0) {
        this->textColor = textColor;
        f_textedit->setStyleSheet( tr("QTextEdit{color:%1}").arg(textColor) );
        qDebug("read textColor: %s", qPrintable(this->textColor));
    }
    
    if(book_fontsize > 0) {
        this->fontSize = book_fontsize;
        QFont font = QFont();
        font.setPointSize(book_fontsize);
        f_textedit->setFont(font);
        qDebug("read book fontsize: %d", book_fontsize);
    }
    else {
        int fontsize = settings->value(tr("/skin/fontsize")).toInt();
        if(fontsize >0) {
            this->fontSize = fontsize;
            QFont font2 = QFont();
            font2.setPointSize(fontsize);
            f_textedit->setFont(font2);
            qDebug("read fontsize: %d", fontsize);
            
        }
    }
    
    if(scrollValuel > 0) {
        qDebug("read scrollValue: %d", scrollValuel);
        this->scrollValue  = scrollValuel;
        f_textedit->verticalScrollBar()->setValue(this->scrollValue);

        
        
    }
    
    
    
    
}
void qtxtReader::writeConfig() {
    QString appPath = QDir::currentPath();
    QString iniFileName = appPath +"/qtxtreader.ini";
    qDebug("save to ini: %s", qPrintable(iniFileName));
    qDebug("set fontsize: %d", this->fontSize);
    qDebug("set textColor: %s", qPrintable(this->textColor));
    qDebug("set scrollValue: %d", this->scrollValue);
    QSettings *settings = new QSettings(iniFileName, QSettings::IniFormat);
   //向ini文件中写入内容,setValue函数的两个参数是键值对
   //向ini文件的第一个节写入内容,ip节下的第一个参数
   //this->fontSize = 12;
   settings->setValue(tr("/skin/fontsize"), this->fontSize);
   settings->setValue(tr("/skin/textcolor"), this->textColor);
   settings->setValue(tr("/book_progress/")+ tr(this->fileName), this->scrollValue);
   settings->setValue(tr("/book_fontsize/")+ tr(this->fileName), this->fontSize);
   settings->sync();

}
bool qtxtReader::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        //qDebug("qtxtReader::eventFilter : key:0x%04x", key->key());
        if(obj->metaObject()->className() == QString("QMenu")) { //a button ,when menu focus
            if( key->key() == Qt::Key_Control) {
                QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_Return,Qt::NoModifier,QString());
                QCoreApplication::postEvent((QObject*)obj, eve1);
            }
            return false;
            
        }
        if( key->key()==Qt::Key_Tab || key->key()==Qt::Key_Left) {
            //QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_PageUp, Qt::NoModifier, QString());
            QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_PageUp,Qt::NoModifier,QString());
            QCoreApplication::postEvent((QObject*)f_textedit, eve1);
            
        }
        else if ( key->key()==Qt::Key_Backspace || key->key()==Qt::Key_Right ) {
            QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_PageDown,Qt::NoModifier,QString());

            QCoreApplication::postEvent((QObject*)f_textedit, eve1);
            //qDebug("send key:0x%04x", eve1->key());
        } else if ( key->key()==Qt::Key_Escape) {
            if(!f_toolbar->isVisible()) {
                f_toolbar->setVisible(true);
            }
        }
        else {
            return QObject::eventFilter(obj, event);
        }
        //return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}
void qtxtReader::slotQuit()
{
    this->writeConfig();
    QApplication::quit();
}
void qtxtReader::fullscreen() {
    f_toolbar->setVisible(false);
}

void qtxtReader::reloadByUtf8()
{
    QString fileName = QString::fromUtf8(this->fileName);
    //QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QFile file(this->fileName);
    const wchar_t *encodedName = reinterpret_cast<const wchar_t *>(fileName.utf16());
    if (file.open(QIODevice::ReadOnly))
    {
        //reader->fileName = this->fileName;
        this->setWindowTitle(fileName);
        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        QString str = stream.readAll();

        qDebug("open file : %ls", encodedName);
        this->setText(str);
    }
    else
    {
        QString str = QString("open file fail:%1 \n %2").arg(fileName, file.errorString());
        this->setText(str);
    }
}

void qtxtReader::actFontMini() {
    //f_textedit->setFont
    QFont font = QFont();
    font.setPointSize(12);
    this->fontSize = 12;
    f_textedit->setFont(font);
    
}
void qtxtReader::actFontSmall() {
    //f_textedit->setFont
    QFont font = QFont();
    font.setPointSize(13);
    this->fontSize = 13;
    f_textedit->setFont(font);
    
}
void qtxtReader::actFontMedium() {
    QFont font = QFont();
    font.setPointSize(14);
    this->fontSize = 14;
    f_textedit->setFont(font);
}
void qtxtReader::actFontBig() {
    QFont font = QFont();
    font.setPointSize(15);
    this->fontSize = 15;
    f_textedit->setFont(font);
}
void qtxtReader::reloadByGBK()
{

    QString fileName = QString::fromUtf8(this->fileName);
    //QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QFile file(this->fileName);
    const wchar_t *encodedName = reinterpret_cast<const wchar_t *>(fileName.utf16());
    if (file.open(QIODevice::ReadOnly))
    {
        //reader->fileName = this->fileName;
        this->setWindowTitle(fileName);
        QTextStream stream(&file);
        stream.setCodec("GBK");

        QString str = stream.readAll();

        qDebug("open file : %ls", encodedName);
        this->setText(str);
    }
    else
    {
        QString str = QString("open file fail:%1 \n %2").arg(fileName, file.errorString());
        this->setText(str);
    }
}



  

// void qtxtReader::fontChanged(const QFont &f)
// {
    
// }


QString qtxtReader::toHtml() const
{
    QString s = f_textedit->toHtml();
    // convert emails to links
    s = s.replace(QRegExp("(<[^a][^>]+>(?:<span[^>]+>)?|\\s)([a-zA-Z\\d]+@[a-zA-Z\\d]+\\.[a-zA-Z]+)"), "\\1<a href=\"mailto:\\2\">\\2</a>");
    // convert links
    s = s.replace(QRegExp("(<[^a][^>]+>(?:<span[^>]+>)?|\\s)((?:https?|ftp|file)://[^\\s'\"<>]+)"), "\\1<a href=\"\\2\">\\2</a>");
    // see also: Utils::linkify()
    return s;
}


// Prints to the provided buffer a nice number of bytes (KB, MB, GB, etc)
void pretty_bytes(char* buf, uint bytes)
{
    const char* suffixes[7];
    suffixes[0] = "个";//"B";
    suffixes[1] = "千";//"KB";
    suffixes[2] = "万";//"MB";
    uint s = 0; // which suffix to use
    double count = bytes;
    if(bytes>1000) {
        s++;
        count = bytes / 1000.0;
    }
    if(bytes>10000) {
        s++;
        count = bytes / 10000.0;
    }
    
    if(s<=0)
        sprintf(buf, "%d%s", (int)count, suffixes[s]);
    else
        sprintf(buf, "%.1f%s", count, suffixes[s]);
}
void qtxtReader::setText(const QString &text)
{
    if (text.isEmpty())
    {
        setPlainText(text);
        return;
    }
    if (text[0] == '<')
    {
        setHtml(text);
    }
    else
    {
        setPlainText(text);
    }
    char cb[1024]="";
    pretty_bytes(cb,text.length());
    QString wc = QString::fromUtf8("字:") + QString::fromUtf8(cb);
    this->l_word_count->setText( wc );

    int bc = f_textedit->document()->blockCount();
    qDebug("block count: %d", bc);

    this->readConfig();
    
}
void qtxtReader::setCode(const QString &text)
{
    if (text.isEmpty())
    {
        l_encode_name->setText(QString::fromUtf8("未识别，使用默认utf8"));
        return;
    }
    else
    {
        l_encode_name->setText(QString::fromUtf8("编码：") + text);
    }
}
