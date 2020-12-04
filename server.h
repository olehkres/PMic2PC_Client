#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets/QWidget>

#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QUdpSocket>

#include <QtMultimedia/QAudioInput>
#include <QtMultimedia/QAudioDeviceInfo>

#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QIntValidator>

#include <QtWidgets/QLayout>

class Server : public QWidget
{
    Q_OBJECT

private:
    QString serverIp;
    int serverPort;
    QUdpSocket* serverSocket;
    QAudioInput* inputAudio;

    QLabel* serverIpEdit;
    QLineEdit* serverPortEdit;
    QPushButton* startButton;

    bool isRunning;

    void startServer();
    void stopServer();
    void updateServerPort();

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void processButton();
};
#endif // SERVER_H
