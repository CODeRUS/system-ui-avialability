#ifndef APPLICATIONEXTENSIONCONTROLLER_H
#define APPLICATIONEXTENSIONCONTROLLER_H

#include <MWidget>
#include <MLayout>
#include <MLinearLayoutPolicy>

#include <QObject>

#include "MAExtensionPlugin.h"
#include "MAvialability.h"

class MStatusIndicatorMenuInterface;

class MAExtensionsController : public MWidget
{
    Q_OBJECT

public:
    explicit MAExtensionsController(MAExtensionsPlugin *extensionsPlugin, QGraphicsItem *parent = NULL);
    virtual ~MAExtensionsController();

private:
    MLayout *m_layout;
    MLinearLayoutPolicy *m_mainLayout;

    MAExtensionsPlugin *m_extensionsPlugin;

    MAvialability *a_avialability;

private slots:
    void onHeight();
};

#endif // APPLICATIONEXTENSIONCONTROLLER_H
