#include <QListIterator>

#include "weisscardmodel.h"

WeissCardModel::WeissCardModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int WeissCardModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return cardDeck.getTotalUniqueCardCount();
}

int WeissCardModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 10;
}

QVariant WeissCardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= cardDeck.getTotalUniqueCardCount())
    {
        return QVariant();
    }

    WeissCard *val = cardDeck.getCardAt(index.row());

    switch (role) {
    case Qt::DisplayRole:
    case CardIdRole:
    {
        QString temp = val->getCId();
        if (temp.length() > 0)
        {
            temp[0] = temp.at(0).toTitleCase();
        }

        return QVariant::fromValue(temp);
    }

    case CardNameRole:
    {
        QString temp = val->getName();
        if (temp.length() > 0)
        {
            temp[0] = temp.at(0).toTitleCase();
        }

        return QVariant::fromValue(temp);
    }
    case CardColorRole:
    {
        QString temp = val->getColorString();
        if (temp.length() > 0)
        {
            temp[0] = temp.at(0).toTitleCase();
        }

        return QVariant::fromValue(temp);
    }
    case CardTypeRole:
    {
        QString temp = val->getTypeString();
        if (temp.length() > 0)
        {
            temp[0] = temp.at(0).toTitleCase();
        }

        return QVariant::fromValue(temp);
    }
    case CardLevelRole:
        return QVariant::fromValue(val->getLevel());
    case CardCostRole:
        return QVariant::fromValue(val->getCost());
    case CardTriggerRole:
    {
        QString temp = val->getTriggerString();
        if (temp.length() > 0)
        {
            temp[0] = temp.at(0).toTitleCase();
        }

        return QVariant::fromValue(temp);
    }
    case CardSoulRole:
        return QVariant::fromValue(val->getSoul());
    case CardPowerRole:
        return QVariant::fromValue(val->getPower());
    case CardQuantityRole:
        return QVariant::fromValue(cardDeck.getUniqueCardCount(val));
    default:
        return QVariant();
    }
}

/*QVariant WeissCardModel::headerData(int section,
                                    Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    switch (section)
    {
    case 0:

    }

    return
}
*/

QHash<int, QByteArray> WeissCardModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[CardIdRole] = "id";
    roles[CardNameRole] = "name";
    roles[CardColorRole] = "color";
    roles[CardTypeRole] = "type";
    roles[CardLevelRole] = "level";
    roles[CardCostRole] = "cost";
    roles[CardTriggerRole] = "trigger";
    roles[CardSoulRole] = "soul";
    roles[CardPowerRole] = "power";
    roles[CardQuantityRole] = "quantity";

    return roles;
}

WeissCard* WeissCardModel::get(int row)
{
    WeissCard *result = 0;
    if (row < 0 || row >= cardDeck.getTotalUniqueCardCount())
    {
        result = 0;
    }
    else
    {
        result = cardDeck.getCardAt(row);
    }

    return result;
}

bool WeissCardModel::canAddCard()
{
    return true;
}

void WeissCardModel::clear()
{
    beginResetModel();
    cardDeck.clearDeck();
    endResetModel();
}

bool WeissCardModel::addCard(WeissCard *card, int maxAdd)
{
    bool result = false;

    if (cardDeck.canAddCard(card))
    {
        int currentcount = cardDeck.getTotalUniqueCardCount();
        int index = currentcount;
        if (cardDeck.containsCard(card))
        {
            index = cardDeck.indexOf(card);
            cardDeck.addCard(card, maxAdd);
            emit dataChanged(createIndex(index, 0), createIndex(index, 0));
        }
        else
        {
            beginInsertRows(QModelIndex(), index, index);
            cardDeck.addCard(card, maxAdd);
            endInsertRows();
        }

        result = true;
    }

    return result;
}

void WeissCardModel::removeCard(WeissCard *card, int maxRemove)
{
    for (int i = 0; i < maxRemove; i++)
    {
        if (cardDeck.containsCard(card))
        {
            int index = cardDeck.indexOf(card);

            if (cardDeck.getUniqueCardCount(card) <= 1)
            {
                beginRemoveRows(QModelIndex(), index, index);
                cardDeck.removeCard(card);
                endRemoveRows();
            }
            else
            {
                cardDeck.removeCard(card);
                emit dataChanged(createIndex(index, 0), createIndex(index, 0));
            }
        }
    }
}

WeissDeck* WeissCardModel::getDeck()
{
    return &cardDeck;
}
