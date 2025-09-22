#ifndef PairedDeviceSelector_H
#define PairedDeviceSelector_H

#include "Device.h"
#include <QMenu>
#include <string>
#include <list>
#include <vector>

class PairedDeviceSelector : public QObject
{
    Q_OBJECT

public:
    PairedDeviceSelector( QMenu& menu );
    virtual ~PairedDeviceSelector();

    void onUpdatedList( const std::vector<Device>& devices );

private:
    class Action : public QAction
    {
    public:
        Action( QMenu& menu, const Device& device );
        virtual ~Action();

        inline const std::string& name() const
        {
            return device_.name();
        }

        inline const std::string& macAddress() const
        {
            return device_.macAddress();
        }

    private:
        const Device device_;
    };

    QMenu& menu_;
    std::list<Action*> actions_;

    void clearOldActions();

signals:
    void deviceSelected( QString macAddress );

private slots:
    void onSelected( bool checked );
};

#endif // PairedDeviceSelector_H
