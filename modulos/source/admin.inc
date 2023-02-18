
// módulo da administração
#include <YSI_Coding\y_hooks>

hook OnScriptInit() {
    Logger_Log("modulo de admins carregado");

    return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
    new playerState = GetPlayerState(playerid);

    switch(playerState) {
        case PLAYER_STATE_DRIVER: {
            new vehicleid = GetPlayerVehicleID(playerid);

            SetVehiclePos(vehicleid, fX, fY, fZ);
        }
        case PLAYER_STATE_ONFOOT: {
            SetPlayerPos(playerid, fX, fY, fZ);
        }
    }

    return 1;
}

// Nicks banidos

static  g_BannedNickname[][MAX_PLAYER_NAME] = {
    "Frankie", ".Ic3Man.", "[CSA]Rogério"
};

stock CheckBannedNicknames(playerid) {
    // Pegar nome
    new playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, sizeof(playerName));

    // Verificar nick
    for(new i; i <sizeof(g_BannedNickname); i++) {
        if(strcmp(g_BannedNickname[i], playerName, true) == 0) {
            Kick(playerid);
            
            Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, ""RED2"Servidor", "{FFFFFF}Este nickname é proibido no servidor.", "Fechar");

            // Pegar ip
            new playerIP[16];
            GetPlayerIp(playerid, playerIP, sizeof(playerIP));

            // Logar
            Logger_Log("entrou com nick proibido", Logger_P(playerid), Logger_S("ip", playerIP), Logger_I("id", playerid));
        }
    }

    return 1;
}

stock CheckStringNickname(const name[]) {
    new bool:isBan = false;

    for(new i; i <sizeof(g_BannedNickname); i++) {
        if(strcmp(g_BannedNickname[i], name, true) == 0) {
            isBan = true;
        }
    }

    return isBan;
}

hook SetupLoginScreen(playerid) {
    CheckBannedNicknames(playerid);

    return 1;
}

// Comandos admin
#include <staff>

// Sistemas de admin
#include <ban>