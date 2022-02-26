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
        const QHexOptions& options() const;
        void setOptions(const QHexOptions& options);
        void setDocument(QHexDocument* doc);
        void setByteColor(quint8 b, QHexColor c);
        void setByteForeground(quint8 b, QColor c);
        void setByteBackground(quint8 b, QColor c);
        void setReadOnly(bool r);

    public Q_SLOTS:
        void setLineLength(int l);
        void setGroupLength(int l);

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
        QTextCharFormat drawFormat(QTextCursor& c, quint8 b, const QString& s, Area area, qint64 line, qint64 column) const;
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

