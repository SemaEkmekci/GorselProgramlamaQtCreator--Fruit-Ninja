//Ad-Soyad: Sema Nur EKMEKCİ
//Numara: 21100011050

#include "dialog.h"
#include "ui_dialog.h"
#include <QTimer>
#include <QMessageBox>
#include <QFile>
#include "karpuz.h"


int durum =0;   //süre bittiğinde karpuzların kaymasını durdurmak için
int max;  //maximum skoru bulmak için

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QTimer *sure = new QTimer(this);
    QTimer *tiklaKontrol = new QTimer(this);
    QTimer *karpuzKay = new QTimer(this);

    connect(karpuzKay, SIGNAL(timeout()),this,SLOT(yerDegistir()));
    connect(sure, SIGNAL(timeout()),this,SLOT(sureDegistir()));

    connect(sure, SIGNAL(timeout()),this,SLOT(ekranaRastgeleKarpuzKoy()));
    connect(tiklaKontrol, SIGNAL(timeout()),this,SLOT(karpuzKes()));
    tiklaKontrol->start(50);
    sure->start(1000);
    karpuzKay->start(200);


    dosyaOku();  //dosya okuma işlemi bir defa yapılacak. konum bilgileri alınacak ve daha sonra connect fonksiyon ile belirli araıklarla listeden rastgele konum seçilerek karpuzlar ekrana gelecek.
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::sureDegistir()
{   // Ekranda yazan süre kısmını her 1 saniyede bir değiştirecek ve süre bittiğinde ekrana message box gelecek.
    static int sayac = 30;
    if(sayac == -1)
    {
        durum=1;     //kayan karpuzları durdurdum.
        QString mesaj = "";
        bool durum = skorBilgileri();
        if(durum==true)
            mesaj = "Oyun Bitti! Tebrikler Maksimum Skor Sizde!\n";
        else
            mesaj = "Oyun Bitti! Maksimum Skoru Geçemediniz\n";
        QMessageBox::information(this,"Bilgi!",mesaj +"Kesilen Karpuz Sayısı: "+QString::number(kesilenKarpuzlar.size())+"\nKaçırılan Karpuz Sayısı: "+QString::number(kacirilanKarpuzlar.size())+"\nMaksimum Skor: "+QString::number(max),"Ok");
        close();
    }
    else
    {
    ui->label_5->setText(QString::number(sayac));
    sayac--;
    }
}

void Dialog::karpuzKes()
{
    int sayi=ekrandakiKrpzlar.size();

    for(int i=0; i<sayi; ++i)
    {
    if(ekrandakiKrpzlar[i]->tiklandimi)
    {
        auto varmi = std::find(kesilenKarpuzlar.begin(), kesilenKarpuzlar.end(), ekrandakiKrpzlar[i]);
        if(varmi == kesilenKarpuzlar.end()){
            ekrandakiKrpzlar[i]->setStyleSheet("border-image:url(:/new/image/2.png);");
            kesilenKarpuzlar.push_back(ekrandakiKrpzlar[i]);
            ui->label_6->setText(QString::number(kesilenKarpuzlar.size()));
            QTimer* karpuzYokEt = new QTimer(); //karpuzu yok etmek için timer oluşturdum.
            connect(karpuzYokEt, &QTimer::timeout, ekrandakiKrpzlar[i], &QLabel::hide);  //3.parametredeki label ı 1sn sonra ekrandan silecek.
            karpuzYokEt->setSingleShot(true); //timer 1 defa çalışacak.
            karpuzYokEt->start(1000);
        }

    }
    }
}

void Dialog::dosyaOku()
{
    int x;
    int y;
    QList<int> konumlar;
    QFile file("D:\\GorselProgramlama\\21100011050karpuz\\21100011050\\konumlar.txt"); //okunacak dosya
    if(!file.open(QIODevice::ReadOnly)) { //dosya okunamıyorsa hata mesajı veriyor.
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    while(!in.atEnd()) { //dosya bitene kadar okuma işlemi gerçekleştir.
    QString line = in.readLine(); //satır satır okuma yap
    QStringList konum = line.split(" "); //" " karakterinden ayır.
    x = konum[0].toInt();
    y = konum[1].toInt();
    konumlar.push_back(x);
    konumlar.push_back(y);
    karpuzList.push_back(konumlar);
    konumlar.clear();
    }
    file.close();
}

void Dialog::ekranaRastgeleKarpuzKoy()
{
    int randomNumber = std::rand() % (karpuzList.size());
    int x = karpuzList[randomNumber][0];
    int y = karpuzList[randomNumber][1];
    karpuz *krpz = new karpuz(this);
    krpz->setGeometry(x,y,80,80);
    krpz->setStyleSheet("border-image:url(:/new/image/1.png);");
    ekrandakiKrpzlar.push_back(krpz);
    krpz->show();
}

bool Dialog::skorBilgileri()
{
    skorlar.clear();
    QFile file("D:\\GorselProgramlama\\21100011050karpuz\\21100011050\\skorlar.txt"); //okunacak dosya
    if(!file.open(QIODevice::ReadOnly)) { //dosya okunamıyorsa hata mesajı veriyor.
    QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream in(&file);
    while(!in.atEnd()) { //dosya bitene kadar okuma işlemi gerçekleştir.
    QString line = in.readLine(); //satır satır okuma yap
    skorlar.push_back(line.toInt());

}
    file.close();
    int sonSkor = kesilenKarpuzlar.size();
    max = 0;
for(int i:skorlar)
{
    if(max < i)
    {
        max = i;
    }

}
skorlar.push_back(sonSkor);

QFile writeFile("D:\\GorselProgramlama\\21100011050karpuz\\21100011050\\skorlar.txt"); //yazılacak dosya


if (writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QTextStream out(&writeFile);
    for(int i:skorlar)
    {
        out << QString::number(i)<< Qt::endl;
    }
    writeFile.close();
    qDebug() << "Yeni dosyaya yazma işlemi tamamlandı.";
} else {
    qDebug() << "Dosya açılırken bir hata oluştu.";
}
if(sonSkor>max) return true; else return false;
}

void Dialog::yerDegistir()
{
for(karpuz *i: ekrandakiKrpzlar)
{
    if(durum==0){
    i->setGeometry(i->x(),i->y()+10,
                                 i->width(),
                                 i->height());
    }
    if(i->y()>800)
    {
        if(!i->tiklandimi)
        {
            auto varmi = std::find(kacirilanKarpuzlar.begin(), kacirilanKarpuzlar.end(),i);
            if(varmi == kacirilanKarpuzlar.end()){
                kacirilanKarpuzlar.push_back(i);
                ui->label_7->setText(QString::number(kacirilanKarpuzlar.size()));
            }
            }


    }
}
}


