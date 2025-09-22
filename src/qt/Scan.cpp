#include "Scan.h"
#include "ui_Scan.h"

///////////////////////////////////////////////////////////////////////////////

Scan::Scan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scan)
{
    this->setEnabled( true );
    ui->setupUi(this);

    ui->progressBar->setMaximum( 0 );
    ui->progressBar->setMinimum( 0 );
    ui->buttonBox->setEnabled( false );

    connect( ui->listWidget, SIGNAL( itemClicked(QListWidgetItem*) ), this, SLOT( onItemClicked(QListWidgetItem*) ) );
}

///////////////////////////////////////////////////////////////////////////////

Scan::~Scan()
{
    auto iter = itemList_.begin();

    while( iter != itemList_.end() )
    {
        delete( *iter );
        ++iter;
    }

    delete ui;
}

///////////////////////////////////////////////////////////////////////////////

void Scan::on_ScanList( const std::vector<Device>& deviceList )
{
    if( deviceList.size() > 0U )
    {
        auto iter = deviceList.begin();

        while( iter != deviceList.end() )
        {
            Item* i = new Item( *iter );
            itemList_.push_back( i );
            ui->listWidget->addItem( i );
            ++iter;
        }
    }
    else
    {
        done( 0 );
    }

    ui->progressBar->setVisible( false );
    ui->buttonBox->setEnabled( true );
}

///////////////////////////////////////////////////////////////////////////////

void Scan::onItemClicked( QListWidgetItem* item )
{
    Item* p = dynamic_cast<Item*>( item );

    if( nullptr != p )
    {
        emit deviceSelected( p->macAddress().c_str() );
    }
}

///////////////////////////////////////////////////////////////////////////////

Scan::Item::Item( const Device& device ) :
    QListWidgetItem( QString( device.name().c_str() ) + " [" + QString( device.macAddress().c_str() ) + ']' ),
    device_( device )
{
    // do nothing
}

///////////////////////////////////////////////////////////////////////////////
