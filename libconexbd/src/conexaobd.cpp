#include "conexaobd.h"
//***********************************************************
ConexaoBD::ConexaoBD(void)
{
 conexao=NULL;
}
//-----------------------------------------------------------
ConexaoBD::ConexaoBD(const QString &servidor, const QString &porta, const QString &usuario, const QString &senha, const QString &nome_bd)
{
 //Configura os parâmetros básicos de conexão
 definirParamConexao(ParamConexao::PARAM_FQDN_SERVIDOR, servidor);
 definirParamConexao(ParamConexao::PARAM_PORTA, porta);
 definirParamConexao(ParamConexao::PARAM_USUARIO, usuario);
 definirParamConexao(ParamConexao::PARAM_SENHA, senha);
 definirParamConexao(ParamConexao::PARAM_NOME_BD, nome_bd);

 //Estabelece a conexão
 conectar();
}
//-----------------------------------------------------------
ConexaoBD::~ConexaoBD(void)
{
 if(conexao)
  PQfinish(conexao);
}
//-----------------------------------------------------------
void ConexaoBD::definirParamConexao(const QString &parametro, const QString &valor)
{
 //Dispara um erro caso se tente atribuir um valor a um parâmetro vazio
 if(parametro=="")
  throw Excecao(ERR_CONEXBD_ATRPARAMINVCONEX, __PRETTY_FUNCTION__, __FILE__, __LINE__);

 //Atribui o valor ao parâmetro selecionado e gera a string de conexão
 params_conexao[parametro]=valor;
 gerarStringConexao();
}
//-----------------------------------------------------------
void ConexaoBD::gerarStringConexao(void)
{
 map<QString, QString>::iterator itr, itr_end;

 itr=params_conexao.begin();
 itr_end=params_conexao.end();

 //Varre o mapa de parâmetros de conexão
 str_conexao="";
 while(itr!=itr_end)
 {
  //Concatena cada parâmetro a seu valor, separândo-os por um sinal de igual
  str_conexao+=itr->first + "=" + itr->second + " ";
  itr++;
 }
}
//-----------------------------------------------------------
void ConexaoBD::conectar(void)
{
 QString str_aux;

 /* Caso a string de conexão não esteja estabelecida indica que o usuário
    está tentado conectar sem configurar os parâmetros de conexão, sendo
    assim um erro será disparado */
 if(str_conexao=="")
  throw Excecao(ERR_CONEXBD_CONEXSEMPARAMCONFIG, __PRETTY_FUNCTION__, __FILE__, __LINE__);

 //Tenta conectar ao banco de dados
 conexao=PQconnectdb(str_conexao.toStdString().c_str());

 /* Caso o descritor de conexão não foi alocado ou se o estado da conexão
    seja CONNECTION_BAD indica que a conexão não foi bem sucedida */
 if(conexao==NULL || PQstatus(conexao)==CONNECTION_BAD)
 {
  //Dispara o erro gerado pelo SGBD
  str_aux=QString(Excecao::obterMensagemErro(ERR_CONEXBD_CONEXNAOESTABELECIDA))
          .arg(PQerrorMessage(conexao));
  throw Excecao(str_aux, ERR_CONEXBD_CONEXNAOESTABELECIDA,
                __PRETTY_FUNCTION__, __FILE__, __LINE__);
 }
}
//-----------------------------------------------------------
void ConexaoBD::fecharConexao(void)
{
 //Dispara um erro caso o usuário tente fechar uma conexão não iniciada
 if(!conexao)
  throw Excecao(ERR_CONEXBD_OPRCONEXNAOALOC, __PRETTY_FUNCTION__, __FILE__, __LINE__);

 //Finaliza a conexão
 PQfinish(conexao);
 conexao=NULL;
}
//-----------------------------------------------------------
void ConexaoBD::reiniciarConexao(void)
{
 //Dispara um erro caso o usuário tente reiniciar uma conexão não iniciada
 if(!conexao)
  throw Excecao(ERR_CONEXBD_OPRCONEXNAOALOC, __PRETTY_FUNCTION__, __FILE__, __LINE__);

 //Reinicia a conexão
 PQreset(conexao);
}
//-----------------------------------------------------------
QString ConexaoBD::obterParamConexao(const QString &parametro)
{
 return(params_conexao[parametro]);
}
//-----------------------------------------------------------
QString ConexaoBD::obterStringConexao(void)
{
 return(str_conexao);
}
//-----------------------------------------------------------
bool ConexaoBD::conexaoEstabelecida(void)
{
 return(conexao!=NULL);
}
//-----------------------------------------------------------
void ConexaoBD::executarComandoSQL(const QString &sql, Resultado &resultado)
{
 Resultado *novo_res=NULL;
 PGresult *res_sql=NULL;
 QString str_aux;

 //Dispara um erro caso o usuário tente reiniciar uma conexão não iniciada
 if(!conexao)
  throw Excecao(ERR_CONEXBD_OPRCONEXNAOALOC, __PRETTY_FUNCTION__, __FILE__, __LINE__);

 //Aloca um novo resultado para receber o result-set vindo da execução do comando sql
 res_sql=PQexec(conexao, sql.toStdString().c_str());
 if(!res_sql)
 {
  str_aux=QString(Excecao::obterMensagemErro(ERR_CONEXBD_CMDSQLNAOEXECUTADO))
          .arg(PQerrorMessage(conexao));
  throw Excecao(str_aux,ERR_CONEXBD_CMDSQLNAOEXECUTADO, __PRETTY_FUNCTION__, __FILE__, __LINE__);
 }

 novo_res=new Resultado(res_sql);
 //Copia o novo resultado para o resultado do parâmetro
 resultado=*(novo_res);
 //Desaloca o resultado criado
 delete(novo_res);
}
//-----------------------------------------------------------
void ConexaoBD::operator = (ConexaoBD conex)
{
 this->params_conexao=conex.params_conexao;
 this->str_conexao=conex.str_conexao;
 conectar();
}
//***********************************************************
