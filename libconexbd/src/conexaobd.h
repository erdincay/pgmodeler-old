/*
# Projeto: Squid-Autoconf
# Sub-projeto: Biblioteca libconexbd
# Classe: ConexaoBD
# Descrição: Esta classe encapsula algumas funções de manipulação de conexões
#            com o PostgreSQL implementadas pela biblioteca libpq
# Data de Criação: 13/07/2009
# Copyright (C) 2006-2012 - Raphael Araujo e Silva <rkhaotix@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# Q Public License version 1.0 (QPL 1.0).
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#ifndef CONEXAOBD_H
#define CONEXAOBD_H

#include "resultado.h"
#include <map>
//***********************************************************
//Opções de conexão usando SSL
namespace ModoSSL {
static const QString
  SSL_DESATIVADO="disabled",
  SSL_PERMITIR="allow",
  SSL_PREFERIR="prefer",
  SSL_REQUERER="require",
  SSL_VERIF_AUT_CERT="verify-ca",
  SSL_VERIF_COMPLETA="verify-full";
};

//Parametros usados na string de conexão com o banco
namespace ParamConexao {
static const QString
  PARAM_FQDN_SERVIDOR="host",
  PARAM_IP_SERVIDOR="hostaddr",
  PARAM_PORTA="port",
  PARAM_NOME_BD="dbname",
  PARAM_USUARIO="user",
  PARAM_SENHA="password",
  PARAM_TEMPO_CONEXAO="connect_timeout",
  PARAM_OPCOES="options",
  //PARAM_TTY="tty",
  PARAM_MODO_SSL="sslmode",
  PARAM_CERT_SSL="sslcert",
  PARAM_CHAVE_SSL="sslkey",
  PARAM_CERT_RAIZ_SSL="sslrootcert",
  PARAM_CRL_SSL="sslcrl",
  PARAM_SERVIDOR_KERBEROS="krbsrvname",
  PARAM_LIB_GSSAPI="gsslib";
  //PARAM_SERVICO="service";
};
//-----------------------------------------------------------
class ConexaoBD {
 private:
  //Descritor de conexão com o banco
  PGconn *conexao;

  //Parâmetros usados para gerar a string de conexão
  map<QString, QString> params_conexao;

  //String de conexão formatada
  QString str_conexao;

  //Gera a string de conexão com base no mapa de parâmetros de conexão
  void gerarStringConexao(void);

 public:
  ConexaoBD(void);
  ConexaoBD(const QString &servidor, const QString &porta, const QString &usuario, const QString &senha, const QString &nome_bd);
  ~ConexaoBD(void);

  /* Define um parâmetro de conexão. Este só deve ser chamado antes de se
     conectar ao banco */
  void definirParamConexao(const QString &parametro, const QString &valor);

  //Cria uma conexão simples com o banco
  void conectar(void);

  //Reinicia a conexão com o banco de dados
  void reiniciarConexao(void);

  //Fecha a conexão aberta
  void fecharConexao(void);

  //Retorna o valor definido atualmente para um dado parâmetro da conexão
  QString obterParamConexao(const QString &parametro);

  //Retorna a string de conexão usada para se conectar ao banco
  QString obterStringConexao(void);

  //Retorna se a conexão está estabelecida
  bool conexaoEstabelecida(void);

  /* Executa um comando DDL ou DML no servidor usando a conexão aberta
     retornando um objeto de resutlado da consulta */
  void executarComandoSQL(const QString &sql, Resultado &resultado);

  //Atribui uma conexão a outra
  void operator = (ConexaoBD conex);
};
//***********************************************************
#endif
