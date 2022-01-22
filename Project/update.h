#ifndef UPDATE_H
#define UPDATE_H

#include <QTimer>

#define UPDATE_PERIOD 16

class Update : public QTimer
{
    Q_OBJECT
    public :
        explicit Update(QObject *parent = nullptr) : QTimer(parent) {
                                                                        connect(this, SIGNAL(timeout()), parent, SLOT(updateX()));
                                                                        start(UPDATE_PERIOD);
                                                                    }
};

#endif // UPDATE_H
