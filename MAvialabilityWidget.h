#ifndef MAvialabilityWidget_H
#define MAvialabilityWidget_H

#include <MWidget>
#include <MImageWidget>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>

#include <Accounts/Account>
#include <Accounts/Manager>

#include <TelepathyQt4/Account>

#include <QDBusConnection>
#include <QDBusInterface>

class MAvialabilityWidget : public MWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev);
    bool event(QEvent *event);

public:
    explicit MAvialabilityWidget(QGraphicsItem *parent = 0, Tp::AccountPtr account = Tp::AccountPtr());
    void init_state();

private:
    QString presenceToIconId(Tp::Presence presence);

    MImageWidget *m_iconService;
    MImageWidget *m_iconPresence;

    Tp::AccountPtr m_account;

    QString currentIconId;
    QString requestedIconId;

    Tp::Presence nextPresence;

    bool isFakePresence;
    bool longPressed;

    QTimer *presenceFaker;
    QTime fakeTime;

private slots:
    void onChangingPresence(bool value);
    void onCurrentPresenceChanged(const Tp::Presence &presence);
    void onRequestedPresenceChanged(const Tp::Presence &presence);
    void onRemoved();
    void onStateChanged(bool value);
    void fakerupdate();
    void openPresence();

signals:
    void accountRemoved(QGraphicsLayoutItem *item, bool action);
    void pressed();
    void released();
    void longpressed();
};

#endif // MAvialabilityWidget_H
