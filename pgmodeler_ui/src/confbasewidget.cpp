#include "confbasewidget.h"
//***********************************************************
void ConfBaseWidget::adicionarParamConfiguracao(const QString &param, const map<QString, QString> &atributos)
{
 if(!param.isEmpty() && !atributos.empty())
  params_config[param]=atributos;
}
//-----------------------------------------------------------
map<QString, map<QString, QString> > ConfBaseWidget::obterParamsConfiguracao(void)
{
 return(params_config);
}
//-----------------------------------------------------------
void ConfBaseWidget::excluirParamConfiguracao(const QString &param)
{
 params_config.erase(param);
}
//-----------------------------------------------------------
void ConfBaseWidget::excluirParamsConfiguracao(void)
{
 params_config.clear();
}
//-----------------------------------------------------------
void ConfBaseWidget::carregarConfiguracao(const QString &id_conf, const vector<QString> &atribs_chave)
{
 try
 {
  //Reinicia o parser XML para a leitura do arquivo
  ParserXML::reiniciarParser();

  ParserXML::definirArquivoDTD(AtributosGlobais::DIR_CONFIGURACOES +
                               AtributosGlobais::SEP_DIRETORIO +
                               id_conf +
                               AtributosGlobais::EXT_DTD_OBJETO,
                               id_conf);

  ParserXML::carregarArquivoXML(AtributosGlobais::DIR_CONFIGURACOES +
                                AtributosGlobais::SEP_DIRETORIO +
                                id_conf +
                                AtributosGlobais::EXT_CONFIGURACAO);

  if(ParserXML::acessarElemento(ParserXML::ELEMENTO_FILHO))
  {
   do
   {
    /* Certificando que só elementos xml serão lidos do parser,
      qualquer outro tipo de objeto xml será ignorado */
    if(ParserXML::obterTipoElemento()==XML_ELEMENT_NODE)
    {
     this->obterParamsConfiguracao(atribs_chave);

     if(ParserXML::possuiElemento(ParserXML::ELEMENTO_FILHO))
     {
      ParserXML::salvarPosicao();
      ParserXML::acessarElemento(ParserXML::ELEMENTO_FILHO);

      do
      {
       this->obterParamsConfiguracao(atribs_chave);
      }
      while(ParserXML::acessarElemento(ParserXML::ELEMENTO_POSTERIOR));

      ParserXML::restaurarPosicao();
     }
    }
   }
   while(ParserXML::acessarElemento(ParserXML::ELEMENTO_POSTERIOR));
  }
 }
 catch(Excecao &e)
 {
  //Redireciona qualquer exceção capturada
  throw Excecao(e.obterMensagemErro(),e.obterTipoErro(),__PRETTY_FUNCTION__,__FILE__,__LINE__, &e);
 }
}
//-----------------------------------------------------------
void ConfBaseWidget::obterParamsConfiguracao(const vector<QString> &atribs_chave)
{
 map<QString, QString> atrib_aux;
 map<QString, QString>::iterator itr, itr_end;
 QString chave;

 ParserXML::obterAtributosElemento(atrib_aux);

 itr=atrib_aux.begin();
 itr_end=atrib_aux.end();

 while(itr!=itr_end && chave.isEmpty())
 {
  if(chave.isEmpty() && find(atribs_chave.begin(), atribs_chave.end(), itr->first)!=atribs_chave.end())
   chave=itr->second;
  itr++;
 }

 if(chave.isEmpty())
  chave=ParserXML::obterNomeElemento();

 if(!atrib_aux.empty())
  params_config[chave]=atrib_aux;
}
//***********************************************************
