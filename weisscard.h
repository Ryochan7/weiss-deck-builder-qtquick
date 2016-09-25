#ifndef WEISSCARD_H
#define WEISSCARD_H

#include <QObject>
#include <QString>

class WeissCard : public QObject
{
    Q_OBJECT
public:
    enum CardColor {
        RedColor,
        GreenColor,
        BlueColor,
        YellowColor,
    };

    Q_ENUMS(CardColor)

    enum CardType {
        CharacterType,
        ClimaxType,
        EventType,
    };

    Q_ENUMS(CardType)

    enum CardTrigger {
        NoneTrigger,
        SoulPlus1Trigger,
        SoulPlus2Trigger,
        ReturnTrigger,
        ShotTrigger,
        ComebackTrigger,
        TreasureTrigger,
        PoolTrigger,
        DrawTrigger,
    };

    Q_ENUMS(CardTrigger)

    explicit WeissCard(QObject *parent = 0);
    explicit WeissCard(QString cid, QString name, CardColor color, CardType type,
                       int level, int cost, int soul, int power, CardTrigger trigger,
                       QString description, QObject *parent = 0);

    explicit WeissCard(WeissCard &card, QObject *parent = 0);

    Q_PROPERTY(QString cid READ getCId WRITE setCId NOTIFY cidChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString name_en READ getNameEn WRITE setNameEn NOTIFY nameEnChanged)
    Q_PROPERTY(CardColor color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(CardType type READ getType WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int level READ getLevel WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(int cost READ getCost WRITE setCost NOTIFY costChanged)
    Q_PROPERTY(int soul READ getSoul WRITE setSoul NOTIFY soulChanged)
    Q_PROPERTY(int power READ getPower WRITE setPower NOTIFY powerChanged)
    Q_PROPERTY(CardTrigger trigger READ getTrigger WRITE setTrigger NOTIFY triggerChanged)
    Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString descriptionEn READ getDescriptionEn WRITE setDescriptionEn NOTIFY descriptionEnChanged)
    Q_PROPERTY(QString flavor READ getFlavor WRITE setFlavor NOTIFY flavorChanged)
    Q_PROPERTY(QString flavorEn READ getFlavorEn WRITE setFlavorEn NOTIFY flavorEnChanged)

    Q_PROPERTY(QString trait READ getTrait WRITE setTrait NOTIFY traitChanged)
    Q_PROPERTY(QString traitEn READ getTraitEn WRITE setTraitEn NOTIFY traitEnChanged)
    Q_PROPERTY(QString trait2 READ getTrait2 WRITE setTrait2 NOTIFY trait2Changed)
    Q_PROPERTY(QString trait2En READ getTrait2En WRITE setTrait2En NOTIFY trait2EnChanged)

    Q_PROPERTY(int damageCount READ getDamageCount)

    Q_PROPERTY(QString imageFileName READ getImageFileName WRITE setImageFileName NOTIFY imageFileNameChanged)

    QString getCId();
    void setCId(QString cid);

    QString getName();
    void setName(QString name);

    QString getNameEn();
    void setNameEn(QString name);

    CardColor getColor();
    Q_INVOKABLE QString getColorString();
    void setColor(CardColor color);
    void setColor(QString color);

    CardType getType();
    Q_INVOKABLE QString getTypeString();
    void setType(CardType type);
    void setType(QString type);

    int getLevel();
    void setLevel(int level);

    int getCost();
    void setCost(int cost);

    int getSoul();
    void setSoul(int soul);

    int getPower();
    void setPower(int power);

    CardTrigger getTrigger();
    Q_INVOKABLE QString getTriggerString();
    QString getTriggerSQLCode();
    static QString getTriggerSQLCode(CardTrigger trigger);
    void setTrigger(CardTrigger trigger);
    void setTrigger(QString trigger);
    void setTriggerFromSQL(QString triggerCode);

    QString getDescription();
    void setDescription(QString description);

    QString getDescriptionEn();
    void setDescriptionEn(QString description);

    QString getFlavor();
    void setFlavor(QString flavor);

    QString getFlavorEn();
    void setFlavorEn(QString flavor);

    QString getTrait();
    void setTrait(QString trait);

    QString getTraitEn();
    void setTraitEn(QString trait);

    QString getTrait2();
    void setTrait2(QString trait);

    QString getTrait2En();
    void setTrait2En(QString trait);

    int getDamageCount();
    //void setDamageCount(int damage);

    QString getImageFileName();
    void setImageFileName(QString imageFileName);
    Q_INVOKABLE QString getImageFilePath();

    static void registerQmlType();


protected:
    bool validLevel(int level);
    bool validCost(int cost);
    bool validSoul(int soul);
    bool validPower(int power);

    QString m_id;
    QString m_name;
    QString m_nameEn;
    CardColor m_color;
    CardType m_type;
    int m_level;
    int m_cost;
    int m_soul;
    int m_power;
    //int m_damageCount;
    CardTrigger m_trigger;
    QString m_description;
    QString m_descriptionEn;
    QString m_flavor;
    QString m_flavorEn;
    QString m_trait;
    QString m_traitEn;
    QString m_trait2;
    QString m_trait2En;
    QString m_imageFileName;

signals:
    void cidChanged(QString value);
    void nameChanged(QString value);
    void nameEnChanged(QString value);
    void colorChanged(CardColor value);
    void typeChanged(CardType value);
    void levelChanged(int value);
    void costChanged(int value);
    void soulChanged(int value);
    void powerChanged(int value);
    void triggerChanged(CardTrigger value);
    void descriptionChanged(QString value);
    void descriptionEnChanged(QString value);
    void flavorChanged(QString value);
    void flavorEnChanged(QString value);
    void imageFileNameChanged(QString value);
    void traitChanged(QString value);
    void traitEnChanged(QString value);
    void trait2Changed(QString value);
    void trait2EnChanged(QString value);

public slots:
};

#endif // WEISSCARD_H
