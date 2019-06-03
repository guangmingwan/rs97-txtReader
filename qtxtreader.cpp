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
    qDebug("styleSheetFromFile %ls %ls", file.utf16(), folderForUrl.utf16());
    QFile f(file);
    f.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(f.readAll());
    f.close();
    styleSheet.replace("url(","url("+folderForUrl+"/");
    return styleSheet;
}
qtxtReader::qtxtReader(QWidget *parent) : QWidget(parent)
{
    setupUi(this);
    #ifdef __APPLE__
    #else
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    #endif
    //this->setGeometry(QRect(0, 0, 320, 240));//可设置窗口显示的方位与大小
    m_lastBlockList = 0;
    f_textedit->setTabStopWidth(40);

    connect(f_textedit, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(slotCurrentCharFormatChanged(QTextCharFormat)));
    connect(f_textedit, SIGNAL(cursorPositionChanged()),
            this, SLOT(slotCursorPositionChanged()));
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

    fontChanged(f_textedit->font());
    bgColorChanged(f_textedit->textColor());

    // paragraph formatting

    m_paragraphItems << tr("Standard")
                     << tr("Heading 1")
                     << tr("Heading 2")
                     << tr("Heading 3")
                     << tr("Heading 4")
                     << tr("Monospace");

    // undo & redo

    // cut, copy & paste

#ifndef QT_NO_CLIPBOARD
    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(slotClipboardDataChanged()));
#endif

    // link

    // bold, italic & underline

    QAction *actFullscreen = new QAction(QString::fromUtf8("全屏"), this);
    //actReloadByUTF8->setShortcut(QKeySequence("CTRL+M"));
    connect(actFullscreen, SIGNAL(triggered()), this, SLOT(fullscreen()));
    f_textedit->addAction(actFullscreen);
    

    QAction *actReloadByUTF8 = new QAction(QString::fromUtf8("强制使用UTF8编码"), this);
    //actReloadByUTF8->setShortcut(QKeySequence("CTRL+M"));
    connect(actReloadByUTF8, SIGNAL(triggered()), this, SLOT(reloadByUtf8()));
    f_textedit->addAction(actReloadByUTF8);

    QAction *actReloadByGBK = new QAction(QString::fromUtf8("强制使用GBK编码"), this);
    connect(actReloadByGBK, SIGNAL(triggered()), this, SLOT(reloadByGBK()));
    f_textedit->addAction(actReloadByGBK);

    QAction *textsource = new QAction(QString::fromUtf8("退出[START]"), this);
    //textsource->setShortcut(QKeySequence("CTRL+O"));
    connect(textsource, SIGNAL(triggered()), this, SLOT(slotQuit()));
    f_textedit->addAction(textsource);

    f_textedit->setFocus();

    QMenu *menu = new QMenu(this);
    menu->addAction(actFullscreen);

    QMenu *actReload = menu->addMenu(QString::fromUtf8("编码"));
    
    //menu->addAction(actReloadByGBK);
    actReload->addAction(actReloadByGBK);
    actReload->addAction(actReloadByUTF8);

    QMenu *actFont = menu->addMenu(QString::fromUtf8("字体"));

    QAction *actFontSmall = new QAction(QString::fromUtf8("小"), this);
    connect(actFontSmall, SIGNAL(triggered()), this, SLOT(actFontSmall()));

    QAction *actFontMedium = new QAction(QString::fromUtf8("中"), this);
    connect(actFontMedium, SIGNAL(triggered()), this, SLOT(actFontMedium()));

    QAction *actFontBig = new QAction(QString::fromUtf8("大"), this);
    connect(actFontBig, SIGNAL(triggered()), this, SLOT(actFontBig()));

    actFont->addAction(actFontSmall);
    actFont->addAction(actFontMedium);
    actFont->addAction(actFontBig);

    //menu->addAction(actReload);
    menu->addAction(textsource);
    f_menu->setMenu(menu);
    f_menu->setPopupMode(QToolButton::InstantPopup);
    f_menu->setShortcut(QKeySequence(Qt::Key_Escape));
    f_menu->setFocusPolicy(Qt::NoFocus);

    f_toolbar->setWindowOpacity(0.5);

    QFontDatabase db;
}


bool qtxtReader::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        //qDebug("qtxtReader::eventFilter : key:0x%04x", key->key());
        if( key->key()==Qt::Key_Tab || key->key()==Qt::Key_Left) {
            //QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_PageUp, Qt::NoModifier, QString());
            QKeyEvent * eve1 = new QKeyEvent (QEvent::KeyPress,Qt::Key_PageUp,Qt::NoModifier,QString());
            QCoreApplication::postEvent((QObject*)f_textedit, eve1);
            //qDebug("send key:0x%04x", eve1->key());
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
void qtxtReader::actFontSmall() {
    //f_textedit->setFont
    QFont font = QFont();
    font.setPointSize(16);
    f_textedit->setFont(font);
    
}
void qtxtReader::actFontMedium() {
    QFont font = QFont();
    font.setPointSize(24);
    f_textedit->setFont(font);
}
void qtxtReader::actFontBig() {
    QFont font = QFont();
    font.setPointSize(32);
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

void qtxtReader::textBold()
{
    QTextCharFormat fmt;
    //fmt.setFontWeight(f_bold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void qtxtReader::focusInEvent(QFocusEvent *)
{
    f_textedit->setFocus(Qt::TabFocusReason);
}

void qtxtReader::textUnderline()
{
    QTextCharFormat fmt;
    mergeFormatOnWordOrSelection(fmt);
}

void qtxtReader::textItalic()
{
    QTextCharFormat fmt;

    mergeFormatOnWordOrSelection(fmt);
}

void qtxtReader::textStrikeout()
{
    QTextCharFormat fmt;

    mergeFormatOnWordOrSelection(fmt);
}

void qtxtReader::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0)
    {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void qtxtReader::textLink(bool checked)
{
    bool unlink = false;
    QTextCharFormat fmt;
    if (checked)
    {
        QString url = f_textedit->currentCharFormat().anchorHref();
        bool ok;
        QString newUrl = QInputDialog::getText(this, tr("Create a link"),
                                               tr("Link URL:"), QLineEdit::Normal,
                                               url,
                                               &ok);
        if (ok)
        {
            fmt.setAnchor(true);
            fmt.setAnchorHref(newUrl);
            fmt.setForeground(QApplication::palette().color(QPalette::Link));
            fmt.setFontUnderline(true);
        }
        else
        {
            unlink = true;
        }
    }
    else
    {
        unlink = true;
    }
    if (unlink)
    {
        fmt.setAnchor(false);
        fmt.setForeground(QApplication::palette().color(QPalette::Text));
        fmt.setFontUnderline(false);
    }
    mergeFormatOnWordOrSelection(fmt);
}

void qtxtReader::textStyle(int index)
{
    QTextCursor cursor = f_textedit->textCursor();
    cursor.beginEditBlock();

    // standard
    if (!cursor.hasSelection())
    {
        cursor.select(QTextCursor::BlockUnderCursor);
    }
    QTextCharFormat fmt;
    cursor.setCharFormat(fmt);
    f_textedit->setCurrentCharFormat(fmt);

    if (index == ParagraphHeading1 || index == ParagraphHeading2 || index == ParagraphHeading3 || index == ParagraphHeading4)
    {
        if (index == ParagraphHeading1)
        {
            fmt.setFontPointSize(m_fontsize_h1);
        }
        if (index == ParagraphHeading2)
        {
            fmt.setFontPointSize(m_fontsize_h2);
        }
        if (index == ParagraphHeading3)
        {
            fmt.setFontPointSize(m_fontsize_h3);
        }
        if (index == ParagraphHeading4)
        {
            fmt.setFontPointSize(m_fontsize_h4);
        }
        if (index == ParagraphHeading2 || index == ParagraphHeading4)
        {
            fmt.setFontItalic(true);
        }

        fmt.setFontWeight(QFont::Bold);
    }
    if (index == ParagraphMonospace)
    {
        fmt = cursor.charFormat();
        fmt.setFontFamily("Monospace");
        fmt.setFontStyleHint(QFont::Monospace);
        fmt.setFontFixedPitch(true);
    }
    cursor.setCharFormat(fmt);
    f_textedit->setCurrentCharFormat(fmt);

    cursor.endEditBlock();
}

void qtxtReader::textFgColor()
{
    QColor col = QColorDialog::getColor(f_textedit->textColor(), this);
    QTextCursor cursor = f_textedit->textCursor();
    if (!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    QTextCharFormat fmt = cursor.charFormat();
    if (col.isValid())
    {
        fmt.setForeground(col);
    }
    else
    {
        fmt.clearForeground();
    }
    cursor.setCharFormat(fmt);
    f_textedit->setCurrentCharFormat(fmt);
    fgColorChanged(col);
}

void qtxtReader::textBgColor()
{
    QColor col = QColorDialog::getColor(f_textedit->textBackgroundColor(), this);
    QTextCursor cursor = f_textedit->textCursor();
    if (!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    QTextCharFormat fmt = cursor.charFormat();
    if (col.isValid())
    {
        fmt.setBackground(col);
    }
    else
    {
        fmt.clearBackground();
    }
    cursor.setCharFormat(fmt);
    f_textedit->setCurrentCharFormat(fmt);
    bgColorChanged(col);
}

void qtxtReader::listBullet(bool checked)
{
    if (checked)
    {
    }
    list(checked, QTextListFormat::ListDisc);
}

void qtxtReader::listOrdered(bool checked)
{
    if (checked)
    {
    }
    list(checked, QTextListFormat::ListDecimal);
}

void qtxtReader::list(bool checked, QTextListFormat::Style style)
{
    QTextCursor cursor = f_textedit->textCursor();
    cursor.beginEditBlock();
    if (!checked)
    {
        QTextBlockFormat obfmt = cursor.blockFormat();
        QTextBlockFormat bfmt;
        bfmt.setIndent(obfmt.indent());
        cursor.setBlockFormat(bfmt);
    }
    else
    {
        QTextListFormat listFmt;
        if (cursor.currentList())
        {
            listFmt = cursor.currentList()->format();
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
    }
    cursor.endEditBlock();
}

void qtxtReader::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = f_textedit->textCursor();
    if (!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    f_textedit->mergeCurrentCharFormat(format);
    f_textedit->setFocus(Qt::TabFocusReason);
}

void qtxtReader::slotCursorPositionChanged()
{
    QTextList *l = f_textedit->textCursor().currentList();
    if (m_lastBlockList && (l == m_lastBlockList || (l != 0 && m_lastBlockList != 0 && l->format().style() == m_lastBlockList->format().style())))
    {
        return;
    }
    m_lastBlockList = l;
    if (l)
    {
        QTextListFormat lfmt = l->format();
        if (lfmt.style() == QTextListFormat::ListDisc)
        {
        }
        else if (lfmt.style() == QTextListFormat::ListDecimal)
        {
        }
        else
        {
        }
    }
    else
    {
    }
}

void qtxtReader::fontChanged(const QFont &f)
{
    
}

void qtxtReader::fgColorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    if (c.isValid())
    {
        pix.fill(c);
    }
    else
    {
        pix.fill(QApplication::palette().foreground().color());
    }
    // l_word_count->setIcon(pix);
}

void qtxtReader::bgColorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    if (c.isValid())
    {
        pix.fill(c);
    }
    else
    {
        pix.fill(QApplication::palette().background().color());
    }
    //f_bgcolor->setIcon(pix);
}

void qtxtReader::slotCurrentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    bgColorChanged((format.background().isOpaque()) ? format.background().color() : QColor());
    fgColorChanged((format.foreground().isOpaque()) ? format.foreground().color() : QColor());
    //l_encode_name->setChecked(format.isAnchor());
}

void qtxtReader::slotClipboardDataChanged(){
#ifndef QT_NO_CLIPBOARD
//if (const QMimeData *md = QApplication::clipboard()->mimeData())

#endif
}

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

void qtxtReader::increaseIndentation()
{
    indent(+1);
}

void qtxtReader::decreaseIndentation()
{
    indent(-1);
}

void qtxtReader::indent(int delta)
{
    QTextCursor cursor = f_textedit->textCursor();
    cursor.beginEditBlock();
    QTextBlockFormat bfmt = cursor.blockFormat();
    int ind = bfmt.indent();
    if (ind + delta >= 0)
    {
        bfmt.setIndent(ind + delta);
    }
    cursor.setBlockFormat(bfmt);
    cursor.endEditBlock();
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
        count = bytes / 1000;
    }
    if(bytes>10000) {
        s++;
        count = bytes / 10000;
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

void qtxtReader::insertImage()
{
    QSettings s;
    QString attdir = s.value("general/filedialog-path").toString();
    QString file = QFileDialog::getOpenFileName(this,
                                                tr("Select an image"),
                                                attdir,
                                                tr("JPEG (*.jpg);; GIF (*.gif);; PNG (*.png);; BMP (*.bmp);; All (*)"));
    QImage image = QImageReader(file).read();

    f_textedit->dropImage(image, QFileInfo(file).suffix().toUpper().toLocal8Bit().data());
}
