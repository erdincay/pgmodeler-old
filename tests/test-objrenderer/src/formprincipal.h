/*
# Projeto: Modelador de Banco de Dados PostgreSQL (pgsqlDBM)
# Sub-projeto: test-objrender
# Classe: FormPrincipal
# Descrição: Definição da classe que implementa o formulário principal de testes das classes,
#            da biblioteca libobjrender.
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
#ifndef FORM_PRINCIPAL_H
#define FORM_PRINCIPAL_H

#include <QtGui>
//#include <QGraphicsScene>
#include "ui_formprincipal.h"
#include "modelobd.h"
#include "ogcaixatexto.h"
#include "ogvisao.h"
#include "ogtabela.h"
#include "ogrelacionamento.h"
#include "cenaobjetos.h"
//***********************************************************
class FormPrincipal: public QMainWindow, public Ui::FormPrincipal {
 Q_OBJECT

 private:
   ModeloBD *modelo;
   QGraphicsView *viewp;
   CenaObjetos *cena;


 public:
   FormPrincipal(QWidget *parent = 0);
  ~FormPrincipal(void);

 private slots:
   void criarObjeto(void);
   void atualizarObjeto(void);

 public slots:
   void show(void);

};
//***********************************************************
#endif
