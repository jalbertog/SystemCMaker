#ifndef PROPERTYCOMPONENT_H
#define PROPERTYCOMPONENT_H
#include <QtCore>
#include <PortItem.h>

class PropertyComponent
{
    public:
        PropertyComponent() {}
        PropertyComponent(const QString &n);
        void addPort(const QString &nPort,PortItem::Sig s);
        void setPos(const QPointF &p);
        inline const QStringList & inPortsList() const {return inPorts;};
        inline const QStringList & outPortsList() const {return outPorts;};
        int numberInPorts() const;
        int numberOutPorts() const;
        QPointF Pos() const;
        void clear();

        PropertyComponent getAndGate();
        PropertyComponent getNotGate();
        PropertyComponent getXorGate();
        PropertyComponent getOrGate();


        void operator=(const PropertyComponent &other);
    private:
        QString name;
        QPointF pos;
        QStringList inPorts;
        QStringList outPorts;
};

#endif