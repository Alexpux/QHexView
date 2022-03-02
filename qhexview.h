#pragma once

#define QHEXVIEW_VERSION 5.0

#include <QAbstractScrollArea>
#include <QTextCharFormat>
#include <QFontMetricsF>
#include <QTextDocument>
#include <QRectF>
#include <QList>
#include "model/qhexdocument.h"
#include "model/qhexcursor.h"

class QHexView : public QAbstractScrollArea
{
    Q_OBJECT

    public:
        enum class Area { Header, Address, Hex, Ascii, Extra };
        Q_ENUM(Area)

    public:
        explicit QHexView(QWidget *parent = nullptr);
        QHexDocument* hexDocument() const;
        QHexCursor* hexCursor() const;
        const QHexOptions* options() const;
        void setOptions(const QHexOptions& options);
        void setDocument(QHexDocument* doc);
        void setByteColor(quint8 b, QHexColor c);
        void setByteForeground(quint8 b, QColor c);
        void setByteBackground(quint8 b, QColor c);
        void setMetadata(qint64 begin, qint64 end, const QColor &fgcolor, const QColor &bgcolor, const QString &comment);
        void setForeground(qint64 begin, qint64 end, const QColor &fgcolor);
        void setBackground(qint64 begin, qint64 end, const QColor &bgcolor);
        void setComment(qint64 begin, qint64 end, const QString& comment);
        void setMetadataSize(qint64 begin, qint64 length, const QColor &fgcolor, const QColor &bgcolor, const QString &comment);
        void setForegroundSize(qint64 begin, qint64 length, const QColor &fgcolor);
        void setBackgroundSize(qint64 begin, qint64 length, const QColor &bgcolor);
        void setCommentSize(qint64 begin, qint64 length, const QString& comment);
        void removeMetadata(qint64 line);
        void removeBackground(qint64 line);
        void removeForeground(qint64 line);
        void removeComments(qint64 line);
        void unhighlight(qint64 line);
        void clearMetadata();

    public Q_SLOTS:
        void setScrollSteps(unsigned int l);
        void setLineLength(unsigned int l);
        void setGroupLength(unsigned int l);
        void setReadOnly(bool r);

    private:
        void checkState();
        void checkAndUpdate(bool calccolumns = false);
        void calcColumns();
        void drawHeader(QTextCursor& c) const;
        void drawDocument(QTextCursor& c) const;
        int documentSizeFactor() const;
        int visibleLines() const;
        qreal getNCellsWidth(int n) const;
        qreal hexColumnWidth() const;
        qreal addressWidth() const;
        qreal hexColumnX() const;
        qreal asciiColumnX() const;
        qreal endColumnX() const;
        qreal cellWidth() const;
        qreal lineHeight() const;
        QHexCursor::Position positionFromPoint(QPoint pt) const;
        QPoint absolutePoint(QPoint pt) const;
        Area areaFromPoint(QPoint pt) const;
        QTextCharFormat drawFormat(QTextCursor& c, quint8 b, const QString& s, Area area, qint64 line, qint64 column, bool checkbyte) const;
        void moveNext(bool select = false);
        void movePrevious(bool select = false);
        bool keyPressMove(QKeyEvent* e);
        bool keyPressTextInput(QKeyEvent* e);
        bool keyPressAction(QKeyEvent* e);

    protected:
        bool event(QEvent* e) override;
        void paintEvent(QPaintEvent*) override;
        void resizeEvent(QResizeEvent* e) override;
        void mousePressEvent(QMouseEvent* e) override;
        void mouseMoveEvent(QMouseEvent* e) override;
        void keyPressEvent(QKeyEvent *e) override;

    private:
        bool m_readonly{false}, m_writing{false};
        Area m_currentarea{Area::Ascii};
        QList<QRectF> m_hexcolumns;
        QTextDocument m_textdocument;
        QFontMetricsF m_fontmetrics;
        QHexDocument* m_hexdocument{nullptr};
};

