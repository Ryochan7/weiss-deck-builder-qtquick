#ifndef WEISSCARDMODEL_H
#define WEISSCARDMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QHash>
#include <QByteArray>

#include "weisscard.h"
#include "weissdeck.h"

class WeissCardModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum CardRoles {
        CardIdRole = Qt::UserRole + 1,
        CardNameRole,
        CardColorRole,
        CardTypeRole,
        CardLevelRole,
        CardCostRole,
        CardTriggerRole,
        CardSoulRole,
        CardPowerRole,
        CardQuantityRole,
    };

    Q_ENUM(CardRoles)

    WeissCardModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    //virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE WeissCard* get(int row);
    Q_INVOKABLE WeissDeck* getDeck();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void resetCards();
    Q_INVOKABLE bool canAddCard();
    Q_INVOKABLE bool addCard(WeissCard *card, int maxAdd);
    Q_INVOKABLE void removeCard(WeissCard *card, int maxRemove);

private:
    WeissDeck cardDeck;
};

#endif // WEISSCARDMODEL_H
