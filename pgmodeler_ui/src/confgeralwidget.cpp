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
}
//-----------------------------------------------------------
void ConfGeralWidget::carregarConfiguracao(void)
{
 QStringList margem;
 vector<QString> atribs_chave;
 unsigned interv;

 atribs_chave.push_back(AtributosParsers::ID);
 ConfBaseWidget::carregarConfiguracao(AtributosGlobais::CONF_GERAL, atribs_chave);

 tam_lista_spb->setValue((params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::TAM_LISTA_OP]).toUInt());

 interv=(params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::INTERVALO_SALVAR_AUTO]).toUInt();
 salvar_mod_chk->setChecked(interv > 0);
 salvar_mod_spb->setValue(interv);

 salvar_wgts_chk->setChecked(params_config[AtributosParsers::CONFIGURACAO].count(AtributosParsers::SALVAR_WIDGETS));
 salvar_sessao_chk->setChecked(params_config[AtributosParsers::CONFIGURACAO].count(AtributosParsers::SALVAR_SESSAO));

 papel_cmb->setCurrentIndex((params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::TIPO_PAPEL_IMP]).toUInt());
 retrato_rb->setChecked(params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::ORIENTACAO_PAPEL]==AtributosParsers::RETRATO);

 margem=params_config[AtributosParsers::CONFIGURACAO][AtributosParsers::MARGEM_PAPEL].split(",");

 marg_esq->setValue((margem.count() >= 1 ? margem[0].toFloat() : 10));
 marg_topo->setValue((margem.count()>= 2 ? margem[1].toFloat() : 10));
 marg_dir->setValue((margem.count() >= 3 ? margem[2].toFloat() : 10));
 marg_base->setValue((margem.count() >= 4 ? margem[3].toFloat() : 10));
}
//***********************************************************
