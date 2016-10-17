#include <QDebug>
#include <QApplication>
#include <QtQml>
#include <QFileInfo>
#include <QJsonObject>

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

WeissCard::CardColor WeissCard::getColorFromString(QString color)
{
    QString temp = color.toLower();
    CardColor result = RedColor;

    if (temp == "red")
    {
        result = RedColor;
    }
    else if (temp == "green")
    {
        result = GreenColor;
    }
    else if (temp == "yellow")
    {
        result = YellowColor;
    }
    else if (temp == "blue")
    {
        result = BlueColor;
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
    CardColor colorType = getColorFromString(color);
    if (this->m_color != colorType)
    {
        this->m_color = colorType;
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

WeissCard::CardType WeissCard::getTypeFromString(QString type)
{
    QString temp = type.toLower();
    CardType result = CharacterType;

    if (temp == "character")
    {
        result = CharacterType;
    }
    else if (temp == "climax")
    {
        result = ClimaxType;
    }
    else if (temp == "event")
    {
        result = EventType;
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
    CardType temp = getTypeFromString(type);
    if (this->m_type != temp)
    {
        this->m_type = temp;
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
    CardTrigger temp = getTriggerFromString(trigger);
    if (this->m_trigger != temp)
    {
        this->m_trigger = temp;
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

WeissCard::CardTrigger WeissCard::getTriggerFromString(QString trigger)
{
    QString temp = trigger.toLower();
    CardTrigger result = NoneTrigger;

    if (temp == "")
    {
        result = NoneTrigger;
    }
    else if (temp == "soul+1")
    {
        result = SoulPlus1Trigger;
    }
    else if (temp == "soul+2")
    {
        result = SoulPlus2Trigger;
    }
    else if (temp == "return")
    {
        result = ReturnTrigger;
    }
    else if (temp == "shot")
    {
        result = ShotTrigger;
    }
    else if (temp == "comeback")
    {
        result = ComebackTrigger;
    }
    else if (temp == "treasure")
    {
        result = TreasureTrigger;
    }
    else if (temp == "pool")
    {
        result = PoolTrigger;
    }
    else if (temp == "draw")
    {
        result = DrawTrigger;
    }

    return result;
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

void WeissCard::read(QJsonObject &jsonObj)
{
    m_id = jsonObj.value("cid").toString();
    m_name = jsonObj.value("name").toString();
    m_nameEn = jsonObj.value("name_e").toString();
    m_color = getColorFromString(jsonObj.value("color").toString());
    m_type = getTypeFromString(jsonObj.value("type").toString());
    m_level = jsonObj.value("level").toInt();
    m_cost = jsonObj.value("cost").toInt();
    m_soul = jsonObj.value("soul").toInt();
    m_power = jsonObj.value("power").toInt();
    m_trigger = getTriggerFromString(jsonObj.value("trigger").toString());
    m_description = jsonObj.value("description").toString();
    m_descriptionEn = jsonObj.value("description_e").toString();
    m_flavor = jsonObj.value("flavor").toString();
    m_flavorEn = jsonObj.value("flavor_e").toString();
    m_trait = jsonObj.value("trait").toString();
    m_traitEn = jsonObj.value("trait_e").toString();
    m_trait2 = jsonObj.value("trait2").toString();
    m_trait2En = jsonObj.value("trait2_e").toString();
    m_imageFileName = jsonObj.value("imagefilename").toString();
}

void WeissCard::write(QJsonObject &jsonObj)
{
    jsonObj.insert("cid", m_id);
    jsonObj.insert("name", m_name);
    jsonObj.insert("name_e", m_nameEn);
    jsonObj.insert("color", getColorString());
    jsonObj.insert("type", getTypeString());
    jsonObj.insert("level", m_level);
    jsonObj.insert("cost", m_cost);
    jsonObj.insert("soul", m_soul);
    jsonObj.insert("power", m_power);
    jsonObj.insert("trigger", getTriggerString());
    jsonObj.insert("description", m_description);
    jsonObj.insert("description_e", m_descriptionEn);
    jsonObj.insert("flavor", m_flavor);
    jsonObj.insert("flavor_e", m_flavorEn);
    jsonObj.insert("trait", m_trait);
    jsonObj.insert("trait_e", m_traitEn);
    jsonObj.insert("trait2", m_trait2);
    jsonObj.insert("trait2_e", m_trait2En);
    jsonObj.insert("imagefilename", m_imageFileName);
}

void WeissCard::registerQmlType()
{
    qmlRegisterType<WeissCard>("com.mycompany.qmlcomponents", 1, 0, "WeissCard");
}
