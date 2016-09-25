#ifndef WEISSCARDFULLMODEL_H
#define WEISSCARDFULLMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QHash>
#include <QByteArray>
#include <QSqlDatabase>
#include <QVariantMap>

#include "weisscard.h"

class WeissCardFullModel : public QAbstractTableModel
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
        CardSoulRole,
        CardPowerRole,
    };

    Q_ENUM(CardRoles)

    explicit WeissCardFullModel(QObject *parent = 0);

    Q_PROPERTY(int resultCount READ getResultCount NOTIFY resultCountChanged)

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    //virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE WeissCard* get(int row);
    Q_INVOKABLE void searchDatabase(QVariantMap map);
    int getResultCount();

protected:
    QList<WeissCard*> m_testData;
    QSqlDatabase m_db;

signals:
    void resultCountChanged(int value);

public slots:
};

#endif // WEISSCARDFULLMODEL_H
