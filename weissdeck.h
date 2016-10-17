#ifndef WEISSDECK_H
#define WEISSDECK_H

#include <QObject>
#include <QString>
#include <QList>
#include <QHash>

#include "weisscard.h"

class WeissDeck : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(int cardCount READ getCardCount WRITE setCardCount NOTIFY cardCountChanged)
    Q_PROPERTY(int climaxCount READ getClimaxCount WRITE setClimaxCount NOTIFY climaxCountChanged)
    Q_PROPERTY(int level0Count READ getLevel0Count WRITE setLevel0Count NOTIFY level0CountChanged)
    Q_PROPERTY(int level1Count READ getLevel1Count WRITE setLevel1Count NOTIFY level1CountChanged)
    Q_PROPERTY(int level2Count READ getLevel2Count WRITE setLevel2Count NOTIFY level2CountChanged)
    Q_PROPERTY(int level3Count READ getLevel3Count WRITE setLevel3Count NOTIFY level3CountChanged)
    Q_PROPERTY(int soulTriggerCount READ getSoulTriggerCount WRITE setSoulTriggerCount NOTIFY soulTriggerCountChanged)
    Q_PROPERTY(int eventCount READ getEventCount WRITE setEventCount NOTIFY eventCountChanged)
    Q_PROPERTY(int yellowCount READ getYellowCount WRITE setYellowCount NOTIFY yellowCountChanged)
    Q_PROPERTY(int greenCount READ getGreenCount WRITE setGreenCount NOTIFY greenCountChanged)
    Q_PROPERTY(int redCount READ getRedCount WRITE setRedCount NOTIFY redCountChanged)
    Q_PROPERTY(int blueCount READ getBlueCount WRITE setBlueCount NOTIFY blueCountChanged)

    explicit WeissDeck(QObject *parent = 0);

    int getCardCount();
    void setCardCount(int count);

    int getClimaxCount();
    void setClimaxCount(int count);

    int getLevel0Count();
    void setLevel0Count(int count);

    int getLevel1Count();
    void setLevel1Count(int count);

    int getLevel2Count();
    void setLevel2Count(int count);

    int getLevel3Count();
    void setLevel3Count(int count);

    int getSoulTriggerCount();
    void setSoulTriggerCount(int count);

    int getEventCount();
    void setEventCount(int count);

    int getYellowCount();
    void setYellowCount(int count);

    int getGreenCount();
    void setGreenCount(int count);

    int getRedCount();
    void setRedCount(int count);

    int getBlueCount();
    void setBlueCount(int count);

    QString getDeckName();
    void setDeckName(QString name);

    WeissCard* getCardAt(int index) const;
    int indexOf(WeissCard *card) const;
    bool canAddCard(WeissCard *card);
    bool addCard(WeissCard *card, int maxAdd);
    void removeCard(WeissCard *card);
    void clearDeck();
    int getTotalUniqueCardCount() const;
    int getUniqueCardCount(WeissCard *card) const;
    bool containsCard(WeissCard *card);

    Q_INVOKABLE void read(QString inputFilePath);
    Q_INVOKABLE void write(QString outputFilePath);

protected:
    void updateDeckStats(WeissCard *card, bool increment);
    WeissCard* cardToUse(WeissCard *card);

    QList<WeissCard*> m_cards;
    QList<WeissCard*> m_uniqueCards;
    QHash<QString, int> m_duplicateCardHash;
    QHash<QString, WeissCard*> m_cardRepo;

    QString m_deckName;
    int m_cardCount;
    int m_climaxCount;
    int m_level0Count;
    int m_level1Count;
    int m_level2Count;
    int m_level3Count;
    int m_soulTriggerCount;
    int m_eventCount;
    int m_yellowCount;
    int m_greenCount;
    int m_redCount;
    int m_blueCount;

signals:
    void deckNameChanged(QString value);
    void cardCountChanged(int value);
    void climaxCountChanged(int value);
    void level0CountChanged(int value);
    void level1CountChanged(int value);
    void level2CountChanged(int value);
    void level3CountChanged(int value);
    void soulTriggerCountChanged(int value);
    void eventCountChanged(int value);
    void yellowCountChanged(int value);
    void greenCountChanged(int value);
    void redCountChanged(int value);
    void blueCountChanged(int value);

public slots:
};

#endif // WEISSDECK_H
