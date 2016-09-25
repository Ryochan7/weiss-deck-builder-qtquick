#include <QDebug>
#include <QListIterator>

#include "weissdeck.h"

WeissDeck::WeissDeck(QObject *parent) : QObject(parent),
    m_deckName("Untitled")
{
    m_cardCount = 0;
    m_climaxCount = 0;
    m_level0Count = 0;
    m_level1Count = 0;
    m_level2Count = 0;
    m_level3Count = 0;
    m_soulTriggerCount = 0;
    m_eventCount = 0;
    m_yellowCount = 0;
    m_greenCount = 0;
    m_redCount = 0;
    m_blueCount = 0;
}

int WeissDeck::getCardCount()
{
    return m_cardCount;
}

void WeissDeck::setCardCount(int count)
{
    if (m_cardCount != count)
    {
        m_cardCount = count;
        emit cardCountChanged(count);
    }
}

int WeissDeck::getClimaxCount()
{
    return m_climaxCount;
}

void WeissDeck::setClimaxCount(int count)
{
    if (m_climaxCount != count)
    {
        m_climaxCount = count;
        emit climaxCountChanged(count);
    }
}

int WeissDeck::getLevel0Count()
{
    return m_level0Count;
}

void WeissDeck::setLevel0Count(int count)
{
    if (m_level0Count != count)
    {
        m_level0Count = count;
        emit level0CountChanged(count);
    }
}

int WeissDeck::getLevel1Count()
{
    return m_level1Count;
}

void WeissDeck::setLevel1Count(int count)
{
    if (m_level1Count != count)
    {
        m_level1Count = count;
        emit level1CountChanged(count);
    }
}

int WeissDeck::getLevel2Count()
{
    return m_level2Count;
}

void WeissDeck::setLevel2Count(int count)
{
    if (m_level2Count != count)
    {
        m_level2Count = count;
        emit level2CountChanged(count);
    }
}

int WeissDeck::getLevel3Count()
{
    return m_level3Count;
}

void WeissDeck::setLevel3Count(int count)
{
    if (m_level3Count != count)
    {
        m_level3Count = count;
        emit level3CountChanged(count);
    }
}

int WeissDeck::getSoulTriggerCount()
{
    return m_soulTriggerCount;
}

void WeissDeck::setSoulTriggerCount(int count)
{
    if (m_soulTriggerCount != count)
    {
        m_soulTriggerCount = count;
        emit soulTriggerCountChanged(count);
    }
}

int WeissDeck::getEventCount()
{
    return m_eventCount;
}

void WeissDeck::setEventCount(int count)
{
    if (m_eventCount != count)
    {
        m_eventCount = count;
        emit eventCountChanged(count);
    }
}

int WeissDeck::getYellowCount()
{
    return m_yellowCount;
}

void WeissDeck::setYellowCount(int count)
{
    if (m_yellowCount != count)
    {
        m_yellowCount = count;
        emit yellowCountChanged(count);
    }
}

int WeissDeck::getGreenCount()
{
    return m_greenCount;
}

void WeissDeck::setGreenCount(int count)
{
    if (m_greenCount != count)
    {
        m_greenCount = count;
        emit greenCountChanged(count);
    }
}

int WeissDeck::getRedCount()
{
    return m_redCount;
}

void WeissDeck::setRedCount(int count)
{
    if (m_redCount != count)
    {
        m_redCount = count;
        emit redCountChanged(count);
    }
}

int WeissDeck::getBlueCount()
{
    return m_blueCount;
}

void WeissDeck::setBlueCount(int count)
{
    if (m_blueCount != count)
    {
        m_blueCount = count;
        emit blueCountChanged(count);
    }
}

QString WeissDeck::getDeckName()
{
    return m_deckName;
}

void WeissDeck::setDeckName(QString name)
{
    if (m_deckName != name)
    {
        m_deckName = name;
        emit deckNameChanged(name);
    }
}

WeissCard* WeissDeck::getCardAt(int index) const
{
    WeissCard *temp = 0;
    if (index >= 0 && index < m_uniqueCards.size())
    {
        temp = m_uniqueCards.at(index);
    }

    return temp;
}

int WeissDeck::indexOf(WeissCard *card) const
{
    int index = m_uniqueCards.indexOf(card);
    if (index == -1)
    {
        index = m_uniqueCards.indexOf(m_cardRepo.value(card->getCId()));
    }

    return index;
}

bool WeissDeck::canAddCard(WeissCard *card)
{
    bool result = true;
    if (m_cards.size() >= 50)
    {
        result = false;
    }
    else if (m_duplicateCardHash.contains(card->getCId()) &&
             m_duplicateCardHash.value(card->getCId()) >= 4)
    {
        result = false;
    }

    return result;
}

bool WeissDeck::addCard(WeissCard *card, int maxAdd)
{
    bool result = canAddCard(card);
    if (result)
    {
        for (int i = 0; i < maxAdd && canAddCard(card); i++)
        {
            WeissCard *temp = 0;
            if (!m_duplicateCardHash.contains(card->getCId()))
            {
                temp = new WeissCard(*card, this);
                m_uniqueCards.append(temp);
                m_cardRepo.insert(card->getCId(), temp);
            }
            else
            {
                temp = m_cardRepo.value(card->getCId());
            }

            m_cards.append(temp);

            int count = 1;
            if (m_duplicateCardHash.contains(temp->getCId()))
            {
                count = m_duplicateCardHash.value(temp->getCId()) + 1;
            }

            m_duplicateCardHash.insert(temp->getCId(), count);

            updateDeckStats(temp, true);
        }
    }

    return result;
}

void WeissDeck::removeCard(WeissCard *card)
{
    if (m_cardRepo.contains(card->getCId()))
    {
        WeissCard *temp = m_cardRepo.value(card->getCId());
        int index = m_cards.indexOf(temp);
        m_cards.removeAt(index);

        if (m_duplicateCardHash.contains(temp->getCId()))
        {
            int count = m_duplicateCardHash.value(temp->getCId()) - 1;
            if (count <= 0)
            {
                m_duplicateCardHash.remove(temp->getCId());
                m_uniqueCards.removeAll(temp);
                m_cardRepo.remove(temp->getCId());
                delete temp;
                temp = 0;
            }
            else
            {
                m_duplicateCardHash.insert(card->getCId(), count);
            }
        }

        updateDeckStats(card, false);
    }
}

void WeissDeck::updateDeckStats(WeissCard *card, bool increment)
{
    int offset = increment ? 1 : -1;
    setCardCount(m_cardCount + offset);

    if (card->getType() == WeissCard::ClimaxType)
    {
        setClimaxCount(m_climaxCount + offset);
    }

    if (card->getLevel() == 0)
    {
        setLevel0Count(m_level0Count + offset);
    }
    else if (card->getLevel() == 1)
    {
        setLevel1Count(m_level1Count + offset);
    }
    else if (card->getLevel() == 2)
    {
        setLevel2Count(m_level2Count + offset);
    }
    else if (card->getLevel() == 3)
    {
        setLevel3Count(m_level3Count + offset);
    }

    if (card->getType() == WeissCard::EventType)
    {
        setEventCount(m_eventCount + offset);
    }

    if (card->getColor() == WeissCard::YellowColor)
    {
        setYellowCount(m_yellowCount + offset);
    }
    else if (card->getColor() == WeissCard::GreenColor)
    {
        setGreenCount(m_greenCount + offset);
    }
    else if (card->getColor() == WeissCard::RedColor)
    {
        setRedCount(m_redCount + offset);
    }
    else if (card->getColor() == WeissCard::BlueColor)
    {
        setBlueCount(m_blueCount + offset);
    }

    if (card->getTrigger() == WeissCard::SoulPlus2Trigger)
    {
        setSoulTriggerCount(m_soulTriggerCount + 2);
    }
    else if (card->getTrigger() == WeissCard::SoulPlus1Trigger)
    {
        setSoulTriggerCount(m_soulTriggerCount + 1);
    }
    else if (card->getTrigger() == WeissCard::ReturnTrigger)
    {
        setSoulTriggerCount(m_soulTriggerCount + 1);
    }
    else if (card->getTrigger() == WeissCard::ShotTrigger)
    {
        setSoulTriggerCount(m_soulTriggerCount + 1);
    }
}

WeissCard* WeissDeck::cardToUse(WeissCard *card)
{
    WeissCard *temp = card;
    if (m_cardRepo.contains(card->getCId()))
    {
        temp = m_cardRepo.value(card->getCId());
    }

    return temp;
}

int WeissDeck::getTotalUniqueCardCount() const
{
    return m_duplicateCardHash.size();
}

int WeissDeck::getUniqueCardCount(WeissCard *card) const
{
    int result = 0;
    if (m_duplicateCardHash.contains(card->getCId()))
    {
        result = m_duplicateCardHash.value(card->getCId());
    }

    return result;
}

void WeissDeck::clearDeck()
{
    QListIterator<WeissCard*> iter(m_uniqueCards);
    iter.toBack();
    while (iter.hasPrevious())
    {
        WeissCard *temp = iter.previous();
        if (temp)
        {
            delete temp;
            temp = 0;
        }
    }

    m_cardRepo.clear();
    m_duplicateCardHash.clear();
    m_uniqueCards.clear();
    m_cards.clear();

    setCardCount(0);
    setClimaxCount(0);
    setLevel0Count(0);
    setLevel1Count(0);
    setLevel2Count(0);
    setLevel3Count(0);
    setSoulTriggerCount(0);
    setEventCount(0);
    setYellowCount(0);
    setGreenCount(0);
    setRedCount(0);
    setBlueCount(0);
}

bool WeissDeck::containsCard(WeissCard *card)
{
    return m_duplicateCardHash.contains(card->getCId());
}
