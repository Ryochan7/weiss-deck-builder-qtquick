#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QDir>
#include <QApplication>

#include "weisscardfullmodel.h"

WeissCardFullModel::WeissCardFullModel(QObject *parent) :
    QAbstractTableModel(parent),
    m_db()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(qApp->applicationDirPath() + QDir::separator() + "CardData.sqlite");
    m_db.open();

    QSqlQuery query(m_db);
    query.prepare("select cardid, name, color, type, level, cost, soul, power, "
                  "trigger, rule, name_e, rule_e, flavor, flavor_e, trait1, trait1_e, trait2, trait2_e, imagefilename from cardtable");
    query.exec();

    while (query.next())
    {
        WeissCard *temp = new WeissCard(this);
        temp->setCId(query.value(0).toString());
        temp->setName(query.value(1).toString());
        temp->setColor(query.value(2).toString());
        temp->setType(query.value(3).toString());
        temp->setLevel(query.value(4).toInt());
        temp->setCost(query.value(5).toInt());
        temp->setSoul(query.value(6).toInt());
        temp->setPower(query.value(7).toInt());
        temp->setTriggerFromSQL(query.value(8).toString());
        temp->setDescription(query.value(9).toString());
        temp->setNameEn(query.value(10).toString());
        temp->setDescriptionEn(query.value(11).toString());
        temp->setFlavor(query.value(12).toString());
        temp->setFlavorEn(query.value(13).toString());

        temp->setTrait(query.value(14).toString());
        temp->setTraitEn(query.value(15).toString());
        temp->setTrait2(query.value(16).toString());
        temp->setTrait2En(query.value(17).toString());
        temp->setImageFileName(query.value(18).toString());

        m_testData.append(temp);
    }
}

int WeissCardFullModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_testData.size();
}
int WeissCardFullModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 8;
}
QVariant WeissCardFullModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_testData.size())
    {
        return QVariant();
    }

    WeissCard *val = m_testData.at(index.row());

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
    case CardSoulRole:
        return QVariant::fromValue(val->getSoul());
    case CardPowerRole:
        return QVariant::fromValue(val->getPower());
    default:
        return QVariant();
    }
}

//QVariant WeissCardFullModel::headerData(int section, Qt::Orientation orientation, int role) const;
QHash<int, QByteArray> WeissCardFullModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[CardIdRole] = "id";
    roles[CardNameRole] = "name";
    roles[CardColorRole] = "color";
    roles[CardTypeRole] = "type";
    roles[CardLevelRole] = "level";
    roles[CardCostRole] = "cost";
    roles[CardSoulRole] = "soul";
    roles[CardPowerRole] = "power";

    return roles;
}

WeissCard* WeissCardFullModel::get(int row)
{
    WeissCard *result = 0;
    if (row < 0 || row >= m_testData.size())
    {
        result = 0;
    }
    else
    {
        result = m_testData.at(row);
    }

    return result;
}

void WeissCardFullModel::searchDatabase(QVariantMap map)
{
    QStringList whereStringList;
    QVariantList fromBindList;
    if (map.contains("cardid") && !map.value("cardid").toString().isEmpty())
    {
        whereStringList.append("cardid LIKE ?");
        QString temp = QString("%%1\%").arg(map.value("cardid").toString());
        fromBindList.append(QVariant::fromValue(temp));
    }

    if (map.contains("name") && !map.value("name").toString().isEmpty())
    {
        whereStringList.append("name LIKE ?");
        QString temp = QString("%%1\%").arg(map.value("name").toString());
        fromBindList.append(QVariant::fromValue(temp));
    }

    if (map.contains("color") && !map.value("color").toString().simplified().isEmpty())
    {
        whereStringList.append("color=?");
        fromBindList.append(map.value("color"));
    }

    if (map.contains("type") && !map.value("type").toString().simplified().isEmpty())
    {
        whereStringList.append("type=?");
        fromBindList.append(map.value("type"));
    }

    if (map.contains("trigger") && !map.value("trigger").toString().simplified().isEmpty())
    {
        whereStringList.append("trigger=?");
        QString temp;
        QString value = map.value("trigger").toString().toLower();
        if (value == "none")
        {
            temp = WeissCard::getTriggerSQLCode(WeissCard::NoneTrigger);
        }
        else if (value == "soul+1")
        {
            temp = WeissCard::getTriggerSQLCode(WeissCard::SoulPlus1Trigger);
        }
        else if (value == "soul+2")
        {
            temp = WeissCard::getTriggerSQLCode(WeissCard::SoulPlus2Trigger);
        }
        else if (value == "return")
        {
            temp = WeissCard::getTriggerSQLCode(WeissCard::ReturnTrigger);
        }
        else if (value == "shot")
        {
            temp = WeissCard::getTriggerSQLCode(WeissCard::ShotTrigger);
        }
        else if (value == "comeback")
        {
            temp = WeissCard::getTriggerSQLCode(WeissCard::ComebackTrigger);
        }
        else if (value == "treasure")
        {
            temp = WeissCard::getTriggerSQLCode(WeissCard::TreasureTrigger);
        }

        fromBindList.append(QVariant::fromValue(temp));
    }

    if (map.contains("power") && !map.value("power").toString().isEmpty())
    {
        whereStringList.append("power=?");
        fromBindList.append(map.value("power"));
    }

    if (map.contains("cost") && !map.value("cost").toString().isEmpty())
    {
        whereStringList.append("cost=?");
        fromBindList.append(map.value("cost"));
    }

    if (map.contains("soul") && !map.value("soul").toString().simplified().isEmpty())
    {
        whereStringList.append("soul=?");
        fromBindList.append(map.value("soul"));
    }

    if (map.contains("level") && !map.value("level").toString().simplified().isEmpty())
    {
        whereStringList.append("level=?");
        fromBindList.append(map.value("level"));
    }

    if (map.contains("trait") && !map.value("trait").toString().isEmpty())
    {
        whereStringList.append("trait LIKE ?");
        QString temp = QString("%%1\%").arg(map.value("trait").toString());
        fromBindList.append(QVariant::fromValue(temp));
    }

    if (map.contains("ability") && !map.value("ability").toString().isEmpty())
    {
        whereStringList.append("ability LIKE ?");
        QString temp = QString("%%1\%").arg(map.value("ability").toString());
        fromBindList.append(QVariant::fromValue(temp));
    }

    QSqlQuery query(m_db);
    QString fromString = "select cardid, name, color, type, level, cost, soul, power, "
                         "trigger, rule, name_e, rule_e, flavor, flavor_e, trait1, trait1_e, trait2, trait2_e, imagefilename";
    fromString.append(" from cardtable");
    if (whereStringList.size() > 0)
    {
        fromString.append(" where ");
        fromString.append(whereStringList.join(" AND "));
    }

    query.prepare(fromString);
    QListIterator<QVariant> iter(fromBindList);
    while (iter.hasNext())
    {
        query.addBindValue(iter.next());
    }

    query.exec();

    beginResetModel();

    int count = 0;
    QListIterator<WeissCard*> iter2(m_testData);
    iter2.toBack();
    while (iter2.hasPrevious())
    {
        WeissCard *temp = iter2.previous();
        if (temp)
        {
            //temp->deleteLater();
            delete temp;
            temp = 0;
        }
    }

    m_testData.clear();
    while (query.next())
    {
        count++;

        WeissCard *temp = new WeissCard(this);
        temp->setCId(query.value(0).toString());
        temp->setName(query.value(1).toString());
        temp->setColor(query.value(2).toString());
        temp->setType(query.value(3).toString());
        temp->setLevel(query.value(4).toInt());
        temp->setCost(query.value(5).toInt());
        temp->setSoul(query.value(6).toInt());
        temp->setPower(query.value(7).toInt());
        temp->setTriggerFromSQL(query.value(8).toString());
        temp->setDescription(query.value(9).toString());
        temp->setNameEn(query.value(10).toString());
        temp->setDescriptionEn(query.value(11).toString());
        temp->setFlavor(query.value(12).toString());
        temp->setFlavorEn(query.value(13).toString());

        temp->setTrait(query.value(14).toString());
        temp->setTraitEn(query.value(15).toString());
        temp->setTrait2(query.value(16).toString());
        temp->setTrait2En(query.value(17).toString());
        temp->setImageFileName(query.value(18).toString());

        m_testData.append(temp);
    }

    endResetModel();
    emit resultCountChanged(m_testData.size());
}

int WeissCardFullModel::getResultCount()
{
    return m_testData.size();
}
