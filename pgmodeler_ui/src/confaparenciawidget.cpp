#include "confaparenciawidget.h"
//***********************************************************
ConfAparenciaWidget::ConfAparenciaWidget(QWidget * parent) : QWidget(parent)
{
 setupUi(this);

 modelo=new ModeloBD;

 cena=new CenaObjetos;
 cena->setSceneRect(QRectF(0,0,250,250));

 //Aloca o viewport com algumas opções de otimização na renderização
 viewp=new QGraphicsView(cena);
 viewp->setEnabled(false);
 viewp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

 //Ativa o antialiasing de fonte e objetos
 viewp->setRenderHint(QPainter::Antialiasing);
 viewp->setRenderHint(QPainter::TextAntialiasing);
 viewp->setRenderHint(QPainter::SmoothPixmapTransform);

 //Força a cena a ser desenhada da esquerda para a direita e de cima para baixo
 viewp->setAlignment(Qt::AlignLeft | Qt::AlignTop);

 //Otimizações: Cache do background (grade) e atualização mínima do viewport
 viewp->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
 viewp->centerOn(0,0);

 confaparencia_grid->addWidget(viewp, confaparencia_grid->count()-1, 0, 1, 4);
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
  ObjetoGrafico::carregarEstiloObjetos();
  criarObjetosExemplo();
 }
 catch(Excecao &e)
 {
  throw Excecao(e.obterMensagemErro(),e.obterTipoErro(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
 }
}
//***********************************************************
