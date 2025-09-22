#ifndef SCAN_H
#define SCAN_H

#include "Device.h"
#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class scan;
}

class Scan : public QDialog
{
    Q_OBJECT

public:
    explicit Scan(QWidget *parent = nullptr);
    ~Scan();

    void on_ScanList( const std::vector<Device>& deviceList );

private:
    class Item : public QListWidgetItem
    {
    public:
        Item( const Device& device );

        inline const std::string& name() const
        {
            return device_.name();
        }

        inline const std::string& macAddress() const
        {
            return device_.macAddress();
        }

    private:
        const Device& device_;
    };

    Ui::scan *ui;
    std::list<Item*> itemList_;

private slots:
    void onItemClicked( QListWidgetItem* item );

signals:
    void deviceSelected( QString macAddress );
};

#endif // SCAN_H
