#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <iostream>

#define GRETA_WIDTH        100
#define GRETA_HEIGHT       117
#define TRUMPETCAC_WIDTH   150
#define TRUMPETCAC_HEIGHT  180
#define TRUMPETDIS_WIDTH   150
#define TRUMPETDIS_HEIGHT  176
#define TRUMPET0_WIDTH     160
#define TRUMPET0_HEIGHT    230
#define TRUMPET1_WIDTH     160
#define TRUMPET1_HEIGHT    230
#define TRUMPET2_WIDTH     160
#define TRUMPET2_HEIGHT    230
#define TRUMPET3_WIDTH     320
#define TRUMPET3_HEIGHT    293
#define TRUMPET4_WIDTH     320
#define TRUMPET4_HEIGHT    293
#define TRUMPET5_WIDTH     199
#define TRUMPET5_HEIGHT    500
#define TRUMPET6_WIDTH     199
#define TRUMPET6_HEIGHT    500
#define TRUMPET7_WIDTH     766
#define TRUMPET7_HEIGHT    529
#define TRUMPET8_WIDTH     244
#define TRUMPET8_HEIGHT    332
#define TRUMPET9_WIDTH     187
#define TRUMPET9_HEIGHT    290
#define TRUMPET9_WIDTH     187
#define TRUMPET9_HEIGHT    290
#define TRUMPET10_WIDTH    290
#define TRUMPET10_HEIGHT   187
#define TRUMPET11_WIDTH    290
#define TRUMPET11_HEIGHT   187

#define BULLET_WIDTH       25
#define BULLET_HEIGHT      13
#define POOPBULLET1_WIDTH  100
#define POOPBULLET1_HEIGHT 100
#define POOPBULLET2_WIDTH  100
#define POOPBULLET2_HEIGHT 100
#define POOPBULLET3_WIDTH  143
#define POOPBULLET3_HEIGHT 100
#define NUCLEARBOMB_WIDTH  204
#define NUCLEARBOMB_HEIGHT 480

#define EXPLOSION_WIDTH    240
#define EXPLOSION_HEIGHT   240

/* */

#define GRETA_SPRITE_COUNT_LIMIT         4
#define GRETA_FRAME_COUNT_LIMIT          10
#define TRUMPETCAC_SPRITE_COUNT_LIMIT    3
#define TRUMPETCAC_FRAME_COUNT_LIMIT     10
#define TRUMPETDIS_SPRITE_COUNT_LIMIT    3
#define TRUMPETDIS_FRAME_COUNT_LIMIT     10
#define TRUMPET_SPRITE_COUNT_LIMIT       0
#define TRUMPET_FRAME_COUNT_LIMIT        0

#define BULLET_SPRITE_COUNT_LIMIT        0
#define BULLET_FRAME_COUNT_LIMIT         0
#define POOPBULLET_SPRITE_COUNT_LIMIT    0
#define POOPBULLET_FRAME_COUNT_LIMIT     0
#define NUCLEARBOMB_SPRITE_COUNT_LIMIT   0
#define NUCLEARBOMB_FRAME_COUNT_LIMIT    0

#define EXPLOSION_SPRITE_COUNT_LIMIT     46
#define EXPLOSION_FRAME_COUNT_LIMIT      1

#define ENNEMIES_POS 18

/* Direction structure */
namespace direction
{
    typedef enum
    {
        NONE,
        RIGHT,
        LEFT
    } direction_t;
}

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    public :
        explicit Entity(QObject *parent = nullptr, const qreal efficientX = 0, const qreal efficientY = 0) : QObject(parent),
                                                                                                             m_efficientX(efficientX),
                                                                                                             m_efficientY(efficientY),
                                                                                                             m_width(0),
                                                                                                             m_height(0),
                                                                                                             m_spriteCounter(0),
                                                                                                             m_frameCounter(0),
                                                                                                             m_spriteCounterLimit(0),
                                                                                                             m_frameCounterLimit(0),
                                                                                                             m_invincible(false)
                                                                                                             {}

        /* Getters & Setters */
        qreal efficientX() const {return m_efficientX;}
        qreal efficientY() const {return m_efficientY;}
        qreal width() const      {return m_width;}
        qreal height() const     {return m_height;}
        bool invincible() const  {return m_invincible;}
        void efficientX(const qreal efficientX)        {m_efficientX = efficientX;}
        //void efficientY(const qreal efficientY)        {m_efficientY = efficientY;}
        //void width(const qreal width)                  {m_width = width;          }
        //void height(const qreal height)                {m_height = height;        }
        void invincible(const bool invincible)         {m_invincible = invincible;}
        //void changeEfficientXBy(const qsizetype delta) {m_efficientX += delta;}
        //void changeEfficientYBy(const qsizetype delta) {m_efficientY += delta;}

        void spriteCounter(const qreal spriteCounter) {m_spriteCounter = spriteCounter; m_frameCounter = m_frameCounterLimit-1;}

        /* Utilities functions */
        float distance(const Entity *entity) const {return qSqrt(qPow((m_efficientX - entity->m_efficientX), 2) + qPow((m_efficientY - entity->m_efficientY), 2));}

        /* Painting functions */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;
        void nextFrame() {
                              m_spriteCounter++;
                              if (m_spriteCounter == m_spriteCounterLimit)
                                  m_spriteCounter = 0;
                              //this->update();
                         }
        virtual void incrementFrameCounter() = 0;
        void addItemToScene(Entity *item, QList<Entity*> *entitiesList) {
                                                                             entitiesList->append(item);
                                                                             qobject_cast<QGraphicsScene*>(parent())->addItem(item);
                                                                        }

        /* Collisions functions */
        //virtual QRectF boundingRect() const override = 0;
        virtual QRectF boundingRect() const override {return QRect(0, 0, m_width, m_height);}
        virtual void collision(QList<Entity*> *entitiesList) = 0;
        bool collideWith(const Entity *entity) const {
                                                          return (x() - 12 < entity->x() + entity->width() &&
                                                                  x() + m_width > entity->x() - 12 &&
                                                                  y() - 12 < entity->y() + entity->height() &&
                                                                  y() + m_height > entity->y() - 12);
                                                     }


        /* Action functions */
        void move(const qreal dx, const qreal dy)                        {moveBy(dx, dy); m_efficientX += dx, m_efficientY += dy;}
        void setPosition(const qreal dx, const qreal dy, const qreal y)  {setPos(dx, y); m_efficientX = dx;  m_efficientY = dy;  }
        virtual void die(QList<Entity*> *entitiesList = NULL) = 0;

        /* Update functions */
        virtual void updateX(QList<Entity*> *entitiesList) = 0;

        /* Operators */
        Entity& operator+=(qreal shift) {
                                            move((qreal)((int)(shift)), 100*(qreal)(shift-(int)(shift)));
                                            return *this;
                                        }

        friend QDebug& operator<<(QDebug &debug, const Entity &entity) {
                                                                            debug << "Entity's x : " << entity.x();
                                                                            debug << "Entity's y : " << entity.y();
                                                                            debug << "-------------------------------------------";
                                                                            debug << "Entity's efficientX : " << entity.efficientX();
                                                                            debug << "Entity's efficientY : " << entity.efficientY();
                                                                            debug << "-------------------------------------------";

                                                                            return debug;
                                                                       }

    protected :
        qreal m_efficientX, m_efficientY;
        qreal m_width, m_height;
        qsizetype m_spriteCounter, m_frameCounter;
        qsizetype m_spriteCounterLimit, m_frameCounterLimit;
        bool m_invincible;
};

#endif // ENTITY_H
