#include "serialportwriter.h"

#include <QCoreApplication>
#include <QFile>
#include <QSerialPort>
#include <QStringList>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication coreApplication(argc, argv);
    const int argumentCount = QCoreApplication::arguments().size();
    const QStringList argumentList = QCoreApplication::arguments();
    QTextStream standardOutput(stdout);

    if (argumentCount == 1) {
        standardOutput << QObject::tr("Usage: %1 <serialportname> [baudrate]")
                          .arg(argumentList.first()) << endl;
        return 1;
    }

    QSerialPort serialPort;
    const QString serialPortName = argumentList.at(1);
    serialPort.setPortName(serialPortName);

    const int serialPortBaudRate = (argumentCount > 2)
            ? argumentList.at(2).toInt() : QSerialPort::Baud9600;
    serialPort.setBaudRate(serialPortBaudRate);

    serialPort.open(QIODevice::WriteOnly);

    QFile dataFile;
    if (!dataFile.open(stdin, QIODevice::ReadOnly)) {
        standardOutput << QObject::tr("Failed to open stdin for reading") << endl;
        return 1;
    }
    const QByteArray writeData(dataFile.readAll());
    dataFile.close();
    if (writeData.isEmpty()) {
        standardOutput << QObject::tr("Either no data was currently available on "
                                      "the standard input for reading, "
                                      "or an error occurred for port %1, error: %2")
                          .arg(serialPortName).arg(serialPort.errorString()) << endl;
        return 1;
    }
    SerialPortWriter serialPortWriter(&serialPort);
    serialPortWriter.write(writeData);
    return coreApplication.exec();
}
