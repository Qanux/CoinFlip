#include "mybutton.h"
#include <QDebug>
#include <QPropertyAnimation>

myButton::myButton(QString normalImgPath, QString pressedImgPath){
//myButton::myButton(QString normalImgPath, QString pressedImgPath=""){
    this->normalImgPath = normalImgPath;  //正常情况下的按钮图标
    this->pressedImgPath = pressedImgPath;//点击后的按钮图标

    QPixmap pix;
    bool res = pix.load(normalImgPath);
    if(!res){
        qDebug() << normalImgPath << "图片加载失败！";
        return;
    }

    //this->setFixedSize(pix.size());
    //设置按钮大小
    this->resize(pix.width(), pix.height());
    //设置按钮形状
    this->setStyleSheet("QPushButton{border:0px;}");
   // 加载按钮图片
    this->setIcon(pix);
    //设置按钮图标大小
    this->setIconSize(pix.size());
}

//鼠标按压事件
void myButton::mousePressEvent(QMouseEvent *e){
    if(this->pressedImgPath != ""){
//        this->setStyleSheet("background: rgb(255,150,128)");
        QPixmap pix;
        bool res = pix.load(this->pressedImgPath);
        if(!res){
            qDebug() << normalImgPath << "图片加载失败！";
            return;
        }

        //this->setFixedSize(pix.size());

        this->resize(pix.width(), pix.height());
        //设置按钮的形状
        this->setStyleSheet("QPushButton{border:0px;}");

        this->setIcon(pix);

        this->setIconSize(pix.size());
    }

    return QPushButton::mousePressEvent(e);
}
//鼠标离开事件
void myButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressedImgPath != ""){
//        this->setStyleSheet("background-color: rgb(0,0,255)");
        QPixmap pix;
        bool res = pix.load(this->normalImgPath);
        if(!res){
            qDebug() << normalImgPath << "图片加载失败！";
            return;
        }

        //this->setFixedSize(pix.size());

        this->resize(pix.width(), pix.height());

        this->setStyleSheet("QPushButton{border:0px;}");

        this->setIcon(pix);

        this->setIconSize(pix.size());
    }

    return QPushButton::mouseReleaseEvent(e);
}
//按钮向下跳
void myButton::downBounce(){
    //创建动态对象
    QPropertyAnimation* ani = new QPropertyAnimation(this, "geometry");

    //设置动画时间间隔
    ani->setDuration(200);

    //起始位置
    ani->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));

    //结束位置
//    ani->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    ani->setEndValue(QRect(this->x(), this->y()+10, this->width(), this->height()));

    //设置弹跳曲线
    ani->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    ani->start();
}
//按钮向上跳
void myButton::upBounce(){
    //创建动态对象
    QPropertyAnimation* ani = new QPropertyAnimation(this, "geometry");

    //设置动画时间间隔
    ani->setDuration(200);

    //起始位置
    ani->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));

    //结束位置
//    ani->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    ani->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    //设置弹跳曲线
    ani->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    ani->start();
}
