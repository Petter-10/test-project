
#include <YSI_Coding\y_timers>
#include <YSI_Extra\y_inline_timers>

#include <YSI_Coding\y_hooks>

hook OnScriptInit() {
    Logger_Dbg(SERVER_DEBUG_HANDLER, "modulo de timers carregado");

    return 1;
}

task ServerUpdate[1000]() {
    // Setar o clima de acordo com a hora atual
    new weatherTime;

	gettime(weatherTime);

	SetWorldTime(weatherTime);
}

task Server_Save[(1000 * 60) * 5]() {
    SaveConfigurationFile();
}

// Autosave
ptask Autosave[(1000 * 60) * 3](playerid) {
    if (IsPlayerLogged(playerid)) {
        Logger_Dbg(SERVER_DEBUG_HANDLER, "autosave executado", Logger_P(playerid));

		CallLocalFunction("OnPlayerAutoSave", "i", playerid);
    }

	return 1;
}
