
// Módulo de comandos

#include <YSI_Coding\y_hooks>
#include <YSI_Visual\y_commands>

hook OnScriptInit() {
	Command_SetDeniedReturn(true);

	// pegar os comandos
	new countCmds = 0;

	foreach(new i : Command()) {
		countCmds ++;
	}

	// printar
	Logger_Dbg(SERVER_DEBUG_HANDLER, "modulo de comandos carregado", Logger_I("total", countCmds));
	return 1;
}

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) {
	switch(success) {
		case COMMAND_UNDEFINED: {
			SendMsg(playerid, X11_ORANGERED2, "O comando '%s' não existe", cmdtext);

			return COMMAND_DENIED;
		}

		case COMMAND_DENIED: {
			SendMsg(playerid, X11_ORANGERED2, "Você não tem permissão", cmdtext);

			// Informar
			Logger_Dbg(PLAYER_DEBUG_HANDLER, "comando nao permitido digitado", Logger_S("comando", cmdtext), Logger_P(playerid));

			return COMMAND_DENIED;
		}

		case COMMAND_OK: {

		}
	}

	// Logar os comandos
    Logger_Dbg(PLAYER_DEBUG_HANDLER, "novo comando", Logger_S("comando", cmdtext), Logger_P(playerid));
	return COMMAND_OK;
}

public e_COMMAND_ERRORS:OnPlayerCommandPerformed(playerid, cmdtext[], e_COMMAND_ERRORS:success) {
    return COMMAND_OK;
}

#include <groups>
#include <allcmds>
