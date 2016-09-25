#include <QDebug>
#include <QApplication>
#include <QtQml>
#include <QFileInfo>

#include "weisscard.h"

WeissCard::WeissCard(QObject *parent) :
    QObject(parent)
{
    this->m_color = RedColor;
    this->m_type = CharacterType;
    this->m_level = 0;
    this->m_cost = 0;
    this->m_soul = 0;
    this->m_power = 0;
    this->m_trigger = NoneTrigger;
}

WeissCard::WeissCard(QString cid, QString name, CardColor color, CardType type,
                     int level, int cost, int soul, int power, CardTrigger trigger,
                     QString description, QObject *parent) :
    QObject(parent)
{
    this->m_id = cid;
    this->m_name = name;
    this->m_color = color;
    this->m_type = type;
    this->m_level = validLevel(level) ? level : 0;
    this->m_cost = validCost(cost) ? cost: 0;
    this->m_soul = validSoul(soul) ? soul : 0;
    this->m_power = validPower(power) ? power : 0;
    this->m_trigger = trigger;
    this->m_description = description;
}

WeissCard::WeissCard(WeissCard &card, QObject *parent) :
    QObject(parent)
{
    this->m_id = card.m_id;
    this->m_name = card.m_name;
    this->m_nameEn = card.m_nameEn;
    this->m_color = card.m_color;
    this->m_type = card.m_type;
    this->m_level = card.m_level;
    this->m_cost = card.m_cost;
    this->m_soul = card.m_soul;
    this->m_power = card.m_power;
    this->m_trigger = card.m_trigger;
    this->m_description = card.m_description;
    this->m_descriptionEn = card.m_descriptionEn;
    this->m_flavor = card.m_flavor;
    this->m_flavorEn = card.m_flavorEn;
    this->m_trait = card.m_trait;
    this->m_traitEn = card.m_traitEn;
    this->m_trait2 = card.m_trait2;
    this->m_trait2En = card.m_trait2En;
    this->m_imageFileName = card.m_imageFileName;
}

QString WeissCard::getCId()
{
    return m_id;
}

void WeissCard::setCId(QString cid)
{
    this->m_id = cid;
    emit cidChanged(cid);
}

QString WeissCard::getName()
{
    return m_name;
}

void WeissCard::setName(QString name)
{
    this->m_name = name;
    emit nameChanged(name);
}

QString WeissCard::getNameEn()
{
    return m_nameEn;
}

void WeissCard::setNameEn(QString name)
{
    if (this->m_nameEn != name)
    {
        this->m_nameEn = name;
        emit nameEnChanged(name);
    }
}

WeissCard::CardColor WeissCard::getColor()
{
    return m_color;
}

QString WeissCard::getColorString()
{
    QString result;
    if (m_color == RedColor)
    {
        result = "red";
    }
    else if (m_color == GreenColor)
    {
        result = "green";
    }
    else if (m_color == BlueColor)
    {
        result = "blue";
    }
    else if (m_color == YellowColor)
    {
        result = "yellow";
    }

    return result;
}

void WeissCard::setColor(CardColor color)
{
    this->m_color = color;
    emit colorChanged(color);
}

void WeissCard::setColor(QString color)
{
    QString temp = color.toLower();

    bool changed = false;
    if (temp == "red" && this->m_color != RedColor)
    {
        this->m_color = RedColor;
        changed = true;
    }
    else if (temp == "green" && this->m_color != GreenColor)
    {
        this->m_color = GreenColor;
        changed = true;
    }
    else if (temp == "yellow" && this->m_color != YellowColor)
    {
        this->m_color = YellowColor;
        changed = true;
    }
    else if (temp == "blue" && this->m_color != BlueColor)
    {
        this->m_color = BlueColor;
        changed = true;
    }

    if (changed)
    {
        emit colorChanged(this->m_color);
    }
}

WeissCard::CardType WeissCard::getType()
{
    return m_type;
}

QString WeissCard::getTypeString()
{
    QString result;
    if (m_type == CharacterType)
    {
        result = "character";
    }
    else if (m_type == ClimaxType)
    {
        result = "climax";
    }
    else if (m_type == EventType)
    {
        result = "event";
    }

    return result;
}

void WeissCard::setType(CardType type)
{
    this->m_type = type;
    emit typeChanged(type);
}

void WeissCard::setType(QString type)
{
    QString temp = type.toLower();
    bool changed = false;

    if (temp == "character" && this->m_type != CharacterType)
    {
        this->m_type = CharacterType;
        changed = true;
    }
    else if (temp == "climax" && this->m_type != ClimaxType)
    {
        this->m_type = ClimaxType;
        changed = true;
    }
    else if (temp == "event" && this->m_type != EventType)
    {
        this->m_type = EventType;
        changed = true;
    }

    if (changed)
    {
        emit typeChanged(this->m_type);
    }
}

int WeissCard::getLevel()
{
    return m_level;
}

void WeissCard::setLevel(int level)
{
    if (validLevel(level))
    {
        this->m_level = level;
        emit levelChanged(level);
    }
}

int WeissCard::getCost()
{
    return m_cost;
}

void WeissCard::setCost(int cost)
{
    if (validCost(cost))
    {
        this->m_cost = cost;
        emit costChanged(cost);
    }
}

int WeissCard::getSoul()
{
    return m_soul;
}

void WeissCard::setSoul(int soul)
{
    if (validSoul(soul))
    {
        this->m_soul = soul;
        emit soulChanged(soul);
    }
}

int WeissCard::getPower()
{
    return m_power;
}

void WeissCard::setPower(int power)
{
    if (validPower(power))
    {
        this->m_power = power;
        emit powerChanged(power);
    }
}

WeissCard::CardTrigger WeissCard::getTrigger()
{
    return m_trigger;
}

QString WeissCard::getTriggerString()
{
    QString result;
    if (m_trigger == NoneTrigger)
    {
        result = "";
    }
    else if (m_trigger == SoulPlus1Trigger)
    {
        result = "soul+1";
    }
    else if (m_trigger == SoulPlus2Trigger)
    {
        result = "soul+2";
    }
    else if (m_trigger == ReturnTrigger)
    {
        result = "return";
    }
    else if (m_trigger == ShotTrigger)
    {
        result = "shot";
    }
    else if (m_trigger == ComebackTrigger)
    {
        result = "comeback";
    }
    else if (m_trigger == TreasureTrigger)
    {
        result = "treasure";
    }
    else if (m_trigger == PoolTrigger)
    {
        result = "pool";
    }
    else if (m_trigger == DrawTrigger)
    {
        result = "draw";
    }

    return result;
}

void WeissCard::setTrigger(CardTrigger trigger)
{
    this->m_trigger = trigger;
    emit triggerChanged(trigger);
}

void WeissCard::setTrigger(QString trigger)
{
    QString temp = trigger.toLower();
    bool changed = false;

    if (temp == "" && this->m_trigger != NoneTrigger)
    {
        this->m_trigger = NoneTrigger;
        changed = true;
    }
    else if (temp == "soul+1" && this->m_trigger != SoulPlus1Trigger)
    {
        this->m_trigger = SoulPlus1Trigger;
        changed = true;
    }
    else if (temp == "soul+2" && this->m_trigger != SoulPlus2Trigger)
    {
        this->m_trigger = SoulPlus2Trigger;
        changed = true;
    }
    else if (temp == "return" && this->m_trigger != ReturnTrigger)
    {
        this->m_trigger = ReturnTrigger;
        changed = true;
    }
    else if (temp == "shot" && this->m_trigger != ShotTrigger)
    {
        this->m_trigger = ShotTrigger;
        changed = true;
    }
    else if (temp == "comeback" && this->m_trigger != ComebackTrigger)
    {
        this->m_trigger = ComebackTrigger;
        changed = true;
    }
    else if (temp == "treasure" && this->m_trigger != TreasureTrigger)
    {
        this->m_trigger = TreasureTrigger;
        changed = true;
    }
    else if (temp == "pool" && this->m_trigger != PoolTrigger)
    {
        this->m_trigger = PoolTrigger;
        changed = true;
    }
    else if (temp == "draw" && this->m_trigger != DrawTrigger)
    {
        this->m_trigger = DrawTrigger;
        changed = true;
    }

    if (changed)
    {
        emit triggerChanged(this->m_trigger);
    }
}

void WeissCard::setTriggerFromSQL(QString triggerCode)
{
    QString temp = triggerCode.toLower();
    if (temp == "0")
    {
        setTrigger(NoneTrigger);
    }
    else if (temp == "1")
    {
        setTrigger(SoulPlus1Trigger);
    }
    else if (temp == "2")
    {
        setTrigger(SoulPlus2Trigger);
    }
    else if (temp == "1w")
    {
        setTrigger(ReturnTrigger);
    }
    else if (temp == "1f")
    {
        setTrigger(ShotTrigger);
    }
    else if (temp == "d")
    {
        setTrigger(ComebackTrigger);
    }
    else if (temp == "g")
    {
        setTrigger(TreasureTrigger);
    }
    else if (temp == "s")
    {
        setTrigger(PoolTrigger);
    }
    else if (temp == "b")
    {
        setTrigger(DrawTrigger);
    }
}

QString WeissCard::getTriggerSQLCode()
{
    QString result = getTriggerSQLCode(m_trigger);
    return result;
}

QString WeissCard::getTriggerSQLCode(CardTrigger trigger)
{
    QString result("0");

    switch (trigger)
    {
        case NoneTrigger:
            result = "0";
            break;
        case SoulPlus1Trigger:
            result = "1";
            break;
        case SoulPlus2Trigger:
            result = "2";
            break;
        case ReturnTrigger:
            result = "1w";
            break;
        case ShotTrigger:
            result = "1f";
            break;
        case ComebackTrigger:
            result = "d";
            break;
        case TreasureTrigger:
            result = "g";
            break;
        case PoolTrigger:
            result = "s";
            break;
        case DrawTrigger:
            result = "b";
            break;
        default:
            break;
    }

    return result.toUpper();
}

QString WeissCard::getDescription()
{
    return m_description;
}

void WeissCard::setDescription(QString description)
{
    if (description != m_description)
    {
        this->m_description = description;
        emit descriptionChanged(description);
    }
}

QString WeissCard::getDescriptionEn()
{
    return m_descriptionEn;
}

void WeissCard::setDescriptionEn(QString description)
{
    if (this->m_descriptionEn != description)
    {
        this->m_descriptionEn = description;
        emit descriptionEnChanged(description);
    }
}

QString WeissCard::getFlavor()
{
    return m_flavor;
}

void WeissCard::setFlavor(QString flavor)
{
    if (m_flavor != flavor)
    {
        m_flavor = flavor;
        emit flavorChanged(flavor);
    }
}

QString WeissCard::getFlavorEn()
{
    return m_flavorEn;
}

void WeissCard::setFlavorEn(QString flavor)
{
    if (m_flavorEn != flavor)
    {
        m_flavorEn = flavor;
        emit flavorEnChanged(flavor);
    }
}

QString WeissCard::getTrait()
{
    return m_trait;
}

void WeissCard::setTrait(QString trait)
{
    if (m_trait != trait)
    {
        m_trait = trait;
        emit traitChanged(trait);
    }
}

QString WeissCard::getTraitEn()
{
    return m_traitEn;
}

void WeissCard::setTraitEn(QString trait)
{
    if (m_traitEn != trait)
    {
        m_traitEn = trait;
        emit traitEnChanged(trait);
    }
}

QString WeissCard::getTrait2()
{
    return m_trait2;
}

void WeissCard::setTrait2(QString trait)
{
    if (m_trait2 != trait)
    {
        m_trait2 = trait;
        emit trait2Changed(trait);
    }
}

QString WeissCard::getTrait2En()
{
    return m_trait2En;
}

void WeissCard::setTrait2En(QString trait)
{
    if (m_trait2En != trait)
    {
        m_trait2En = trait;
        emit trait2EnChanged(trait);
    }
}

int WeissCard::getDamageCount()
{
    int damageCount = 0;
    switch (m_trigger)
    {
        case WeissCard::SoulPlus2Trigger:
            damageCount++;
        case WeissCard::SoulPlus1Trigger:
        case WeissCard::ReturnTrigger:
        case WeissCard::ShotTrigger:
        {
            damageCount++;
            break;
        }
        default:
            break;
    }

    return damageCount;
}

/*void WeissCard::setDamageCount(int damage)
{

}
*/

QString WeissCard::getImageFileName()
{
    return m_imageFileName;
}

void WeissCard::setImageFileName(QString imageFileName)
{
    if (imageFileName != m_imageFileName)
    {
        this->m_imageFileName = imageFileName;
        emit imageFileNameChanged(imageFileName);
    }
}

QString WeissCard::getImageFilePath()
{
    QString result = "";
    QString temp = qApp->applicationDirPath() + "/deckimages/";
    QString setid = QString(m_id).remove(0, 3);
    setid = setid.left(3);
    temp += setid + "/" + m_imageFileName;

    QFileInfo tempInfo(temp);
    if (tempInfo.exists() && tempInfo.isReadable())
    {
        result = temp;
    }

    return result;
}


bool WeissCard::validLevel(int level)
{
    bool result = false;
    if (level >= 0 && level <= 3)
    {
        result = true;
    }

    return result;
}

bool WeissCard::validCost(int cost)
{
    bool result = false;
    if (cost >= 0 && cost <= 7)
    {
        result = true;
    }

    return result;
}

bool WeissCard::validSoul(int soul)
{
    bool result = false;
    if (soul >= 0 && soul <= 3)
    {
        result = true;
    }

    return result;
}

bool WeissCard::validPower(int power)
{
    bool result = false;
    if (power >= 0 && power <= 20000)
    {
        result = true;
    }

    return result;
}

void WeissCard::registerQmlType()
{
    qmlRegisterType<WeissCard>("com.mycompany.qmlcomponents", 1, 0, "WeissCard");
}
