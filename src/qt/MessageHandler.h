#ifndef MessageHandler_H
#define MessageHandler_H

#include <QMainWindow>

class QTextEdit;

class MessageHandler
{
public:
    static MessageHandler& GetInstance();
    ~MessageHandler();

    void set_TextEdit( QTextEdit* newTextEdit );

private:
    MessageHandler();
    MessageHandler( MessageHandler& src ) = delete;
    MessageHandler& operator=( MessageHandler& src ) = delete;

    static QtMessageHandler originalHandler_;
    static QTextEdit* textEdit_;

    static void messageHandler( const QtMsgType type,
                                const QMessageLogContext &context,
                                const QString &message );

    static void on_Debug( const QString& message, const Qt::GlobalColor colour = Qt::black );
    static void on_Fatal( const QString& message );
};

#endif // MessageHandler_H
