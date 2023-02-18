
// Módulo de mensagens
#include <YSI_Server\y_colours>

// Defines
#define SendErrorMsg(%0,%1)		        SendMsg(%0, X11_ORANGERED2, "** "%1)
#define SendSyntaxMsg(%0,%1)		    SendMsg(%0, X11_ORANGERED2, "* "%1)
#define SendAdminAction(%0,%1)			SendMsg(%0, X11_ROYALBLUE3, "LSA-ADMIN: {FFFFFF}"%1)
#define SendFormatMessage(%0,%1,%2,%3)	SendMsg(%0, %1, %2":{FFFFFF} "%3)

#define PLAYER_OFFLINE 					"Jogador ID informado é inválido ou está desconectado."
#define SPACE_LINE						"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

static gs_Buffer[256];

stock SendMsg(playerid, colour, const fmat[], GLOBAL_TAG_TYPES:...) {
    format(gs_Buffer, sizeof(gs_Buffer), fmat, ___(3)),
    SendClientMessage(playerid, colour, gs_Buffer);
    return 1;
}

stock SendMsgAll(colour, const fmat[], GLOBAL_TAG_TYPES:...) {
    format(gs_Buffer, sizeof(gs_Buffer), fmat, ___(2)),
    SendClientMessageToAll(colour, gs_Buffer);
    return 1;
}

stock GameTextForPlayerEx(playerid, const fmat[], time, style, GLOBAL_TAG_TYPES:...) {
    format(gs_Buffer, sizeof(gs_Buffer), fmat, ___(4)),
    GameTextForPlayer(playerid, gs_Buffer, time, style);
    return 1;
}

stock GameTextForAllEx(const fmat[], time, style, GLOBAL_TAG_TYPES:...) {
    format(gs_Buffer, sizeof(gs_Buffer), fmat, ___(3)),
    GameTextForAll(gs_Buffer, time, style);
    return 1;
}

stock PlayerTextDrawUpdate(playerid, PlayerText:text, const fmat[], GLOBAL_TAG_TYPES:...) {
    format(gs_Buffer, sizeof(gs_Buffer), fmat, ___(3)),
    PlayerTextDrawSetString(playerid, text, gs_Buffer);
    return 1;
}

stock TextDrawUpdate(Text:text, const fmat[], GLOBAL_TAG_TYPES:...) {
    format(gs_Buffer, sizeof(gs_Buffer), fmat, ___(2)),
    TextDrawSetString(text, gs_Buffer);
    return 1;
}

stock ProxDetector(playerid, radi, color, const message[], GLOBAL_TAG_TYPES:...) {
    format(gs_Buffer, sizeof(gs_Buffer), fmat, ___(4)),
	
    static Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

	foreach(new i : Player) {
		if(IsPlayerInRangeOfPoint(i, radi, x, y ,z))
			SendClientMessage(i, color, gs_Buffer);
	}
	
	return 1;
}
