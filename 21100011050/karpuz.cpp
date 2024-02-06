//Ad-Soyad: Sema Nur EKMEKCİ
//Numara: 21100011050

#include "karpuz.h"

karpuz::karpuz(QWidget *parrent):QPushButton(parrent)
{
    tiklandimi=false;
    connect(this, SIGNAL(clicked()),this,SLOT(tikla()));
}

void karpuz::tikla()
{
    tiklandimi=!tiklandimi;
}
