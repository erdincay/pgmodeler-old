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
 connect(fechar_btn, SIGNAL(clicked(bool)), this, SLOT(close(void)));
 connect(sel_arquivo_tb, SIGNAL(clicked(void)), this, SLOT(selecionarArquivoDestino(void)));
 connect(exportar_btn, SIGNAL(clicked(void)), this, SLOT(exportarModelo(void)));

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

  /* Atualiza a lista de conexões ao exibir o formulário de exportação, obtendo-as
     do widget de configuração de conexões */
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

  //Esconde os widgets de progresso da exportação
  this->ocultarProgressoExportacao();
  QDialog::show();
 }
}
//-----------------------------------------------------------
void FormExportacao::hideEvent(QHideEvent *)
{
 this->modelo=NULL;
 arquivo_edt->clear();
 exportacao_arq_rb->setChecked(true);
 exportar_btn->setEnabled(false);
}
//-----------------------------------------------------------
void FormExportacao::exportarModelo(void)
{
 try
 {
  //Redimensiona a janela para exibição dos widgets de progresso
  this->resize(this->maximumSize());

  //Exibe os widgets de progresso
  ln2_frm->setVisible(true);
  rot_prog_lbl->setVisible(true);
  prog_pb->setVisible(true);

  //Inicialmente o ícone de sucesso/erro da exportação fica escondido
  ico_lbl->setVisible(false);

  //Configura o widget de progresso para capturar o progresso da geração do código
  prog_tarefa->setWindowTitle(trUtf8("Gerando código-fonte..."));
  connect(this->modelo, SIGNAL(s_objetoCarregado(int,QString,unsigned)),
          prog_tarefa, SLOT(executarProgesso(int,QString,unsigned)));

  rot_prog_lbl->setText(trUtf8("Iniciando exportação do modelo..."));
  rot_prog_lbl->repaint();

  //Caso seja exportação em arquivo
  if(exportacao_arq_rb->isChecked())
  {
   //Define a versão do postgresql a ser adotada
   ParserEsquema::definirVersaoPgSQL(pgsqlvers_cmb->currentText());

   rot_prog_lbl->setText(trUtf8("Salvando arquivo '%1'").arg(arquivo_edt->text()));

   //Salva o modelo em arquivo
   modelo->salvarModelo(arquivo_edt->text(), ParserEsquema::DEFINICAO_SQL);
   prog_pb->setValue(25);
  }
  //Caso seja exportação direto para o SGBD
  else
  {
   QString  versao;
   ConexaoBD *conexao=NULL;
   EspacoTabela *esp_tab=NULL;
   Papel *papel=NULL;
   unsigned i, qtd;

   //Obtém a conexão selecionada no combo
   conexao=reinterpret_cast<ConexaoBD *>(conexoes_cmb->itemData(conexoes_cmb->currentIndex()).value<void *>());
   //Tenta se conectar
   conexao->conectar();
   //Obtém a versão do servidor PostgreSQL. Essa versão é usada na geração de código a seguir
   versao=(conexao->obterVersaoSGBD()).mid(0,3);

   /* Caso o checkbox de versão esteja marcada então a versão do servidor é ignorada
      usando aquela escolhida no combo */
   if(pgsqlvers_chk->isChecked())
    ParserEsquema::definirVersaoPgSQL(pgsqlvers1_cmb->currentText());
   else
    ParserEsquema::definirVersaoPgSQL(versao);

   //Cria os papéis separadamente no servidor
   qtd=modelo->obterNumObjetos(OBJETO_PAPEL);
   for(i=0; i < qtd; i++)
   {
    papel=modelo->obterPapel(i);
    rot_prog_lbl->setText(trUtf8("Criando papel '%1'...").arg(QString::fromUtf8(papel->obterNome())));
    rot_prog_lbl->repaint();
    conexao->executarComandoDDL(papel->obterDefinicaoObjeto(ParserEsquema::DEFINICAO_SQL));
    prog_pb->setValue(10);
   }

   //Cria os espaços de tabela separadamente no servidor
   qtd=modelo->obterNumObjetos(OBJETO_ESPACO_TABELA);
   for(i=0; i < qtd; i++)
   {
    esp_tab=modelo->obterEspacoTabela(i);
    rot_prog_lbl->setText(trUtf8("Criando espaço de tabela '%1'...").arg(QString::fromUtf8(esp_tab->obterNome())));
    rot_prog_lbl->repaint();
    conexao->executarComandoDDL(esp_tab->obterDefinicaoObjeto(ParserEsquema::DEFINICAO_SQL));
    prog_pb->setValue(20);
   }

   //Cria o banco de dados no servidor
   rot_prog_lbl->setText(trUtf8("Criando banco de dados '%1'...").arg(QString::fromUtf8(modelo->obterNome())));
   rot_prog_lbl->repaint();
   conexao->executarComandoDDL(modelo->__obterDefinicaoObjeto(ParserEsquema::DEFINICAO_SQL));
   prog_pb->setValue(30);

   /* Após a criação do banco de dados, é necessário fechar a conexão e reconectar agora
      no banco recém criado para criar os demais objetos */
   conexao->fechar();
   conexao->definirParamConexao(ConexaoBD::PARAM_NOME_BD, modelo->obterNome());
   rot_prog_lbl->setText(trUtf8("Conectando ao banco de dados '%1'...").arg(QString::fromUtf8(modelo->obterNome())));
   rot_prog_lbl->repaint();
   conexao->conectar();
   prog_pb->setValue(50);

   //Cria os demais objetos no novo banco
   rot_prog_lbl->setText(trUtf8("Criando objetos No banco de dados '%1'...").arg(QString::fromUtf8(modelo->obterNome())));
   rot_prog_lbl->repaint();
   conexao->executarComandoDDL(modelo->obterDefinicaoObjeto(ParserEsquema::DEFINICAO_SQL, false));
  }

  //Finaliza o progresso da exportação
  prog_pb->setValue(100);
  rot_prog_lbl->setText(trUtf8("Exportação finalizada com sucesso!"));
  ico_lbl->setPixmap(QPixmap(QString(":/icones/icones/msgbox_info.png")));
  ico_lbl->setVisible(true);

  prog_tarefa->close();
  disconnect(this->modelo, NULL, prog_tarefa, NULL);

  //Oculta os widgets de progresso após 10 segundos
  QTimer::singleShot(10000, this, SLOT(ocultarProgressoExportacao(void)));
 }
 catch(Excecao &e)
 {
  //Exibe no progresso a mensagem de falha
  rot_prog_lbl->setText(trUtf8("Falha na exportação!"));
  rot_prog_lbl->repaint();
  ico_lbl->setPixmap(QPixmap(QString(":/icones/icones/msgbox_erro.png")));
  ico_lbl->setVisible(true);

  prog_tarefa->close();
  disconnect(this->modelo, NULL, prog_tarefa, NULL);

  //Oculta os widgets de progresso após 10 segundos
  QTimer::singleShot(10000, this, SLOT(ocultarProgressoExportacao(void)));
  throw Excecao(e.obterMensagemErro(),e.obterTipoErro(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
 }
}
//-----------------------------------------------------------
void FormExportacao::ocultarProgressoExportacao(void)
{
 ln2_frm->setVisible(false);
 rot_prog_lbl->setVisible(false);
 prog_pb->setVisible(false);
 ico_lbl->setVisible(false);
 this->resize(this->minimumSize());
}
//-----------------------------------------------------------
void FormExportacao::habilitarTipoExportacao(void)
{
 bool exp_arq=(sender()==exportacao_arq_rb);

 //Widgets habilitados quando a exportação é para arquivo
 modelo_sql_lbl->setEnabled(exp_arq);
 arquivo_lbl->setEnabled(exp_arq);
 arquivo_edt->setEnabled(exp_arq);
 sel_arquivo_tb->setEnabled(exp_arq);
 pgsql_lbl->setEnabled(exp_arq);
 pgsqlvers_cmb->setEnabled(exp_arq);
 dica_lbl->setEnabled(exp_arq);

 //Widgets habilitados quando a exportação é para o sgbd
 modelo_sgbd->setEnabled(!exp_arq);
 conexoes_lbl->setEnabled(!exp_arq);
 conexoes_cmb->setEnabled(!exp_arq);
 pgsqlvers_chk->setEnabled(!exp_arq);
 pgsqlvers1_cmb->setEnabled(!exp_arq && pgsqlvers_chk->isChecked());
 dica1_lbl->setEnabled(!exp_arq);
 alerta_frm->setEnabled(!exp_arq);

 exportar_btn->setEnabled((exportacao_sgbd_rb->isChecked() && conexoes_cmb->count() > 0) ||
                          (exportacao_arq_rb->isChecked() && !arquivo_edt->text().isEmpty()));
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

 exportar_btn->setEnabled(!arquivo_edt->text().isEmpty());
}
//***********************************************************
