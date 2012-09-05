#include "MAExtensionPlugin.h"
#include "MAExtensionController.h"

Q_EXPORT_PLUGIN2(avialabilityapplet, MAExtensionsPlugin)

MAExtensionsPlugin::MAExtensionsPlugin(QObject *parent) :
    statusIndicatorMenu(0),
    m_extensionsController(0)
{
    Q_UNUSED(parent)
}

void MAExtensionsPlugin::setStatusIndicatorMenuInterface(MStatusIndicatorMenuInterface &menuInterface)
{
    statusIndicatorMenu = &menuInterface;
}

MStatusIndicatorMenuInterface *MAExtensionsPlugin::statusIndicatorMenuInterface() const
{
    return statusIndicatorMenu;
}

bool MAExtensionsPlugin::initialize(const QString &)
{
    m_extensionsController = new MAExtensionsController(this);

    return true;
}

QGraphicsWidget *MAExtensionsPlugin::widget()
{
    return m_extensionsController;
}
