#ifndef SELECTABLEMODELVIEW_H
#define SELECTABLEMODELVIEW_H

#include <QObject>
#include <QWidget>
#include "../model_components/selectablemodelcomponentskeeper.h"

class SelectableModelView : public QObject
{
    Q_OBJECT

public:
    explicit SelectableModelView(
        QWidget *properties_view_widget,
        QObject *parent = nullptr
    );

    static void removeAllWidgetsFromLayout(QLayout *layout);

protected:
    void showPropertiesView(PropertiesComponent *properties_component);
    void hidePropertiesView();

private:
    QWidget *properties_view_widget;

signals:

public slots:
    void onSelectableModelSelected(SelectableModelComponentsKeeper *components_keeper);
};

#endif // SELECTABLEMODELVIEW_H
