# pt_BR:
# Definição SQL para espaços de tabela
# Versão PostgreSQL: 8.x, 9.0
# ATENÇÃO: Não modifique este arquivo a não ser que você saiba
#          o que está fazendo.
#
# en_US:
# SQL definition for tablespaces
# PostgreSQL Version: 8.x, 9.0
# CAUTION: Do not modify this file unless you know what
#          you are doing.

[-- object: ] @{name} [ | type: ] @{sql-object} [ -- ] $br

[CREATE TABLESPACE ] @{name} $br
$tb [LOCATION ] @{directory}; $br

%if @{owner} %then @{owner} %end
%if @{comment} %then @{comment} %end
