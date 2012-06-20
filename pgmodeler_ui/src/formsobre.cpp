#include "formsobre.h"
//**********************************************************
FormSobre::FormSobre(QWidget *parent) : QWidget(parent)
{
 setupUi(this);
 pgmodeler_ver_lbl->setText(AtributosGlobais::VERSAO_PGMODELER);
}
//**********************************************************
