#include "formconfiguracao.h"
//***********************************************************
FormConfiguracao::FormConfiguracao(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
 QGridLayout *layout=NULL;

 setupUi(this);

 conf_geral=new ConfGeralWidget(this);
 conf_aparencia=new ConfAparenciaWidget(this);
 conf_conexoes=new ConfConexoesWidget(this);

 layout=new QGridLayout;
 layout->setContentsMargins(2,2,2,2);
 layout->addWidget(conf_geral);
 geral_frm->setLayout(layout);

 layout=new QGridLayout;
 layout->setContentsMargins(2,2,2,2);
 layout->addWidget(conf_aparencia);
 aparencia_frm->setLayout(layout);

 layout=new QGridLayout;
 layout->setContentsMargins(2,2,2,2);
 layout->addWidget(conf_conexoes);
 conexoes_frm->setLayout(layout);

 connect(lista_ico_lst, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));
 connect(cancelar_btn, SIGNAL(clicked(void)), this, SLOT(close(void)));

 conf_geral->carregarConfiguracao();
}
//-----------------------------------------------------------
ConfBaseWidget *FormConfiguracao::obterWidgetConfiguracao(unsigned idx)
{
 if(idx >= static_cast<unsigned>(stackedWidget->count()))
  return(NULL);
 else
 {
  switch(idx)
  {
   case 0: return(dynamic_cast<ConfBaseWidget *>(conf_geral)); break;
   case 1: return(dynamic_cast<ConfBaseWidget *>(conf_aparencia)); break;
   default:
   case 2: return(dynamic_cast<ConfBaseWidget *>(conf_conexoes)); break;
  }
 }
}
//***********************************************************
