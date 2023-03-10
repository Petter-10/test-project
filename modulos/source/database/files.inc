
#include <YSI_Storage\y_ini>
#include <YSI_Extra\y_inline_bcrypt>

#include <YSI_Coding\y_hooks>

// Diretorios
#define SETTINGS_FILE		DIRECTORY_MAIN"config.cfg"
#define DIRECTORY_LOGS      DIRECTORY_MAIN"logs/server.log"

// Carregar arquivos de configuracao
hook OnScriptInit() {
    // Configurações de logs
	Logger_ToggleDebug(SERVER_DEBUG_HANDLER, true);
	Logger_ToggleDebug(MYSQL_DEBUG_HANDLER, true);

	Logger_ToggleDebug(PLAYER_DEBUG_HANDLER, true);

   // Verificar a existência de arquivo
    if(!fexist(SETTINGS_FILE)) {
        new INI:confFile = INI_Open(SETTINGS_FILE);

        // Deposito de encomendas
        INI_SetTag(confFile, "deposito");

        INI_WriteInt(confFile, "ls", 5000);
        INI_WriteInt(confFile, "lv", 5000);
        INI_WriteInt(confFile, "sf", 5000);

        INI_Close(confFile);

        Logger_Dbg(SERVER_DEBUG_HANDLER, "arquivo de configuracao nao encontrado, criando...");
    }
    else {
        INI_ParseFile(SETTINGS_FILE, "ServerConfig_%s");

        Logger_Dbg(SERVER_DEBUG_HANDLER, "arquivo de configuracao carregado");
    }

    // Arquivo de logs
    if(!fexist(DIRECTORY_LOGS)) {
        Logger_Dbg(SERVER_DEBUG_HANDLER, "arquivo de log nao encontrado, criar.");
        
    }
    else {
        // Registrar no log
        new File:handle = fopen(DIRECTORY_LOGS, io_append), string[100];

        format(string, sizeof(string), "[%s] Servidor ligado\n", FormatFullTime());
    	fwrite(handle, string);

        fclose(handle);
    }
    return 1;
}

stock SaveConfigurationFile() {
    // Salvar deposito
    ServerSave_deposito();

    // Logar
    Logger_Dbg(SERVER_DEBUG_HANDLER, "arquivo de configuracao salvo");
    return 1;
}

stock ServerLog(const file[], const text[], GLOBAL_TAG_TYPES:...) {
	new textstring[256], filepatch[65];
    format(textstring, sizeof(textstring), text, ___(2)),

    // Colocar o .log no final
    format(filepatch, sizeof(filepatch), DIRECTORY_MAIN"logs/%s.log", file);

    // Abrir o arquivo
    new File:handle = fopen(filepatch, io_append);

    if(handle) {
        new string[256];

        format(string, sizeof(string), "[%s] %s\n", FormatFullTime(), textstring);
    	fwrite(handle, string);

        fclose(handle);
    }
    else {
        Logger_Err("log nao encontrado", Logger_S("local", file));
    }

	return 1;
}
