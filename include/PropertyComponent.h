#ifndef PROPERTYCOMPONENT_H
#define PROPERTYCOMPONENT_H
#include <QtCore>
#include <PortItem.h>

/**
 * @brief The PropertyComponent class for hadled the property of gates
 *    And used for xml
 */
class PropertyComponent
{
    public:
        PropertyComponent() {}
        PropertyComponent(const QString &n);
        void addPort(const QString &nPort,PortItem::Sig s);
        void setPos(const QPointF &p);
        inline const QStringList & inPortsList() const {return inPorts;}
        inline const QStringList & outPortsList() const {return outPorts;}
        int numberInPorts() const;
        int numberOutPorts() const; 
        QPointF Pos() const;
        void clear();

        PropertyComponent getAndGate();
        PropertyComponent getNotGate();
        PropertyComponent getXorGate();
        PropertyComponent getOrGate();

        QString name;
        
        void operator=(const PropertyComponent &other);
    private:
        QPointF pos;
        QStringList inPorts;
        QStringList outPorts;
};

#endif
