
#include <YSI_Extra\y_inline_mysql>
#include <YSI_Coding\y_hooks>

// Conexoes MySQL
static 
    MySQL: Database, va_query[300];

hook OnScriptInit() {
	// printar
	Logger_Dbg(MYSQL_DEBUG_HANDLER, "modulo de SQL carregado", Logger_S("situacao", (Database == MYSQL_INVALID_HANDLE ? "desativado" : "ativado")));
	return 1;
}

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle) {
	switch(errorid) {
		case 1136: printf("[MySQL] Erro 1136 | A contagem de colunas não corresponde a contagem de valor => \"%s\"", query);
		case 1054: printf("[MySQL] Erro 1054 | Campo invalido => \"%s\"", query);
		case 1065: printf("[MySQL] Erro 1065 | Query vazia (o tamanho da variavel pequeno??) => \"%s\" em \"%s\"", query, callback);
		case 1058: printf("[MySQL] Erro 1058 | A contagem de colunas não corresponde a contagem de valor => \"%s\" em \"%s\"", query, callback);
		case 1203: printf("[MySQL] Erro 1203 | O usuario ja possui o maximo de 'max_user_connections' ativas => \"%s\" em \"%s\"", query, callback);
		case 1045: printf("[MySQL] Erro 1045 | Acesso negado");
		case ER_SYNTAX_ERROR: printf("[MySQL] Erro de Sintaxe => \"%s\"",query);

		default : printf("[MySQL] Error %d | Callback: %s | \"%s\"", errorid, callback, query);
	}
	return 1;
}

stock Database_Init() {
    new
        MySQLOpt: option_id = mysql_init_options();

	mysql_set_option(option_id, AUTO_RECONNECT, true);

	Database = mysql_connect_file("mysql.ini");

	if (Database == MYSQL_INVALID_HANDLE || mysql_errno(Database) != 0) {
		Logger_Fatal("MySQL nao conectado, servidor desligado.");
		return 1;
	}

	mysql_log(ERROR);

	// Logs
	Logger_Dbg(MYSQL_DEBUG_HANDLER, "MySQL conectado com sucesso");
	
	// Carregar os dados
    CallLocalFunction("OnLoadMySQL", "");
    return 1;   
}

stock Database_Close() {
	CallLocalFunction("OnMySQLPreClose", "");
	
    mysql_close(Database);

	// Logs
	Logger_Dbg(MYSQL_DEBUG_HANDLER, "MySQL desconectado com sucesso");
    return 1;
}

stock MySQL_Update(const fquery[], GLOBAL_TAG_TYPES:...) {
	mysql_format(Database, va_query, sizeof(va_query), fquery, ___(1));
	return mysql_tquery(Database, va_query);
}

MySQL:MySQL_Database()
    return Database;

// Logs do player
stock PlayerLog(userid, const text[], GLOBAL_TAG_TYPES:...) {
	new string[145];
	format(string, sizeof(string), text, ___(2));

    MySQL_Update("INSERT INTO `playerlog` ( `user_id`, `log` ) VALUES ( '%i', '%e')", GetAccountID(userid), string);
    return 1;
}

// Restante dos arquivos
#include <files>
