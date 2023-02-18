
#include <YSI_Coding\y_hooks>

stock CheckPlayerBan(playerid) {
    inline const OnPlayerCheckBan() {
        new rows; 
        
        cache_get_row_count(rows);

        if (rows) {
            new idBan, ban, desban, admin[MAX_PLAYER_NAME], motivo[128], dialogBan[200];

            cache_get_value_name(0, "Admin", admin);
            cache_get_value_name(0, "Motivo", motivo);
            cache_get_value_name_int(0, "BanID", idBan);
            cache_get_value_name_int(0, "Ban", ban);
            cache_get_value_name_int(0, "Desban", desban);

            if (desban <= 0) {
                new hora, minuto, segundo, dia, mes, ano;
                TimestampToDate(ban, ano, mes, dia, hora, minuto, segundo);
            
                format(dialogBan, sizeof(dialogBan), "Você está banido permanentemente do servidor!\n\nResponsável pelo ban: %s\nData do banimento: %d/%d/%d - %d:%d:%d\nMotivo: %s", admin, dia, mes, ano, hora, minuto, segundo, motivo);
                Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "Ban", dialogBan, "Fechar", "");
                
                Kick(playerid);
            }
            else if(getdate() + gettime() < desban) {
                new bandate[3], bantime[3], desbandate[3], desbantime[3];

                TimestampToDate(ban, bandate[0],bandate[1],bandate[2], bantime[0],bantime[1],bantime[2], -3);
                TimestampToDate(desban, desbandate[0],desbandate[1],desbandate[2], desbantime[0],desbantime[1],desbantime[2], -3);

                format(dialogBan, sizeof(dialogBan), "Você está banido do servidor!\n\nResponsável pelo ban: %s\nData do banimento: %d/%d/%d - %d:%d:%d\nData do desbanimento: %d/%d/%d - %d:%d:%d\nMotivo: %s", admin, bandate[2], bandate[1], bandate[0], bantime[0], bantime[1], bantime[2], desbandate[2], desbandate[1], desbandate[0], desbantime[0], desbantime[1], desbantime[2], motivo);
                Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, "Ban", dialogBan, "Fechar", "");
                
                Kick(playerid);
                return 1;
            }
            else {
                MySQL_Update("DELETE FROM `banidos` WHERE `ban_id` = '%i'", idBan);
            }
        }
        else {
            CallLocalFunction("OnPlayerPassedBanCheck", "i", playerid);
        }					
    }

	new playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerName, sizeof(playerName));

    MySQL_TQueryInline(MySQL_Database(), using inline OnPlayerCheckBan, "SELECT * FROM `banidos` WHERE `username` = '%e'", playerName);
    return 1;
}

hook SetupLoginScreen(playerid) {
	CheckPlayerBan(playerid);

	return 1;
}

YCMD:ban(playerid, params[], help) {
    new userid, tempo, motivo[64];

    if (sscanf(params, "rds[64]", userid, tempo, motivo))
        return SendSyntaxMsg(playerid, "/Ban [id] [tempo] [motivo]");

	if (!IsPlayerConnected(userid))
		return SendErrorMsg(playerid, "Jogador(a) não conectado(a)");

    //if (GetPlayerAdminLevel(userid) > GetPlayerAdminLevel(playerid))
		//return SendErrorMsg(playerid, "Você não pode fazer nada contra um admin superior a você.");

	//if (GetPlayerAdminLevel(userid) == GetPlayerAdminLevel(playerid))
		//return SendErrorMsg(playerid, "Você não pode fazer nada contra um admin do mesmo nível.");

	// Preparar variaveis
    new playerip[16], serial[64], bantime, unbantime;
    
	GetPlayerIp(userid, playerip, sizeof(playerip));
    
	gpci(userid, serial, sizeof(serial));

	// Calcular tempo
    bantime = getdate() + gettime();
    
	if(tempo < 1) {
		unbantime = 0;
	}
	else {
		unbantime = bantime + (tempo*86400);
	}

	// Registrar e informar o ban
	new adminName[MAX_PLAYER_NAME], playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, adminName, sizeof(adminName));

	GetPlayerName(userid, playerName, sizeof(playerName));

    MySQL_Update("INSERT INTO `banidos` (username, ip, gpci, admin, ban, desban, motivo) VALUES (%d, '%e', '%e', '%e', %d, %d, '%e');", playerName, playerip, serial, adminName, bantime, unbantime, motivo);

    if(tempo < 1) {
		SendMsgAll(X11_RED2, "LSA-ADMIN: %a baniu %p permanentemente.", playerid, userid);
	}
	else {
		SendMsgAll(X11_RED2, "LSA-ADMIN: %a baniu %p por %i dias.", playerid, userid, tempo);
	}

	// Avisar
	SendMsg(userid, X11_RED, "~> Você foi banido(a) pelo motivo '%s'", motivo);
	SendMsg(userid, X11_RED, "~> Se você acha que foi banido injustamente, tire um print (F8) deste ban");
	SendMsg(userid, X11_RED, "~> Entre em nosso Discord e solicite seu desban no canal \"banimentos\"");
	SendMsg(userid, X11_RED, "~> Aguarde nossa administração analisar o caso.");

	// Kickar
    Kick(userid);
    return 1;
}

YCMD:desban(playerid, params[], help) {
    new playerBan[MAX_PLAYER_NAME];

    if(sscanf(params, "s[24]", playerBan))
        return SendSyntaxMsg(playerid, "/Desban [username]");

	inline const UnbanPlayer() {
		new rows, banId;
        
		cache_get_row_count(rows);

		if (!rows)
			return SendErrorMsg(playerid, "Jogador banido não encontrado.");
	
		cache_get_value_name_int(0, "BanID", banId);

		MySQL_Update("DELETE FROM `banidos` WHERE `ban_id` = '%d'", banId);

		SendMsgAll(X11_RED2, "LSA-ADMIN: %a desbaniu %s.", playerid, playerBan);
	}

	MySQL_TQueryInline(MySQL_Database(), using inline UnbanPlayer, "SELECT ban_id FROM banidos WHERE username = '%e'", playerBan);
	return 1;
}

YCMD:banip(playerid, params[], help) {
	new userid, motivo[30];

	if (sscanf(params, "rs[30]", userid, motivo))
		return SendSyntaxMsg(playerid, "/IPBan [id] [motivo]");
	
	if (!IsPlayerConnected(userid))
	    return SendErrorMsg(playerid, "Jogador(a) não conectado(a).");

	if(!(1 <= strlen(motivo) <= 30))
		return SendErrorMsg(playerid, "Motivo inválido.");

	// Mensagem
	SendMsgAll(X11_RED, "LSA-ADMIN: %a baniu %p", playerid, userid);
	
	ServerLog("ipban", "%p baniu o IP do(a) jogador(a) %p", playerid, userid);
	
	// Avisar
	SendMsg(userid, X11_RED, "~> Você foi banido(a) pelo motivo '%s'", motivo);
	SendMsg(userid, X11_RED, "~> Se você acha que foi banido injustamente, tire um print (F8) deste ban");
	SendMsg(userid, X11_RED, "~> Entre em nosso Discord e solicite seu desban no canal \"banimentos\"");
	SendMsg(userid, X11_RED, "~> Aguarde nossa administração analisar o caso.");
	
	// Banir
	BanPlayerEx(userid, motivo);
	return 1;
}

YCMD:desbanip(playerid, params[], help) {
	new pIP[17];

	if (sscanf(params, "s[17]", pIP))
		return SendSyntaxMsg(playerid, "/DesbanIP [ip]");
	
	SendAdminAction(playerid, "Você desbaniu o IP %s", pIP);

	new cmdRcon[50];
	format(cmdRcon, sizeof(cmdRcon), "unbanip %s", pIP);
	SendRconCommand(cmdRcon);

	SendRconCommand("reloadbans");
	return 1;
}
