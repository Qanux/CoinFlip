#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <mybutton.h>
#include <QDebug>
#include <chooselevelscene.h>
#include <QTime>
#include <QApplication>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置窗口标题
    this->setWindowTitle("CoinFlip");
    //设置窗口固定大小
    this->setFixedSize(420, 680);
    //设置窗口图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //退出
    connect(ui->actionQuit, &QAction::triggered, [=](){
        this->close();
    });

    //开始按钮的音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);
    startSound->play();

    //创建Start按钮
    //加载开始按钮图片
    myButton* startBtn = new myButton(":/res/MenuSceneStartButton.png");
    ChooseLevelScene* choice = new ChooseLevelScene();

    //监听选择关卡场景的返回按钮的信号
    connect(choice, &ChooseLevelScene::chooseBackScene,this,[=](){

        sleep(500);
        // 设置固定窗口
        this->setGeometry(choice->geometry());
        choice->close();
        //choice->hide();
        this->show();
    });
    //对开始按钮进行设置
    startBtn->setParent(this);

    startBtn->move(this->width()*0.5 - startBtn->width()*0.5, this->height()*0.7);

    connect(startBtn, &QPushButton::clicked, [=](){
        //开启开始按钮的音乐
        startSound->play();
        //设置按钮点击后上下跳动
        startBtn->downBounce();
        startBtn->upBounce();

        sleep(500);

        // 设置窗口固定
        choice->setGeometry(this->geometry());

        this->hide();
        choice->show();

    });
}
//用于延迟事件的进行
void MainScene::sleep(int ms){
    QTime reachTime = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
    }
}

void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    //设置存放背景的设备
    QPixmap pix;
    pix.load(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

MainScene::~MainScene()
{
    delete ui;
}
