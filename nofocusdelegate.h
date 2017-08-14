#ifndef NOFOCUSDELEGATE_H
#define NOFOCUSDELEGATE_H
#include <QStyledItemDelegate>

class NoFocusDelegate : public QStyledItemDelegate
{

    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // NOFOCUSDELEGATE_H
