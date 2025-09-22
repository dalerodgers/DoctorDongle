#include "PairedDeviceSelector.h"
#include <QString>

///////////////////////////////////////////////////////////////////////////////

PairedDeviceSelector::PairedDeviceSelector( QMenu& menu ) :
    menu_( menu )
{
    // do nothing
}

///////////////////////////////////////////////////////////////////////////////

PairedDeviceSelector::~PairedDeviceSelector()
{
    clearOldActions();
}

///////////////////////////////////////////////////////////////////////////////

void PairedDeviceSelector::onUpdatedList( const std::vector<Device>& devices )
{
    clearOldActions();

    auto iter = devices.begin();

    while( iter != devices.end() )
    {
        Action* p = new Action( menu_, *iter );
        actions_.push_back( p );

        connect( p, SIGNAL( triggered(bool) ), this, SLOT( onSelected(bool) ) );
        ++iter;
    }
}

///////////////////////////////////////////////////////////////////////////////

void PairedDeviceSelector::clearOldActions()
{
    auto iter = actions_.begin();

    while( iter != actions_.end() )
    {
        menu_.removeAction( *iter );
        delete *iter;
        ++iter;
    }

    actions_.clear();
}

///////////////////////////////////////////////////////////////////////////////

void PairedDeviceSelector::onSelected( bool checked )
{
    Q_UNUSED( checked );
    Action* action = dynamic_cast<Action*>( QObject::sender() );

    if( nullptr != action )
    {
        emit deviceSelected( action->macAddress().c_str() );
    }
}

///////////////////////////////////////////////////////////////////////////////

PairedDeviceSelector::Action::Action( QMenu& menu, const Device& device ) :
    QAction(),
    device_( device )
{
    this->setText( ( device_.name() + " [" + device_.macAddress() + "]" ).c_str() );
    menu.addAction( this );
}

///////////////////////////////////////////////////////////////////////////////

PairedDeviceSelector::Action::~Action()
{
}

///////////////////////////////////////////////////////////////////////////////
