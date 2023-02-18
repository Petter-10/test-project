
#include <login>

#include <YSI_Coding\y_hooks>

static g_PlayerUID[MAX_PLAYERS];
static g_PlayerDiscordID[MAX_PLAYERS][32];

static g_SecurityKey[MAX_PLAYERS];

public OnPlayerConnect(playerid) {
    // Verificar se � NPC
    if (IsPlayerNPC(playerid)) {
        // Carregar as informa��es de NPC
        CallLocalFunction("OnCustomNPCConnect", "d", playerid);

		//return Y_HOOKS_BREAK_RETURN_0();
    }
    else {
        // Carregar as informa��es de player
        CallLocalFunction("SetupLoginScreen", "d", playerid);
    }

    return 1;
}

public OnPlayerDisconnect(playerid, reason) {
	// NPC
	if (IsPlayerNPC(playerid)) {
		CallLocalFunction("OnCustomNPCDisconnect", "dd", playerid, reason);
	}
	else {
		if (!IsPlayerLogged(playerid)) 
			return 0;

		switch(reason) {
			case 0: Logger_Log("jogador caiu", Logger_P(playerid));
			case 2: Logger_Log("jogador kickado/banido", Logger_P(playerid));
		}

		// Resetar money
		ResetPlayerMoney(playerid);
	}
	return 1;
}

public OnPlayerRequestSpawn(playerid) {
	return 0;
}

public SetupLoginScreen(playerid) {
    // Mensagem de carregando
    SendClientMessage(playerid, -1, "Carregando dados, aguarde um momento.");
    
    SetPlayerColor(playerid, 0xEB3434FF);

    // Resetar
    g_PlayerUID[playerid] = 0;
    g_PlayerDiscordID[playerid][0] = EOS;

    g_SecurityKey[playerid] = 0;
    return 1;
}



// Dados da conta
hook OnLoadPlayerData(playerid) {
	// Carregar email
    inline const LoadEmail() {
		if (cache_num_rows()) {
			cache_get_value_name(0, "discord_id", g_PlayerDiscordID[playerid], 32);

			// Logar
			Logger_Dbg(PLAYER_DEBUG_HANDLER, "discord carregado", Logger_S("id", g_PlayerDiscordID[playerid]), Logger_P(playerid));
		}
    }

	MySQL_TQueryInline(MySQL_Database(), using inline LoadEmail, "SELECT discord_id FROM playerdata WHERE user_id = %i", GetAccountID(playerid));
    return 1;
}

ChangeNickname(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused listitem

		if (!response) return 1;

		if (!(3 <= strlen(inputtext) <= 20)) {
			SendErrorMsg(playerid, "Nickname inv�lido. use de 3 a 20 car�cteres");
			return ChangeNickname(playerid);
		}

		if (strfind(inputtext, "Frankie", true) != -1)
			return SendErrorMsg(playerid, "Este nick � de uso exclusivo no servidor.");

		// Verificar nicks proibidos
        if (CheckStringNickname(inputtext))
            return SendErrorMsg(playerid, "Este nick � proibido no servidor.");

		// Verificar se j� est� em uso
		inline const OnPlayerCheckUsername() {
			new rows;

			cache_get_row_count(rows);

            if(rows) {
                SendErrorMsg(playerid, "Nickname j� est� em uso");
                
				ChangeNickname(playerid);
            }
            else {
                SendMsg(playerid, Y_LIMEGREEN, "Nickname alterado para \"%s\"", inputtext);
                SendMsg(playerid, Y_LIMEGREEN, "N�o se esque�a de seu nick novo.");

                SendMsgAll(X11_YELLOW, "NICKNAME: %a mudou seu nick para %s", playerid, inputtext);

                PlayerLog(playerid, "[%s] %p mudou seu nickname para %s", FormatFullTime(), playerid, inputtext);

                /*
                GivePlayerCoins(playerid, -300);

				// Salvar casas
                foreach(new i : Houses) if(GetHouseOwnerID(i) == GetAccountID(playerid)) {
					UpdateHouseOwner(i, inputtext);
				}

				// Salvar empresas
                foreach(new i : Business) if(GetBusinessOwnerID(i) == GetAccountID(playerid)) {
                    UpdateBusinessOwner(i, inputtext);
                }

				// Salvar o veiculo
                foreach(new i : Vehicle) if(gVehicleData[i][OwnerID] == GetAccountID(playerid)) {
					StrCpy(gVehicleData[i][Owner], inputtext);
				}

				// Salvar aeroporto
				foreach(new i : Airports) if (GetAirportSQLID(i) == GetAccountID(playerid)) {
                    UpdateAirportOwner(i, inputtext);		
				}
                */

				// Setar o novo nick
                SetPlayerName(playerid, inputtext);
            }
		}

		MySQL_TQueryInline(MySQL_Database(), using inline OnPlayerCheckUsername, "SELECT * FROM `playerdata` WHERE `username` = '%e'", inputtext);
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, ""SPRING_GREEN"Mudan�a de Nick", "{FFFFFF}Insira o nick que voc� deseja ter para sua conta.\n\n"ORANGERED"OBS: {FFFFFF}N�o utilize ESPA�OS em seu novo nick", "Mudar", "Fechar");
	return 1;
}

/*
YCMD:mudarsenha(playerid, params[], help) {
	RequestSecurityKey(playerid);
	return 1;
}

RequestSecurityKey(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused listitem

		if(response) {
			if(!strcmp(inputtext, g_PlayerMail[playerid])) {
				// Gerar o pin
				g_SecurityKey[playerid] = gerarPIN();
			
				new infoEmail[128];
				format(infoEmail, sizeof(infoEmail), "Ol� %p voc� solicitou uma altera��o de senha. Aqui est� o c�digo: %d", playerid, g_SecurityKey[playerid]);
				
				// Enviar email
				SendMail(g_PlayerMail[playerid], "contato.lsarpg@gmail.com", "Life in San Andreas", "Mudan�a de Senha", infoEmail);
			
				ConfirmEmailCode(playerid);
			}
			else {
				SendErrorMsg(playerid, "Email inv�lido.");

				RequestSecurityKey(playerid);
			}
		}
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, ""SPRING_GREEN"Mudan�a de Senha", "{FFFFFF}Digite seu email cadastrado abaixo.", "Pr�xima", "Fechar");
	return 1;
}

static ConfirmEmailCode(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused listitem

		if(response) {
			if (g_SecurityKey[playerid] == strval(inputtext)) {
				ChangePassword(playerid);
			}
			else {
				SendErrorMsg(playerid, "C�digo incorreto.");

				ConfirmEmailCode(playerid);
			}
		}
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, ""SPRING_GREEN"Mudan�a de Senha", "{FFFFFF}Digite o c�digo que voc� recebeu em seu email:\n\n"ORANGERED"OBS: {FFFFFF}Verifique a Caixa de 'Spam'", "Pr�xima", "Fechar");
	return 1;	
}

ChangePassword(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused listitem

		if (response) {
			inline const PasswordHash(string:senha[]) {
				SendClientMessage(playerid, Y_LIMEGREEN, "Voc� mudou sua senha");

				Log_Write(playerid, "[%s] %p mudou sua senha", FormatFullTime(), playerid);

				// Salvar
				MySQL_Update("UPDATE playerdata SET senha = '%e' WHERE user_id = %i", senha, GetAccountID(playerid));
			}
			
			BCrypt_HashInline(inputtext, BCRYPT_COST, using inline PasswordHash);
		}
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_PASSWORD, ""SPRING_GREEN"Mudan�a de Senha", "{FFFFFF}Insira a nova senha que voc� deseja ter para sua conta.", "Mudar", "Fechar");
	return 1;
}
*/

// Fun��es
stock SetPlayerAccountID(playerid, uid) {
	return g_PlayerUID[playerid] = uid;
}

stock GetAccountID(playerid)
	return g_PlayerUID[playerid];

stock SetPlayerDiscordID(playerid, const discorid[]) {
	StrCpy(g_PlayerDiscordID[playerid], discorid);

	// Salvar
	MySQL_Update("UPDATE playerdata SET discord_id = '%e' WHERE user_id = %i", discorid, GetAccountID(playerid));
	return 1;
}

stock GetPlayerDiscordID(playerid, string[], len = sizeof(string)) {
	StrCpy(string, g_PlayerDiscordID[playerid], len);
	return 1;
}

stock SetPlayerLastLogin(playerid) {
	// Salvar
	MySQL_Update("UPDATE playerdata SET ultimo_login = %i WHERE user_id = %i", gettime(), GetAccountID(playerid));
	return 1;
}