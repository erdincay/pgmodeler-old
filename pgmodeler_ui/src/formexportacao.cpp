#include "formexportacao.h"
#include "progressotarefa.h"
#include "formconfiguracao.h"

extern ProgressoTarefa *prog_tarefa;
extern FormConfiguracao *fconfiguracao;
//***********************************************************
FormExportacao::FormExportacao(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
 vector<QString> versoes;

 modelo=NULL;

 setupUi(this);
 connect(exportacao_arq_rb, SIGNAL(toggled(bool)), this, SLOT(habilitarTipoExportacao(void)));
 connect(exportacao_sgbd_rb, SIGNAL(toggled(bool)), this, SLOT(habilitarTipoExportacao(void)));
 connect(pgsqlvers_chk, SIGNAL(toggled(bool)), pgsqlvers1_cmb, SLOT(setEnabled(bool)));
 connect(cancelar_btn, SIGNAL(clicked(bool)), this, SLOT(close(void)));
 connect(sel_arquivo_tb, SIGNAL(clicked(void)), this, SLOT(selecionarArquivoDestino(void)));

 //Obtém as versões disponíveis de esquemas SQL
 ParserEsquema::obterVersoesPgSQL(versoes);

 //Preenche os comboboxes de versões
 pgsqlvers_cmb->addItems(QStringList(QList<QString>::fromVector(QVector<QString>::fromStdVector(versoes))));
 pgsqlvers1_cmb->addItems(QStringList(QList<QString>::fromVector(QVector<QString>::fromStdVector(versoes))));
}
//-----------------------------------------------------------
void FormExportacao::show(ModeloBD *modelo)
{
 if(modelo)
 {
  map<QString, ConexaoBD *> conexoes;
  map<QString, ConexaoBD *>::iterator itr;

  this->modelo=modelo;
  dynamic_cast<ConfConexoesWidget *>(fconfiguracao->obterWidgetConfiguracao(FormConfiguracao::WGT_CONF_CONEXOES))->obterConexoes(conexoes);

  conexoes_cmb->clear();

  itr=conexoes.begin();
  while(itr!=conexoes.end())
  {
   conexoes_cmb->addItem(itr->first + QString(" (%1)").arg((itr->second)->obterParamConexao(ConexaoBD::PARAM_FQDN_SERVIDOR)),
                         QVariant::fromValue<void *>(itr->second));
   itr++;
  }

  QDialog::show();
 }
}
//-----------------------------------------------------------
void FormExportacao::hideEvent(QHideEvent *)
{
 this->modelo=NULL;
 arquivo_edt->clear();
 exportacao_arq_rb->setChecked(true);
}
//-----------------------------------------------------------
void FormExportacao::exportarModelo(void)
{

}
//-----------------------------------------------------------
void FormExportacao::habilitarTipoExportacao(void)
{
 bool exp_arq=(sender()==exportacao_arq_rb);

 modelo_sql_lbl->setEnabled(exp_arq);
 arquivo_lbl->setEnabled(exp_arq);
 arquivo_edt->setEnabled(exp_arq);
 sel_arquivo_tb->setEnabled(exp_arq);
 pgsql_lbl->setEnabled(exp_arq);
 pgsqlvers_cmb->setEnabled(exp_arq);
 dica_lbl->setEnabled(exp_arq);

 modelo_sgbd->setEnabled(!exp_arq);
 conexoes_lbl->setEnabled(!exp_arq);
 conexoes_cmb->setEnabled(!exp_arq);
 pgsqlvers_chk->setEnabled(!exp_arq);
 pgsqlvers1_cmb->setEnabled(!exp_arq && pgsqlvers_chk->isChecked());
 dica1_lbl->setEnabled(!exp_arq);
 alerta_frm->setEnabled(!exp_arq);
}
//-----------------------------------------------------------
void FormExportacao::selecionarArquivoDestino(void)
{
 QFileDialog arquivo_dlg;

 arquivo_dlg.setWindowTitle(trUtf8("Exportar modelo como..."));
 arquivo_dlg.setFilter(trUtf8("Código SQL (*.sql);;Todos os Arquivos (*.*)"));
 arquivo_dlg.setFileMode(QFileDialog::AnyFile);
 arquivo_dlg.setAcceptMode(QFileDialog::AcceptSave);
 arquivo_dlg.setModal(true);

 if(arquivo_dlg.exec()==QFileDialog::Accepted)
  arquivo_edt->setText(arquivo_dlg.selectedFile());
}
//***********************************************************
