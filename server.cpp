#include "server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , serverPort(9555)
    , isRunning(false)
{
    serverIpEdit = new QLabel(this);
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
            serverIpEdit->setText(address.toString() + " :");
            serverIp = address.toString();
        }
    }

    serverPortEdit = new QLineEdit("9555", this);
    serverPortEdit->setValidator(new QIntValidator(serverPortEdit));

    startButton = new QPushButton("Start", this);
    connect(startButton, SIGNAL(clicked()),
            this, SLOT(processButton()));

    QHBoxLayout* addressLayout = new QHBoxLayout();
    addressLayout->addWidget(serverIpEdit);
    addressLayout->addWidget(serverPortEdit);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(addressLayout);
    mainLayout->addWidget(startButton);
}

Server::~Server()
{
}

void Server::startServer()
{
    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    //If format isn't supported find the nearest supported
    QAudioDeviceInfo inputAudioInfo(QAudioDeviceInfo::defaultInputDevice());
    if (!inputAudioInfo.isFormatSupported(format))
        format = inputAudioInfo.nearestFormat(format);

    serverSocket = new QUdpSocket(this);
    updateServerPort();
    serverSocket->connectToHost(QHostAddress(serverIp), serverPort);

    inputAudio = new QAudioInput(format, this);
    inputAudio->start(serverSocket);

    startButton->setText("Stop");
    isRunning = true;
}

void Server::stopServer()
{
    inputAudio->stop();

    delete inputAudio;
    delete serverSocket;

    startButton->setText("Start");
    isRunning = false;
}

void Server::updateServerPort()
{
    serverPort = serverPortEdit->text().toInt();
}

void Server::processButton()
{
    if (isRunning)
        stopServer();
    else
        startServer();
}
