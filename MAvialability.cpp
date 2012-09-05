#include "MAvialability.h"
#include "MAvialabilityWidget.h"
#include <gq/GConfItem>

MAvialability::MAvialability(QGraphicsItem *parent):
    MWidget(parent)
{
    setMaximumWidth(460);
    setMinimumWidth(460);

    m_layout = new MLayout(this);
    m_layout->setMaximumWidth(460);
    m_layout->setMinimumWidth(460);
    m_mainLayout = new MFlowLayoutPolicy(m_layout);
    m_mainLayout->setVerticalSpacing(16);
    m_mainLayout->setHorizontalSpacing(12);
    m_mainLayout->setContentsMargins(0,0,0,0);

    Tp::registerTypes();

    const QDBusConnection &bus = QDBusConnection::sessionBus();
    accountFactory =        Tp::AccountFactory::create(bus,
         Tp::Features() << Tp::Account::FeatureCore
                        << Tp::Account::FeatureAvatar
                        << Tp::Account::FeatureCapabilities
                        << Tp::Account::FeatureProfile
                        << Tp::Account::FeatureProtocolInfo);
    connectionFactory =     Tp::ConnectionFactory::create(bus,
         Tp::Features() << Tp::Connection::FeatureConnected
                        << Tp::Connection::FeatureCore
                        << Tp::Connection::FeatureRoster
                        << Tp::Connection::FeatureSimplePresence
                        << Tp::Connection::FeatureRosterGroups);
    channelFactory =        Tp::ChannelFactory::create(bus);
    contactFactory =        Tp::ContactFactory::create(
         Tp::Features() << Tp::Contact::FeatureAlias
                        << Tp::Contact::FeatureAvatarToken
                        << Tp::Contact::FeatureAvatarData
                        << Tp::Contact::FeatureSimplePresence
                        << Tp::Contact::FeatureInfo
                        << Tp::Contact::FeatureLocation
                        << Tp::Contact::FeatureCapabilities);
    mAM =                   Tp::AccountManager::create(bus,
                                                       accountFactory,
                                                       connectionFactory,
                                                       channelFactory,
                                                       contactFactory);

    connect(mAM->becomeReady(Tp::AccountManager::FeatureCore),
                SIGNAL(finished(Tp::PendingOperation*)),
            SLOT(onReadyLoad(Tp::PendingOperation*)));
}

void MAvialability::onReadyLoad(Tp::PendingOperation *op)
{
    Q_UNUSED(op);

    mAccSet = mAM->validAccounts();

    foreach (Tp::AccountPtr account, mAccSet->accounts())
        if (!account->cmName().count(QRegExp("ring|mmscm")))
        {
            connect(account->becomeReady(),
                    SIGNAL(finished(Tp::PendingOperation*)),
                    SLOT(onAccountReady(Tp::PendingOperation*)));
        }

    connect(mAM.data(),
            SIGNAL(newAccount(Tp::AccountPtr)),
            SLOT(onNewAccount(Tp::AccountPtr)));
}


void MAvialability::addAccount(Tp::AccountPtr newAccount)
{
     MAvialabilityWidget *widget = new MAvialabilityWidget(this, newAccount);
     m_mainLayout->addItem(widget);

     connect(widget,
             SIGNAL(accountRemoved(QGraphicsLayoutItem*, bool)),
             SLOT(onAccountRemoved(QGraphicsLayoutItem*, bool)));

     widget->init_state();

     if (m_mainLayout->count() == 0)
         m_layout->setMaximumHeight(0);
     //why i have unwanted extra space under icons without this line!?
     else
         m_layout->setMaximumHeight(m_mainLayout->rowCount() * 64 + m_mainLayout->verticalSpacing() * (m_mainLayout->rowCount()-1));

     emit heightChanged();

     //GConfItem("/apps/system-ui-avialability/rowCount").set(m_mainLayout->rowCount());
}

void MAvialability::onNewAccount(Tp::AccountPtr newaccount)
{
    if (!newaccount->isReady())
        connect(newaccount->becomeReady(),
                SIGNAL(finished(Tp::PendingOperation*)),
                SLOT(onAccountReady(Tp::PendingOperation*)));
    else
        addAccount(newaccount);
}

void MAvialability::onAccountReady(Tp::PendingOperation *op)
{
    Tp::AccountPtr account = Tp::AccountPtr::staticCast(op->object());
    addAccount(account);
}

void MAvialability::onAccountRemoved(QGraphicsLayoutItem *item, bool value)
{
    if (value)
        m_mainLayout->addItem(item);
    else
        m_mainLayout->removeItem(item);
}

