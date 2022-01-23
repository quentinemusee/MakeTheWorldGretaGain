#include "platform.h"

Platform::Platform(QObject *parent, const qreal efficientX, const qreal efficientY, const platformType::platformType_t platformType) : Entity(parent, efficientX, efficientY),
                                                                                                                                       m_platformType(platformType),
                                                                                                                                       m_counter(0),
                                                                                                                                       m_buttonPressed(false)
{
    switch(m_platformType)
    {
        case platformType::DEFAULT_FLOOR :
            setPixmap(QPixmap(":/ressources/images/floorTest.png"));
            m_width = DEFAULT_FLOOR_WIDTH;
            m_height = DEFAULT_FLOOR_HEIGHT;

            m_spriteCounterLimit = DEFAULT_FLOOR_SPRITE_COUNT_LIMIT;
            m_frameCounterLimit  = DEFAULT_FLOOR_FRAME_COUNT_LIMIT;

            break;
        case platformType::FLOOR1 :
            setPixmap(QPixmap(":/ressources/images/floor1S.png"));
            m_width = FLOOR1_WIDTH;
            m_height = FLOOR1_HEIGHT;

            m_spriteCounterLimit = FLOOR1_SPRITE_COUNT_LIMIT;
            m_frameCounterLimit  = FLOOR1_FRAME_COUNT_LIMIT;

            break;
        case platformType::FLYINGFLOOR1 :
            setPixmap(QPixmap(":/ressources/images/flyingFloor1.png"));
            m_width = FLYINGFLOOR1_WIDTH;
            m_height = FLYINGFLOOR1_HEIGHT;

            m_spriteCounterLimit = FLYINGFLOOR1_SPRITE_COUNT_LIMIT;
            m_frameCounterLimit  = FLYINGFLOOR1_FRAME_COUNT_LIMIT;

            break;
        case platformType::PLATFORMGREY :
            setPixmap(QPixmap(":/ressources/images/platformGreyS.png"));
            m_width = PLATFORMGREY_WIDTH;
            m_height = PLATFORMGREY_HEIGHT;

            m_spriteCounterLimit = PLATFORMGREY_SPRITE_COUNT_LIMIT;
            m_frameCounterLimit  = PLATFORMGREY_FRAME_COUNT_LIMIT;

            break;

        case platformType::SHORTPIPE :
            setPixmap(QPixmap(":/ressources/images/shortPipeS.png"));
            m_width = SHORTPIPE_WIDTH;
            m_height = SHORTPIPE_HEIGHT;

            m_spriteCounterLimit = SHORTPIPE_SPRITE_COUNT_LIMIT;
            m_frameCounterLimit  = SHORTPIPE_FRAME_COUNT_LIMIT;

            break;

        case platformType::LARGEPIPE :
            setPixmap(QPixmap(":/ressources/images/largePipeS.png"));
            m_width = LARGEPIPE_WIDTH;
            m_height = LARGEPIPE_HEIGHT;

            m_spriteCounterLimit = LARGEPIPE_SPRITE_COUNT_LIMIT;
            m_frameCounterLimit  = LARGEPIPE_FRAME_COUNT_LIMIT;

            break;
        case platformType::GRID :
            setPixmap(QPixmap(":/ressources/images/gridS.png"));
            m_width = GRID_WIDTH;
            m_height = GRID_HEIGHT;

            m_spriteCounterLimit = GRID_SPRITE_COUNT_LIMIT;
            m_frameCounterLimit  = GRID_FRAME_COUNT_LIMIT;

            break;
        default:
            break;
    }
}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (m_platformType == platformType::GRID && m_buttonPressed)
        painter->drawPixmap(m_efficientX + 23, m_efficientY, pixmap(), 80, 0, 57, m_height);
    else
        painter->drawPixmap(m_efficientX, m_efficientY, pixmap(), 0, 0, m_width, m_height);
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

QPainterPath Platform::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

QRectF Platform::boundingRect() const
{
    return QRect(m_efficientX, m_efficientY, m_width, m_height);
}

void Platform::buttonPressed(QList<Entity*> *entitiesList)
{
    Character *greta = qobject_cast<Character*>(entitiesList->at(0));
    if (greta->efficientX() >= 20450 && greta->attackCooldownCounter())
        m_buttonPressed = true;
    else
        if (entitiesList->length() - ENNEMIES_POS > 1 && !greta->invincible())
            m_buttonPressed = false;
}

void Platform::open(QList<Entity*> *entitiesList)
{
    if (m_platformType == platformType::GRID && m_buttonPressed)
    {
        m_counter++;
        if (m_counter > 30)
            moveBy(0, -1);
        if (m_counter == 1110)
        {
            qobject_cast<QGraphicsScene*>(parent())->removeItem(this);
            for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
                if (entitiesList->at(i) == this)
                    entitiesList->removeAt(i);
            return;
        }
    }
}

void Platform::updateX(QList<Entity*> *entitiesList)
{
    buttonPressed(entitiesList);
    open(entitiesList);
}
