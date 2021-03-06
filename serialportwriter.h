#ifndef SERIALPORTWRITER_H
#define SERIALPORTWRITER_H

#include <QByteArray>
#include <QObject>
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>

class SerialPortWriter : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortWriter(QSerialPort *serialPort, QObject *parent = nullptr);
    void write(const QByteArray &writeData);

private slots:
    void handleBytesWritten(qint64 bytes);
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *m_serialPort = nullptr;
    QByteArray m_writeData;
    QTextStream m_standardOutput;
    qint64 m_bytesWritten = 0;
    QTimer m_timer;
};

#endif // SERIALPORTWRITER_H
