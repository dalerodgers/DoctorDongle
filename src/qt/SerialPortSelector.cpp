#include "SerialPortSelector.h"

#include <QObject>
#include <QSerialPortInfo>

///////////////////////////////////////////////////////////////////////////////

SerialPortSelector::SerialPortSelector( QMenu& menu ) :
    menu_( menu ),
    currentPortName_( "" )
{
    clearActions();

    connect( &menu_, SIGNAL( aboutToShow() ), this, SLOT( onAboutToShow() ) );
}

///////////////////////////////////////////////////////////////////////////////

SerialPortSelector::~SerialPortSelector()
{
    clearActions();
    disconnect( &menu_, SIGNAL( aboutToShow() ), this, SLOT( onAboutToShow() ) );
}

///////////////////////////////////////////////////////////////////////////////

void SerialPortSelector::clearActions()
{
    for( QAction* action : menu_.actions() )
    {
        if( nullptr != action )
        {
            menu_.removeAction( action );
            disconnect( action, SIGNAL( triggered(bool) ), this, SLOT( onSelected(bool) ) );

            delete action;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void SerialPortSelector::onAboutToShow()
{
    // clear previous actions from menu .......................................
    clearActions();

    // ........................................................................
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &portInfo : serialPortInfos)
    {
        const QString portName = portInfo.portName();

        QAction* p = new QAction( portName );
        connect( p, SIGNAL( triggered(bool) ), this, SLOT( onSelected(bool) ) );

        if( portInfo.isBusy() || portInfo.isNull() )
        {
            p->setEnabled( false );
        }

        if( portName == currentPortName_ )
        {
            QFont f = p->font();
            f.setBold( true );

            p->setFont( f );
        }

        menu_.addAction( p );
    }
}

///////////////////////////////////////////////////////////////////////////////

void SerialPortSelector::onSelected( bool checked )
{
    Q_UNUSED( checked );

    QAction* action = dynamic_cast<QAction*>( QObject::sender() );

    if( action )
    {
        const QString newName = action->text();

        if( newName != currentPortName_ )
        {
            currentPortName_ = newName;
            emit portNameChanged( currentPortName_ );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
