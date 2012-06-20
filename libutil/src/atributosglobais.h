/*
# Projeto: Modelador de Banco de Dados PostgreSQL (pgsqlDBM)
# Sub-projeto: Biblioteca libutil
# Descrição:  Definição do namespace AtributosGlobais, um espaço de nomes o qual
#             armazena uma série de strings estáticas constantes, usadas
#             para referênciar as variáveis de configuração globais do software.
# Data de Criação: 14/05/2010
#
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
#ifndef ATRIBUTOS_GLOBAIS_H
#define ATRIBUTOS_GLOBAIS_H

#include <cstdlib>
#include <QString>
#include <QDir>
//***********************************************************
namespace AtributosGlobais {
static const QString
   VERSAO_PGMODELER="0.1.0-alfa",
   DIR_RAIZ_ESQUEMAS=getenv("PGMODELER_SCHEMAS_DIR"),
   DIR_CONFIGURACOES=getenv("PGMODELER_CONFIGS_DIR"),
   DIR_LINGUAS=getenv("PGMODELER_LANG_DIR"),

   //Caractere separador de diretórios (/ -> Linux, \\ -> M$ Window$)
   SEP_DIRETORIO=QDir::toNativeSeparators("/"),
   DIR_ESQUEMA_SQL="sql",
   DIR_ESQUEMA_XML="xml",
   DIR_ESQUEMA_COMUM="common",
   EXT_ESQUEMA=".sch",
   DIR_DTD_OBJETO="dtd",
   EXT_DTD_OBJETO=".dtd",
   DTD_RAIZ="dbmodel",
   EXT_CONFIGURACAO=".conf",
   SUF_ARQ_DESTAQUE="-highlight",

   CONF_DESTAQUE_CODIGO="source-code-highlight",
   CONF_ESTILO_OBJETOS="objects-style",
   CONF_GERAL="pgmodeler",
   CONF_CONEXOES="connections",
   CONF_DESTAQUE_SQL="sql-highlight",
   CONF_DESTAQUE_XML="xml-highlight";
};
//***********************************************************
#endif
