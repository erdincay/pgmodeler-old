#include "confgeralwidget.h"
//***********************************************************
ConfGeralWidget::ConfGeralWidget(QWidget * parent) : QWidget(parent)
{
 int cod_tipo_papel[]={5, 6, 7, 8, 0, 9, 10, 11, 12, 13,
                       14, 15, 16, 17, 18, 19, 1, 20, 21, 22,
                       23, 24, 25, 26, 4, 27, 28, 3, 2, 29, 30 };

 Ui_ConfGeralWidget::setupUi(this);

 for(int i=0; i <= 30; i++)
  papel_cmb->setItemData(i, QVariant(cod_tipo_papel[i]));

 connect(unidade_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(converterUnidadeMargem(void)));
 connect(salvar_mod_chk, SIGNAL(toggled(bool)), salvar_mod_spb, SLOT(setEnabled(bool)));
}
//-----------------------------------------------------------
void ConfGeralWidget::carregarConfiguracao(void)
{
 QStringList margem;
 vector<QString> atribs_chave;
 unsigned interv;

 atribs_chave.push_back(AtributosParsers::ID);
 ConfBaseWidget::carregarConfiguracao(AtributosGlobais::CONF_GERAL, atribs_chave);

 tam_grade_spb->setValue((params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::TAM_GRADE]).toUInt());
 tam_lista_spb->setValue((params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::TAM_LISTA_OP]).toUInt());

 interv=(params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::INTERVALO_SALVAR_AUTO]).toUInt();
 salvar_mod_chk->setChecked(interv > 0);
 salvar_mod_spb->setValue(interv);
 salvar_mod_spb->setEnabled(salvar_mod_chk->isChecked());

 salvar_wgts_chk->setChecked(params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::SALVAR_WIDGETS]==AtributosParsers::VERDADEIRO);
 salvar_sessao_chk->setChecked(params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::SALVAR_SESSAO]==AtributosParsers::VERDADEIRO);

 papel_cmb->setCurrentIndex((params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::TIPO_PAPEL_IMP]).toUInt());
 retrato_rb->setChecked(params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::ORIENTACAO_PAPEL]==AtributosParsers::RETRATO);

 margem=params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::MARGEM_PAPEL].split(",");

 marg_esq->setValue((margem.count() >= 1 ? margem[0].toFloat() : 10));
 marg_topo->setValue((margem.count()>= 2 ? margem[1].toFloat() : 10));
 marg_dir->setValue((margem.count() >= 3 ? margem[2].toFloat() : 10));
 marg_base->setValue((margem.count() >= 4 ? margem[3].toFloat() : 10));

 this->aplicarConfiguracao();
}
//-----------------------------------------------------------
void ConfGeralWidget::salvarConfiguracao(void)
{
 try
 {
  params_config[AtributosGlobais::CONF_GERAL][AtributosParsers::TAM_GRADE]=QString("%1").arg(tam_grade_spb->value());
  params_config[AtributosGlobais::CONF_GERAL][AtributosParsers::TAM_LISTA_OP]=QString("%1").arg(tam_lista_spb->value());
  params_config[AtributosGlobais::CONF_GERAL][AtributosParsers::INTERVALO_SALVAR_AUTO]=QString("%1").arg(salvar_mod_chk->isChecked() ? salvar_mod_spb->value() : 0);
  params_config[AtributosGlobais::CONF_GERAL][AtributosParsers::TIPO_PAPEL_IMP]=QString("%1").arg(papel_cmb->currentIndex());
  params_config[AtributosGlobais::CONF_GERAL][AtributosParsers::ORIENTACAO_PAPEL]=(retrato_rb->isChecked() ? AtributosParsers::RETRATO : AtributosParsers::PAISAGEM);

  unidade_cmb->setCurrentIndex(0);
  params_config[AtributosGlobais::CONF_GERAL][AtributosParsers::MARGEM_PAPEL]=QString("%1,%2,%3,%4").arg(marg_esq->value())
                                                                             .arg(marg_topo->value())
                                                                             .arg(marg_dir->value())
                                                                             .arg(marg_base->value());

  params_config[AtributosGlobais::CONF_GERAL][AtributosParsers::SALVAR_SESSAO]=(salvar_sessao_chk->isChecked() ? "1" : "");
  params_config[AtributosGlobais::CONF_GERAL][AtributosParsers::SALVAR_WIDGETS]=(salvar_wgts_chk->isChecked() ? "1" : "");

  ConfBaseWidget::salvarConfiguracao(AtributosGlobais::CONF_GERAL);

  this->aplicarConfiguracao();
 }
 catch(Excecao &e)
 {
  throw Excecao(e.obterMensagemErro(),e.obterTipoErro(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
 }
}
//-----------------------------------------------------------
void ConfGeralWidget::aplicarConfiguracao(void)
{
 CenaObjetos::definirGrade(tam_grade_spb->value());
 CenaObjetos::definirConfiguracaoPagina(static_cast<QPrinter::PaperSize>(papel_cmb->itemData(papel_cmb->currentIndex()).toInt()),
                                        (retrato_rb->isChecked() ? QPrinter::Portrait : QPrinter::Landscape),
                                        QRectF(marg_esq->value(), marg_topo->value(),
                                               marg_dir->value(), marg_base->value()));
 ListaOperacoes::definirTamanhoMaximo(tam_lista_spb->value());
}
//-----------------------------------------------------------
void ConfGeralWidget::restaurarPadroes(void)
{
 unidade_cmb->setCurrentIndex(0);
 marg_esq->setValue(10);
 marg_dir->setValue(10);
 marg_topo->setValue(10);
 marg_base->setValue(10);
 papel_cmb->setCurrentIndex(4);
 paisagem_rb->setChecked(true);

 salvar_sessao_chk->setChecked(true);
 salvar_wgts_chk->setChecked(true);
 salvar_mod_chk->setChecked(true);
 salvar_mod_spb->setValue(10);

 tam_lista_spb->setValue(500);
 tam_grade_spb->setValue(20);
}
//-----------------------------------------------------------
void ConfGeralWidget::converterUnidadeMargem(void)
{
 static int unidade_ant=0;
 float fator_conv[]={1.0f, 2.83f, 0.04f, 0.1f},
       esq, dir, topo, base;

 esq=marg_esq->value() / fator_conv[unidade_ant];
 dir=marg_dir->value() / fator_conv[unidade_ant];
 base=marg_base->value() / fator_conv[unidade_ant];
 topo=marg_topo->value() / fator_conv[unidade_ant];

 marg_esq->setValue(esq * fator_conv[unidade_cmb->currentIndex()]);
 marg_dir->setValue(dir * fator_conv[unidade_cmb->currentIndex()]);
 marg_base->setValue(base * fator_conv[unidade_cmb->currentIndex()]);
 marg_topo->setValue(topo * fator_conv[unidade_cmb->currentIndex()]);

 unidade_ant=unidade_cmb->currentIndex();
}
//***********************************************************
