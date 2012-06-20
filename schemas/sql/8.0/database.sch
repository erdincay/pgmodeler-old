# pt_BR:
# Definição SQL para banco de dados
# Versão PostgreSQL: 8.0
# ATENÇÃO: Não modifique este arquivo a não ser que você saiba
#          o que está fazendo.
#
# en_US:
# SQL definition for databases
# PostgreSQL Version: 8.0
# CAUTION: Do not modify this file unless that you know what
#          you are doing.

 [-- object: ] @{name} [ | type: ] @{sql-object} [ -- ] $br

[CREATE DATABASE ] @{name} $br

%if @{template} %then
  $tb [TEMPLATE = ] @{template} $br
%end

%if @{encoding} %then
  $tb [ENCODING = ] @{encoding} $br
%end

%if @{tablespace} %then
  $tb [TABLESPACE = ] @{tablespace} $br
%end

; $br

%if @{owner} %then @{owner} %end
%if @{comment} %then @{comment} %end
