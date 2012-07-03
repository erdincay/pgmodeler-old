/*
# Projeto: Modelador de Banco de Dados PostgreSQL (pgsqlDBM)
# Sub-projeto: Biblioteca pgsqldbm_ui
# Classe: ConfConexoesWidget
# Descrição: Implementa o widget de configurações de conexões com o sgbd.
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
#ifndef CONF_CONEXOES_WIDGET_H
#define CONF_CONEXOES_WIDGET_H

#include "ui_confconexoeswidget.h"
#include "confbasewidget.h"
//***********************************************************
class ConfConexoesWidget: public QWidget, public Ui::ConfConexoesWidget, public ConfBaseWidget {
 public:
  Q_OBJECT

 public:
  ConfConexoesWidget(QWidget * parent=0);

  void salvarConfiguracao(void);
  void carregarConfiguracao(void);

 public slots:
  void aplicarConfiguracao(void){}
  void restaurarPadroes(void){}
};
//***********************************************************
#endif
