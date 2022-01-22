#ifndef INGAMESCENE_H
#define INGAMESCENE_H

#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QPixmap>
#include <QElapsedTimer>
#include "entity.h"
#include "greta.h"
#include "trumpetcac.h"
#include "trumpetdis.h"
#include "trumpet.h"
#include "platform.h"
#include "background.h"

#include "bullet.h"
#include "poopbullet.h"
#include "nuclearbomb.h"

class InGameScene : public QGraphicsScene
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit InGameScene(QObject *parent = nullptr, const QRect rect = QRect(0, 0, 1920, 1080));

        /* Destructor */
        virtual ~InGameScene();

        /* Setup functions */
        void initEnnemies();
        void deleteEnnemies();

        /* Getters */
        Greta *greta() const                 {return m_greta;       }
        QList<Entity*> *entitiesList() const {return m_entitiesList;}
        QElapsedTimer *elapsedTimer() const  {return m_elapsedTimer;}

        /* Action functions */
        void addItemToScene(Entity *item);
        void restart();
        void udpateInvincibleText();

    private :
        QRect m_rect;
        Greta *m_greta;
        QList<Entity*> *m_entitiesList;
        QElapsedTimer *m_elapsedTimer;
        bool m_firstFrame;
};

#endif // INGAMESCENE_H
