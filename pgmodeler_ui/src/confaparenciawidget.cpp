#include "confaparenciawidget.h"
//***********************************************************
ConfAparenciaWidget::ConfAparenciaWidget(QWidget * parent) : QWidget(parent)
{
 setupUi(this);

 QString ids_confs[]={
  AtributosParsers::GLOBAL, AtributosParsers::RESTRICOES, AtributosParsers::SELECAO_OBJETO,
  AtributosParsers::TIPO_OBJETO, AtributosParsers::ARCO_CADEADO, AtributosParsers::CORPO_CADEADO,
  AtributosParsers::NOME_ESQUEMA_TABELA, AtributosParsers::NOME_TABELA, AtributosParsers::CORPO_TABELA,
  AtributosParsers::CORPO_EXT_TABELA, AtributosParsers::TITULO_TABELA, ObjetoBase::obterNomeEsquemaObjeto(OBJETO_REGRA),
  ObjetoBase::obterNomeEsquemaObjeto(OBJETO_REGRA), ObjetoBase::obterNomeEsquemaObjeto(OBJETO_INDICE),
  ObjetoBase::obterNomeEsquemaObjeto(OBJETO_INDICE), ObjetoBase::obterNomeEsquemaObjeto(OBJETO_GATILHO),
  ObjetoBase::obterNomeEsquemaObjeto(OBJETO_GATILHO), AtributosParsers::NOME_ESQUEMA_VISAO, AtributosParsers::NOME_VISAO,
  AtributosParsers::CORPO_VISAO, AtributosParsers::TITULO_VISAO, AtributosParsers::ALIAS,
  AtributosParsers::COLUNA_REF, AtributosParsers::TABELA_REF, AtributosParsers::REFERENCIA,
  ObjetoBase::obterNomeEsquemaObjeto(OBJETO_CAIXA_TEXTO), AtributosParsers::COLUNA, AtributosParsers::COLUNA,
  AtributosParsers::COLUNA_HERDADA, AtributosParsers::COLUNA_PROTEGIDA, AtributosParsers::COLUNA_PK,
  AtributosParsers::COLUNA_PK, AtributosParsers::COLUNA_FK, AtributosParsers::COLUNA_FK,
  AtributosParsers::COLUNA_UQ, AtributosParsers::COLUNA_UQ, AtributosParsers::COLUNA_NN,
  AtributosParsers::COLUNA_NN, AtributosParsers::RELACIONAMENTO, AtributosParsers::ROTULO,
  AtributosParsers::ROTULO, AtributosParsers::ATRIBUTO, AtributosParsers::ATRIBUTO };
 int i, qtd=elemento_cmb->count(),
     vet_ids_aux[]={ 2, 4, 5, 8, 9, 10, 12, 14, 16, 19, 20,
                     24, 25, 27, 31, 33, 35, 37, 38, 40, 42 };
 vector<int> ids_confs_obj(vet_ids_aux, vet_ids_aux + sizeof(vet_ids_aux) / sizeof(int));

 itens_conf.resize(qtd);
 for(i=0; i < qtd; i++)
 {
  itens_conf[i].id_conf=ids_confs[i];
  itens_conf[i].conf_obj=(std::find(ids_confs_obj.begin(), ids_confs_obj.end(), i)!=ids_confs_obj.end());
 }

 modelo=new ModeloBD;
 cena=new CenaObjetos;
 cena->setSceneRect(QRectF(0,0,500,500));

 //Aloca o viewport com algumas opções de otimização na renderização
 viewp=new QGraphicsView(cena);
 viewp->setEnabled(false);
 viewp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
 viewp->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
 viewp->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

 //Ativa o antialiasing de fonte e objetos
 viewp->setRenderHint(QPainter::Antialiasing);
 viewp->setRenderHint(QPainter::TextAntialiasing);
 viewp->setRenderHint(QPainter::SmoothPixmapTransform);

 //Força a cena a ser desenhada da esquerda para a direita e de cima para baixo
 viewp->setAlignment(Qt::AlignLeft | Qt::AlignTop);

 //Otimizações: Cache do background (grade) e atualização mínima do viewport
 viewp->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
 viewp->centerOn(0,0);

 confaparencia_grid->addWidget(viewp, confaparencia_grid->count()-1, 0, 1, 5);
 this->habilitarElemConfiguracao();

 connect(elemento_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(habilitarElemConfiguracao(void)));
 connect(cor1_tb, SIGNAL(clicked(void)), this, SLOT(aplicarCorElemento(void)));
 connect(cor2_tb, SIGNAL(clicked(void)), this, SLOT(aplicarCorElemento(void)));
 connect(cor3_tb, SIGNAL(clicked(void)), this, SLOT(aplicarCorElemento(void)));

 connect(fonte_cmb, SIGNAL(currentFontChanged(QFont)), this, SLOT(aplicarEstiloFonte(void)));
 connect(tam_fonte_spb, SIGNAL(valueChanged(double)), this, SLOT(aplicarEstiloFonte(void)));
 connect(negrito_chk, SIGNAL(toggled(bool)), this, SLOT(aplicarEstiloFonte(void)));
 connect(sublinhado_chk, SIGNAL(toggled(bool)), this, SLOT(aplicarEstiloFonte(void)));
 connect(italico_chk, SIGNAL(toggled(bool)), this, SLOT(aplicarEstiloFonte(void)));
}
//-----------------------------------------------------------
ConfAparenciaWidget::~ConfAparenciaWidget(void)
{
 delete(viewp);
 delete(cena);
 delete(modelo);
}
//-----------------------------------------------------------
void ConfAparenciaWidget::criarObjetosExemplo(void)
{
 try
 {
  OGRelacionamento *rel=NULL;
  OGCaixaTexto *caixa=NULL;
  OGTabela *tab=NULL;
  OGVisao *visao=NULL;
  unsigned qtd, i;

  modelo->carregarModelo(AtributosGlobais::DIR_CONFIGURACOES +
                         AtributosGlobais::SEP_DIRETORIO +
                         AtributosGlobais::MODELO_EXEMPLO);

  qtd=modelo->obterNumObjetos(OBJETO_TABELA);
  for(i=0; i < qtd; i++)
  {
   tab=new OGTabela(modelo->obterTabela(i));
   tab->setSelected(i==1);
   cena->addItem(tab);
  }

  qtd=modelo->obterNumObjetos(OBJETO_VISAO);
  for(i=0; i < qtd; i++)
  {
   visao=new OGVisao(modelo->obterVisao(i));
   cena->addItem(visao);
  }

  qtd=modelo->obterNumObjetos(OBJETO_RELACAO);
  for(i=0; i < qtd; i++)
  {
   rel=new OGRelacionamento(modelo->obterRelacionamento(i, OBJETO_RELACAO));
   cena->addItem(rel);
  }

  qtd=modelo->obterNumObjetos(OBJETO_RELACAO_BASE);
  for(i=0; i < qtd; i++)
  {
   rel=new OGRelacionamento(modelo->obterRelacionamento(i, OBJETO_RELACAO_BASE));
   cena->addItem(rel);
  }

  qtd=modelo->obterNumObjetos(OBJETO_CAIXA_TEXTO);
  for(i=0; i < qtd; i++)
  {
   caixa=new OGCaixaTexto(modelo->obterCaixaTexto(i));
   caixa->setSelected(i==0);
   cena->addItem(caixa);
  }
 }
 catch(Excecao &e)
 {
  throw Excecao(e.obterMensagemErro(),e.obterTipoErro(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
 }
}
//-----------------------------------------------------------
void ConfAparenciaWidget::carregarConfiguracao(void)
{
 try
 { 
  int i, qtd=itens_conf.size();

  ObjetoGrafico::carregarEstiloObjetos();
  criarObjetosExemplo();

  for(i=0; i < qtd; i++)
  {
   if(itens_conf[i].conf_obj)
   {
    ObjetoGrafico::obterEstiloPreenchimento(itens_conf[i].id_conf,
                                            itens_conf[i].cores[0], itens_conf[i].cores[1]);
    itens_conf[i].cores[2]=ObjetoGrafico::obterEstiloBorda(itens_conf[i].id_conf).color();
   }
   else
    itens_conf[i].fmt_fonte=ObjetoGrafico::obterEstiloFonte(itens_conf[i].id_conf);
  }

  cena->update();
 }
 catch(Excecao &e)
 {
  throw Excecao(e.obterMensagemErro(),e.obterTipoErro(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
 }
}
//-----------------------------------------------------------
void ConfAparenciaWidget::habilitarElemConfiguracao(void)
{
 QPalette pal;
 int idx=elemento_cmb->currentIndex();

 fonte_cmb->setEnabled(idx==0);
 fonte_lbl->setEnabled(idx==0);
 tam_fonte_spb->setEnabled(idx==0);
 unidade_lbl->setEnabled(idx==0);

 sublinhado_chk->setEnabled(!itens_conf[idx].conf_obj);
 negrito_chk->setEnabled(!itens_conf[idx].conf_obj);
 italico_chk->setEnabled(!itens_conf[idx].conf_obj);

 cores_lbl->setVisible(idx!=0);
 cor1_tb->setVisible(idx!=0);
 cor2_tb->setVisible(itens_conf[idx].conf_obj);
 cor3_tb->setVisible(itens_conf[idx].conf_obj);

 if(!itens_conf[idx].conf_obj)
 {
  QTextCharFormat fmt=ObjetoGrafico::obterEstiloFonte(itens_conf[idx].id_conf);
  pal.setColor(QPalette::Button, fmt.foreground());
  cor1_tb->setPalette(pal);
  sublinhado_chk->setChecked(fmt.font().underline());
  italico_chk->setChecked(fmt.font().italic());
  negrito_chk->setChecked(fmt.font().bold());
  fonte_cmb->setCurrentFont(fmt.font());
 }
 else
 {
  QColor cor1, cor2;

  ObjetoGrafico::obterEstiloPreenchimento(itens_conf[idx].id_conf, cor1, cor2);

  pal.setColor(QPalette::Button, cor1);
  cor1_tb->setPalette(pal);

  pal.setColor(QPalette::Button, cor2);
  cor2_tb->setPalette(pal);

  pal.setColor(QPalette::Button, ObjetoGrafico::obterEstiloBorda(itens_conf[idx].id_conf).color());
  cor3_tb->setPalette(pal);

  sublinhado_chk->setChecked(false);
  italico_chk->setChecked(false);
  negrito_chk->setChecked(false);
 }
}
//-----------------------------------------------------------
void ConfAparenciaWidget::aplicarCorElemento(void)
{
 QToolButton *btn=dynamic_cast<QToolButton *>(sender());

 if(btn)
 {
  QPalette pal;
  unsigned idx_cor;

  pal=btn->palette();
  cor_dlg.setCurrentColor(pal.color(QPalette::Button));
  cor_dlg.exec();

  if(cor_dlg.result()==QDialog::Accepted)
  {
   pal.setColor(QPalette::Button, cor_dlg.selectedColor());
   btn->setPalette(pal);

   if(itens_conf[elemento_cmb->currentIndex()].conf_obj)
   {
    if(btn==cor1_tb) idx_cor=0;
    else if(btn==cor2_tb) idx_cor=1;
    else idx_cor=3;

    itens_conf[elemento_cmb->currentIndex()].cores[idx_cor]=cor_dlg.selectedColor();
    ObjetoGrafico::definirCorElemento(itens_conf[elemento_cmb->currentIndex()].id_conf, cor_dlg.selectedColor(), idx_cor);
   }
   else
   {
    itens_conf[elemento_cmb->currentIndex()].fmt_fonte.setForeground(cor_dlg.selectedColor());
    ObjetoGrafico::definirEstiloFonte(itens_conf[elemento_cmb->currentIndex()].id_conf,
                                      itens_conf[elemento_cmb->currentIndex()].fmt_fonte);
   }

   modelo->definirObjetosModificados();
   cena->update();
  }
 }
}
//-----------------------------------------------------------
void ConfAparenciaWidget::aplicarEstiloFonte(void)
{
 QFont fonte;

 fonte=itens_conf[elemento_cmb->currentIndex()].fmt_fonte.font();
 fonte.setBold(negrito_chk->isChecked());
 fonte.setItalic(italico_chk->isChecked());
 fonte.setUnderline(sublinhado_chk->isChecked());
 fonte.setPointSizeF(tam_fonte_spb->value());

 itens_conf[elemento_cmb->currentIndex()].fmt_fonte.setFont(fonte);
 ObjetoGrafico::definirEstiloFonte(itens_conf[elemento_cmb->currentIndex()].id_conf,
                                   itens_conf[elemento_cmb->currentIndex()].fmt_fonte);

 modelo->definirObjetosModificados();
 cena->update();
}
//***********************************************************
