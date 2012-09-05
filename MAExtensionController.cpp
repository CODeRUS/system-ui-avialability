#include "MAExtensionController.h"
#include <QGraphicsLinearLayout>

MAExtensionsController::MAExtensionsController(MAExtensionsPlugin *extensionsPlugin,
                                               QGraphicsItem *parent) :
    MWidget(parent),
    m_extensionsPlugin(extensionsPlugin)
{
    setObjectName("StatusIndicatorMenuExtensionContentItem");

    setMinimumHeight(0);

    m_layout = new MLayout(this);
    m_mainLayout = new MLinearLayoutPolicy(m_layout, Qt::Vertical);
    m_mainLayout->setContentsMargins(16,8,0,8);

    a_avialability = new MAvialability(0);
    m_mainLayout->addItem(a_avialability);

    connect(a_avialability,
            SIGNAL(heightChanged()),
            this,
            SLOT(onHeight()));
    onHeight();
}

MAExtensionsController::~MAExtensionsController()
{
}

void MAExtensionsController::onHeight()
{
    if (a_avialability->maximumHeight() == 0)
        m_mainLayout->setContentsMargins(0,0,0,0);
    else
        m_mainLayout->setContentsMargins(16,8,0,8);
}
