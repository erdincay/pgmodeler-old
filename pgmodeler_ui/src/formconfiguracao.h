/*
# Projeto: Modelador de Banco de Dados PostgreSQL (pgsqlDBM)
# Sub-projeto: Biblioteca pgsqldbm_ui
# Classe: FormConfiguracao
# Descrição: Formulario que reúne todos os widgets de configuração.
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
#ifndef FORM_CONFIGURACAO_H
#define FORM_CONFIGURACAO_H

#include "ui_formconfiguracao.h"
#include "confaparenciawidget.h"
#include "confgeralwidget.h"
#include "confconexoeswidget.h"
//***********************************************************
class FormConfiguracao: public QDialog, public Ui::FormConfiguracao {
 private:
  Q_OBJECT

  ConfGeralWidget *conf_geral;
  ConfAparenciaWidget *conf_aparencia;
  ConfConexoesWidget *conf_conexoes;

 public:
  FormConfiguracao(QWidget * parent = 0, Qt::WindowFlags f = 0);
  ConfBaseWidget *obterWidgetConfiguracao(unsigned idx);

 public slots:
  void salvarConfiguracao(void);

 private slots:
  void restaurarPadroes(void);
};
//***********************************************************
#endif
