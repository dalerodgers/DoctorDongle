#ifndef SerialPortSelector_H
#define SerialPortSelector_H

#include <QMenu>

class SerialPortSelector : public QObject
{
    Q_OBJECT

public:
    SerialPortSelector( QMenu& menu );
    ~SerialPortSelector();

    void overrideName( const QString& name );

signals:
    void portNameChanged( QString newName );

private:
    QMenu& menu_;
    QString currentPortName_;

    void clearActions();

private slots:
    void onSelected( bool checked = false );
    void onAboutToShow();
};

#endif // SerialPortSelector_H
