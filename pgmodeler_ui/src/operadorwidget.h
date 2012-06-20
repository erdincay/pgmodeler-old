/*
# Projeto: Modelador de Banco de Dados PostgreSQL (pgsqlDBM)
# Sub-projeto: Biblioteca pgsqldbm_ui
# Classe: OperadorWidget
# Descrição: Definição da classe que implementa o formulário de
#            edição dos atributos de operadores.
#
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
#ifndef OPERADOR_WIDGET_H
#define OPERADOR_WIDGET_H

#include "objetobasewidget.h"
#include "tipopgsqlwidget.h"
#include "ui_operadorwidget.h"
//***********************************************************
class OperadorWidget: public ObjetoBaseWidget, public Ui::OperadorWidget {
 Q_OBJECT

 private:
   TipoPgSQLWidget *tipo_args[2];
   SeletorObjetoWidget *sel_funcoes[3],
                       *sel_operadores[6];

 public:
   OperadorWidget(QWidget * parent = 0);
  ~OperadorWidget(void);
   void definirAtributos(ModeloBD *modelo, ListaOperacoes *lista_op, Operador *operador);

 private slots:
  void hideEvent(QHideEvent *);

 public slots:
   void aplicarConfiguracao(void);
};
//***********************************************************
#endif
