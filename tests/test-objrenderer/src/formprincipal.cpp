#include "formprincipal.h"
//**********************************************************
FormPrincipal::FormPrincipal(QWidget *parent) : QMainWindow(parent)
{
 setupUi(this);
 modelo=new ModeloBD;
 cena=new CenaObjetos;
 viewp=new QGraphicsView(cena,this);
 connect(limpar_btn, SIGNAL(clicked(void)), codigo_txt, SLOT(clear(void)));
 connect(criar_btn, SIGNAL(clicked(void)), this, SLOT(criarObjeto(void)));
 connect(atualizar_btn, SIGNAL(clicked(void)), this, SLOT(atualizarObjeto(void)));
}
//----------------------------------------------------------
FormPrincipal::~FormPrincipal(void)
{
 delete(modelo);
 delete(viewp);
 delete(cena);
}
//----------------------------------------------------------
void FormPrincipal::show(void)
{
 cena->setSceneRect(0,0,10000,10000);
 viewp->setGeometry(0,0,750,750);
 //viewp->scale(3,3);
 viewp->setRenderHint(QPainter::Antialiasing, true);
 viewp->setRenderHint(QPainter::TextAntialiasing, true);
 QWidget::show();
}
//----------------------------------------------------------
void FormPrincipal::atualizarObjeto(void)
{
 cena->alinharObjetosGrade();
 /*RelacionamentoBase *rel=modelo->obterRelacionamento(1, OBJETO_RELACAO);

 rel->definirProtegido(true);*/
 /*Tabela *tabela=modelo->obterTabela(0);

 tabela->definirNome("tabela_teste1");
 try
 {
  tabela->removerRestricao(0);
 }
 catch(Excecao &e)
 {}

 try
 {
 tabela->removerColuna(0);
 }
 catch(Excecao &)
 {}

 try
 {
 tabela->removerRegra(0);
 tabela->removerRegra(0);
 tabela->removerGatilho(0);
 tabela->removerGatilho(0);
  tabela->removerGatilho(0);
 }
 catch(Excecao &)
 {}

 tabela->definirModificado(true); */
}
//----------------------------------------------------------
void FormPrincipal::criarObjeto(void)
{
 ObjetoBase *objeto=NULL;
 ObjetoGrafico::carregarEstiloObjetos();

 ParserXML::reiniciarParser();
 ParserXML::carregarBufferXML(codigo_txt->toPlainText().toUtf8());

 if(ParserXML::acessarElemento(ParserXML::ELEMENTO_FILHO))
 {
  do
  {
   ParserXML::salvarPosicao();
   objeto=modelo->criarObjeto(modelo->obterTipoObjeto(ParserXML::obterNomeElemento()));

   if(objeto)
   {
    if(objeto->obterTipoObjeto()!=OBJETO_RESTRICAO &&
       objeto->obterTipoObjeto()!=OBJETO_INDICE)
    {
     if(!dynamic_cast<RelacionamentoBase *>(objeto))
     modelo->adicionarObjeto(objeto);

     if(dynamic_cast<Visao *>(objeto))
     {
      OGVisao *obj_grafico=NULL;
      obj_grafico=new OGVisao(dynamic_cast<Visao *>(objeto));
      cena->addItem(obj_grafico);
     }
     else if(dynamic_cast<CaixaTexto *>(objeto))
     {
      OGCaixaTexto *obj_grafico=NULL;
      obj_grafico=new OGCaixaTexto(dynamic_cast<CaixaTexto *>(objeto));
      cena->addItem(obj_grafico);
     }
     else if(dynamic_cast<Tabela *>(objeto))
     {
      OGTabela *obj_grafico=NULL;
      obj_grafico=new OGTabela(dynamic_cast<Tabela *>(objeto));
      cena->addItem(obj_grafico);
     }
     else if(dynamic_cast<RelacionamentoBase *>(objeto))
     {
      OGRelacionamento *obj_grafico=NULL;
      obj_grafico=new OGRelacionamento(dynamic_cast<RelacionamentoBase *>(objeto));
      cena->addItem(obj_grafico);
     }
    }
   }
   ParserXML::restaurarPosicao();
  }
  while(ParserXML::acessarElemento(ParserXML::ELEMENTO_POSTERIOR));
 }

 viewp->show();
 codigo_txt->setPlainText("<dbmodel>\n\n</dbmodel>\n");
}
//**********************************************************
