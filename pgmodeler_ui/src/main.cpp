#include "formprincipal.h"
#include "aplicacao.h"
#include <QTranslator>

int main(int argc, char **argv)
{
 try
 {
  Aplicacao app(argc,argv);
  QString local = QLocale::system().name();
  QTranslator tradutor;

  //Carrega o arquivo de tradução da interface de acordo com o locale do sistema
  tradutor.load(AtributosGlobais::DIR_LINGUAS + QString("/pgmodeler-") + local);
  //Instala o tradutor na aplicação
  app.installTranslator(&tradutor);

  /* Aloca o formulário principal.
     Durante a sua alocação pode ser disparadas uma série de exceções que a
     aplicação não é capaz de caputar pois o formulário ainda não foi atribuído
     a esta, desta forma, a alocação do formulário e feita dentro de um
     try-catch para possível captura de erros. A aplicação será abortada
     e o erro mostrado no console caso ocorra. */
  FormPrincipal *fmain=new FormPrincipal;

  //Atribui o formulário alocado à aplicação
  app.setMainWidget(fmain);
  //Exibe o formulário principal e prossegue com a execução da aplicação
  fmain->showMaximized();
  app.installEventFilter(fmain);
  return(app.exec());
 }
 //Caso um erro seja capturado durante a inicialização da aplicação
 catch(Excecao &e)
 {
  deque<Excecao> excecoes;
  deque<Excecao>::iterator itr, itr_end;
  unsigned idx=0;

  //Obtém a lista de exceções geradas
  e.obterListaExcecoes(excecoes);
  itr=excecoes.begin();
  itr_end=excecoes.end();

  //Exibe todas as exceções no console
  while(itr!=itr_end)
  {
   cout << "[" << idx << "] " << itr->obterArquivo().toStdString() << " (" << itr->obterLinha().toStdString() << ")" << endl;
   cout << "    " << itr->obterLocal().toStdString() << endl;
   cout << "      [" << Excecao::obterNomeErro(itr->obterTipoErro()).toStdString() << "] ";
   cout << itr->obterMensagemErro().toStdString() << endl << endl;
   itr++; idx++;
  }

  //Retorna o código de erro da última exceção e aborta a aplicação
  return(e.obterTipoErro());
 }
}
