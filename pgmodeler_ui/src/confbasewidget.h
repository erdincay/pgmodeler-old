/*
# Projeto: Modelador de Banco de Dados PostgreSQL (pgsqlDBM)
# Sub-projeto: Biblioteca pgsqldbm_ui
# Classe: ConfBaseWidget
# Descrição: Implementa operações básicas para gravação de arquivos  e acesso às configuraçoẽs
#            nos widgets de configurações.
#
# Copyright (C) 2006-2012 - Raphael Araújo e Silva <rkhaotix@gmail.com>
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
#ifndef CONF_BASE_WIDGET_H
#define CONF_BASE_WIDGET_H

#include "excecao.h"
#include "parserxml.h"
#include "atributosparsers.h"
//***********************************************************
class ConfBaseWidget {
 private:
  map<QString, map<QString, QString> > params_config;
  void obterParamsConfiguracao(const vector<QString> &atribs_chave);

 protected:
  void salvarConfiguracao(const QString &id_conf);
  void carregarConfiguracao(const QString &id_conf, const vector<QString> &atribs_chave=vector<QString>());

 public:
  ConfBaseWidget(void){}

  void adicionarParamConfiguracao(const QString &param, const map<QString, QString> &atributos);
  map<QString, QString> obterParamConfiguracao(const QString &param);

  void excluirParamConfiguracao(const QString &param);
  void excluirParamsConfiguracao(void);
};
//***********************************************************
#endif
