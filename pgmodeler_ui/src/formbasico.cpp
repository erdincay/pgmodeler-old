#include "formbasico.h"
//***********************************************************
FormBasico::FormBasico(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
 setupUi(this);
}
//----------------------------------------------------------
void FormBasico::definirBotoes(unsigned conf_botoes)
{
 if(conf_botoes==CaixaMensagem::BOTAO_OK_CANCELAR)
 {
  aplicar_ok_btn->setText(trUtf8("&Aplicar"));
  cancelar_btn->setVisible(true);
 }
 else
 {
  aplicar_ok_btn->setText(trUtf8("&Ok"));
  cancelar_btn->setVisible(false);
 }
}
//***********************************************************
