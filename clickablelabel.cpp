#include "clickablelabel.h"

#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(const QString& text, int requestId, QWidget *parent = nullptr)
        : QLabel(text, parent), m_requestId(requestId)
    {
        setCursor(Qt::PointingHandCursor);
    }

signals:
    void clicked(int requestId);

protected:
    void mousePressEvent(QMouseEvent *event) override
    {
        Q_UNUSED(event);
        emit clicked(m_requestId);
    }

private:
    int m_requestId;
};

#endif // CLICKABLELABEL_H

