# pt_BR:
# Definição SQL para modelo de banco de dados
# Versão PostgreSQL: 8.x, 9.0
# ATENÇÃO: Não modifique este arquivo a não ser que você saiba
#          o que está fazendo.
#
# en_US:
# SQL definition for database model
# PostgreSQL Version: 8.x, 9.0
# CAUTION: Do not modify this file unless you know what
#          you are doing.

[/*
 pt_BR:
  Banco de dados gerado com pgModeler (PostgreSQL Database Modeller).
  Site do Projeto: sourceforge.net/projects/pgmodeler
  Autor da Modelagem: ] 

%if @{author} %then
 @{author} 
%else
  ---
%end

$br $br
[en_US:
  Database generated with pgModeler (PostgreSQL Database Modeller).
  Project Site: sourceforge.net/projects/pgmodeler
  Model Author: ] 

%if @{author} %then
 @{author} 
%else
  ---
%end
$br [*/] $br $br


%if @{role} %then @{role} %end
%if @{tablespace} %then @{tablespace} %end
%if @{database} %then @{database} %end
%if @{schema} %then @{schema} %end
%if @{shell-types} %then @{shell-types} %end
%if @{objects} %then @{objects} %end
%if @{grant} %then @{grant} %end

$br