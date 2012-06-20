#include "confgeralwidget.h"
//***********************************************************
ConfGeralWidget::ConfGeralWidget(QWidget * parent) : QWidget(parent)
{
 Ui_ConfGeralWidget::setupUi(this);
}
//-----------------------------------------------------------
void ConfGeralWidget::carregarConfiguracao(void)
{
 vector<QString> atribs_chave;

 atribs_chave.push_back(AtributosParsers::ID);
 ConfBaseWidget::carregarConfiguracao(AtributosGlobais::CONF_GERAL, atribs_chave);
}
//***********************************************************
