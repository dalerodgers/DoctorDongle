#include "MessageHandler.h"

#include <iostream>
#include <QCoreApplication>
#include <QMessageBox>
#include <QTextEdit>

///////////////////////////////////////////////////////////////////////////////

QtMessageHandler MessageHandler::originalHandler_ = nullptr;
QTextEdit* MessageHandler::textEdit_ = nullptr;

///////////////////////////////////////////////////////////////////////////////

MessageHandler::MessageHandler()
{
    originalHandler_ = nullptr;
    textEdit_ = nullptr;
}

///////////////////////////////////////////////////////////////////////////////

MessageHandler::~MessageHandler()
{
    set_TextEdit( nullptr );
}

///////////////////////////////////////////////////////////////////////////////

MessageHandler& MessageHandler::GetInstance()
{
    static MessageHandler instance;
    return instance;
}

///////////////////////////////////////////////////////////////////////////////

void MessageHandler::set_TextEdit( QTextEdit* newTextEdit )
{
    if( newTextEdit != nullptr )
    {
        if( nullptr == originalHandler_ )
        {
            // not currently set, save old handler, switch and install
            originalHandler_ = qInstallMessageHandler( messageHandler );
        }
        else
        {
            static_cast<void>( qInstallMessageHandler( messageHandler ) );
        }
    }
    else
    {
        if( nullptr != originalHandler_ )
        {
            static_cast<void>( qInstallMessageHandler( originalHandler_ ) );
            originalHandler_ = nullptr;
        }
    }

    textEdit_ = newTextEdit;
}

///////////////////////////////////////////////////////////////////////////////

void MessageHandler::messageHandler( const QtMsgType type, const QMessageLogContext &context, const QString &message )
{
    Q_UNUSED( context );

    if( textEdit_ != nullptr )
    {
        switch ( type )
        {
            case QtDebugMsg:
            case QtInfoMsg:
                on_Debug( message, Qt::black );
                break;

            case QtWarningMsg:
            case QtCriticalMsg:
                on_Debug( message, Qt::red );
                break;

            case QtFatalMsg:
                on_Fatal( message );
                break;
        }
    }
    else
    {
        std::cerr << message.toStdString();
        std::cerr << std::flush;
    }
}

///////////////////////////////////////////////////////////////////////////////

void MessageHandler::on_Debug( const QString& message, const Qt::GlobalColor colour )
{
    // Move cursor to end of document
    QTextCursor cursor = textEdit_->textCursor();
    cursor.movePosition( QTextCursor::End );

    textEdit_->setTextCursor( cursor );
    textEdit_->setTextColor( colour );
    textEdit_->insertPlainText( message + '\r' );
    textEdit_->ensureCursorVisible();

    QCoreApplication::processEvents();  // flush the text
}

///////////////////////////////////////////////////////////////////////////////

void MessageHandler::on_Fatal( const QString& message )
{
    QMessageBox *msgBox = new QMessageBox();
    msgBox->setAttribute( Qt::WA_DeleteOnClose );
    msgBox->setWindowTitle( "Error!" );
    msgBox->setText( message.toStdString().c_str() );
    msgBox->exec();

    ::exit( -1 );
}

///////////////////////////////////////////////////////////////////////////////
