#include "chooselevelscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QPixmap>
#include <mybutton.h>
#include <QDebug>
#include <QLabel>
#include <playscene.h>
#include <QTime>
#include <QApplication>
#include <QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) :
    QMainWindow(parent)
{
    //设置新窗口
    this->setFixedSize(420, 680);
    this->setWindowTitle("Level");
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar* menubar =  menuBar();
    setMenuBar(menubar);

    //创建菜单栏开始
    QMenu* startMenu = menubar->addMenu("Start");

    //创建菜单项退出
    QAction* quitAction = startMenu->addAction("Exit");

    //点击退出
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //选择关卡按钮音效
    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    QSound *backSound = new QSound(":/res/TapButtonSound.wav",this);

    //Back按钮
    myButton* backBtn = new myButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
//    backBtn->resize(80,80);
//    backBtn->move(320,620);
    backBtn->move(this->width()-backBtn->width()-20, this->height()-backBtn->height()-20);
    connect(backBtn, &QPushButton::clicked, [=](){
        //qDebug() << "点击了返回按钮";
        backSound->play();
        emit this->chooseBackScene(); // 发出信号，返回到主界面
    });

    //20关卡按钮
    for(int i = 0; i < 20; i++){
        // 关卡按钮
        myButton* selectBtn = new myButton(":/res/LevelIcon.png");
        selectBtn->setParent(this);
        // 参数1：横坐标 参数2：纵坐标 70：按钮间隔 (70, 180)：起始移动坐标
        selectBtn->move(70+i%4*70, 180+i/4*70);

        connect(selectBtn, &QPushButton::clicked,[=](){
            QString str = QString("No. %1 was selected.").arg(i+1);
            qDebug() << str;
            //选择音乐响起
            chooseSound->play();
            this->hide();
            this->playScene = new PlayScene(i+1);

            //设置固定窗口
            playScene->setGeometry(this->geometry());

            //游戏场景
            playScene->show();

            //监听游戏场景的Back按钮
            connect(playScene, &PlayScene::selectLevelScene, [=](){
                this->sleep(500);

                // 设置固定窗口
                this->setGeometry(playScene->geometry());
                playScene->hide();
                this->show();
                delete playScene;
                playScene = NULL;
            });
        });

        //左下角显示选择的关卡数
        QLabel* label = new QLabel;
        label->setParent(selectBtn);
        //label->setParent(this);
        label->setFixedSize(selectBtn->width(), selectBtn->height());
        label->setText(QString::number(i+1));
        //label->move(70+i%4*80, 180+i/4*80);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        label->setAttribute(Qt::WA_TransparentForMouseEvents); // 设置label的穿透功能，使鼠标点击可以点击到下方的按钮
    }
}

void ChooseLevelScene::sleep(int ms){
    QTime  reachTime = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *){
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");

    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width()*0.5-pix.width()*0.6, 40, pix.width()*1.2, pix.height()*1.2, pix);
}
