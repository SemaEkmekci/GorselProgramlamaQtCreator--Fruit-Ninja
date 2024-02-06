//Ad-Soyad: Sema Nur EKMEKCİ
//Numara: 21100011050

#ifndef KARPUZ_H
#define KARPUZ_H

#include <QPushButton>
#include <QWidget>

class karpuz : public QPushButton
{
    Q_OBJECT
public:
    karpuz(QWidget *parrent = 0);
    bool tiklandimi;
public slots:
    void tikla();
};

#endif // KARPUZ_H
