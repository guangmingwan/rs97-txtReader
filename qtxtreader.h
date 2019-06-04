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

#ifndef _qtxtReader_H_
#define _qtxtReader_H_

#include <QPointer>
#include "ui_qtxtreader.h"

/**
 * @Brief A simple rich-text editor
 */
class qtxtReader : public QWidget, protected Ui::qtxtReader {
    Q_OBJECT
  public:
    char* fileName;
    qtxtReader(QWidget *parent = 0);

    QString toPlainText() const { return f_textedit->toPlainText(); }
    QString toHtml() const;
    QTextDocument *document() { return f_textedit->document(); }
    QTextCursor    textCursor() const { return f_textedit->textCursor(); }
    void           setTextCursor(const QTextCursor& cursor) { f_textedit->setTextCursor(cursor); }

  public slots:
    void setText(const QString &text);
    void setCode(const QString &code);
  protected slots:
    void setPlainText(const QString &text) { f_textedit->setPlainText(text); }
    void setHtml(const QString &text)      { f_textedit->setHtml(text); }
    void reloadByUtf8();
    void fullscreen();
    void reloadByGBK();
    void actFontMini();
    void actFontSmall();
    void actFontMedium(); 
    void actFontBig(); 
   
    void slotQuit();
    void setValue(int v);

  protected:
    //void keyPressEvent( QKeyEvent *k );
    //bool event(QEvent *event);
    QMenu *menu;
    QString styleSheetFromFile(QString file, QString folderForUrl);
    int scrollValue;
    int fontSize;
    QString textColor;
    void readConfig();
    void writeConfig();
    bool eventFilter(QObject* obj, QEvent* event);
    
    QStringList m_paragraphItems;
    int m_fontsize_h1;
    int m_fontsize_h2;
    int m_fontsize_h3;
    int m_fontsize_h4;

    enum ParagraphItems { ParagraphStandard = 0,
                          ParagraphHeading1,
                          ParagraphHeading2,
                          ParagraphHeading3,
                          ParagraphHeading4,
                          ParagraphMonospace };

    QPointer<QTextList> m_lastBlockList;
};

#endif
