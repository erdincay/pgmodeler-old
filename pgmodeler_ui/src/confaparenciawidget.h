/*
# Projeto: Modelador de Banco de Dados PostgreSQL (pgsqlDBM)
# Sub-projeto: Biblioteca pgsqldbm_ui
# Classe: ConfAparenciaWidget
# Descrição: Implementa o widget de configurações de aparência dos objetos do modelo.
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
#ifndef CONF_APARENCIA_WIDGET_H
#define CONF_APARENCIA_WIDGET_H

#include "ui_confaparenciawidget.h"
#include "confbasewidget.h"
#include "cenaobjetos.h"
#include "modelobd.h"
#include <algorithm>
//***********************************************************
class ConfAparenciaWidget: public QWidget, public Ui::ConfAparenciaWidget, public ConfBaseWidget {
 private:
  Q_OBJECT

  class ItemConfAparencia {
   public:
    QString id_conf;
    QTextCharFormat fmt_fonte;
    QColor cores[3];
    bool conf_obj;
  };

  QColorDialog cor_dlg;
  QGraphicsView *viewp;
  CenaObjetos *cena;
  ModeloBD *modelo;
  vector<ItemConfAparencia> itens_conf;

  void criarObjetosExemplo(void);

 public:
  ConfAparenciaWidget(QWidget * parent=0);
  ~ConfAparenciaWidget(void);

  void salvarConfiguracao(void);
  void carregarConfiguracao(void);

 private slots:
  void habilitarElemConfiguracao(void);
  void aplicarEstiloFonte(void);
  void aplicarCorElemento(void);
  void aplicarConfiguracao(void){};

 public slots:
  void restaurarPadroes(void);
};
//***********************************************************
#endif
