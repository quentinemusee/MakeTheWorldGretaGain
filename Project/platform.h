#ifndef PLATFORM_H
#define PLATFORM_H

#include <QPainter>
#include "entity.h"
#include "character.h"

#define DEFAULT_FLOOR_WIDTH  24000
#define DEFAULT_FLOOR_HEIGHT 400
#define FLOOR1_WIDTH         4116
#define FLOOR1_HEIGHT        215
#define FLYINGFLOOR1_WIDTH   350
#define FLYINGFLOOR1_HEIGHT  75
#define PLATFORMGREY_WIDTH   1180
#define PLATFORMGREY_HEIGHT  64

#define SHORTPIPE_WIDTH   140
#define SHORTPIPE_HEIGHT  300
#define LARGEPIPE_WIDTH   200
#define LARGEPIPE_HEIGHT  400
#define GRID_WIDTH        80
#define GRID_HEIGHT       1080

#define DEFAULT_FLOOR_SPRITE_COUNT_LIMIT 0
#define DEFAULT_FLOOR_FRAME_COUNT_LIMIT  0
#define FLOOR1_SPRITE_COUNT_LIMIT        0
#define FLOOR1_FRAME_COUNT_LIMIT         0
#define FLYINGFLOOR1_SPRITE_COUNT_LIMIT  0
#define FLYINGFLOOR1_FRAME_COUNT_LIMIT   0
#define PLATFORMGREY_SPRITE_COUNT_LIMIT  0
#define PLATFORMGREY_FRAME_COUNT_LIMIT   0

#define SHORTPIPE_SPRITE_COUNT_LIMIT  0
#define SHORTPIPE_FRAME_COUNT_LIMIT   0
#define LARGEPIPE_SPRITE_COUNT_LIMIT  0
#define LARGEPIPE_FRAME_COUNT_LIMIT   0
#define GRID_SPRITE_COUNT_LIMIT       0
#define GRID_FRAME_COUNT_LIMIT        0

/* Plateform type structure */
namespace platformType
{
    typedef enum
    {
        DEFAULT_FLOOR,
        FLOOR1,
        FLYINGFLOOR1,
        PLATFORMGREY,
        SHORTPIPE,
        LARGEPIPE,
        GRID
    } platformType_t;
}

class Platform : public Entity
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit Platform(QObject *parent = nullptr, const qreal efficientX = 0, const qreal efficientY = 0,
                          const platformType::platformType_t platformType = platformType::DEFAULT_FLOOR);

        /* Painting functions */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void incrementFrameCounter() override {return;}

        /* Collisions functions */
        QPainterPath shape() const override;
        QRectF boundingRect() const override;
        void collision(QList<Entity*> *entitiesList) override {Q_UNUSED(entitiesList); return;}

        /* Action functions */
        void die(QList<Entity*> *entitiesList = nullptr) override {Q_UNUSED(entitiesList);}
        void buttonPressed(QList<Entity*> *entitiesList = nullptr);
        void open(QList<Entity*> *entitiesList = nullptr);

        /* Update functions */
        void updateX(QList<Entity*> *entitiesList) override;

    private :
        platformType::platformType_t m_platformType;
        qsizetype m_counter;
        bool m_buttonPressed;
};

#endif // PLATFORM_H
