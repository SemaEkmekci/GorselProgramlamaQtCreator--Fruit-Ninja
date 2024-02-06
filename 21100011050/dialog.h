//Ad-Soyad: Sema Nur EKMEKCİ
//Numara: 21100011050

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include "karpuz.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void sureDegistir();
    void karpuzKes();
    void dosyaOku();
    void ekranaRastgeleKarpuzKoy();
    bool skorBilgileri();
    void yerDegistir();
private:
    Ui::Dialog *ui;
    QTimer *sure;
    QTimer *tiklaKontrol;
    QTimer *karpuzKay;
    QList<QList <int>> karpuzList;
    QList<karpuz*> ekrandakiKrpzlar;
    QList<karpuz*> kesilenKarpuzlar;
    QList<karpuz*> kacirilanKarpuzlar;
    QList<int> skorlar;

};
#endif // DIALOG_H

