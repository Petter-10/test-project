
#include <YSI_Coding\y_hooks>

// Tela de login
static const g_MusicLinks[][] = {
   	"https://onedrive.live.com/download?resid=31C8109163997654!1766&authkey=!AFfglksmRLMZtK0&e=LMExot", // In My Mind
   	"https://onedrive.live.com/download?resid=31C8109163997654!1979&authkey=!AOm6qUk260CugY0&e=OjPK1Q", //Keep on Rising
   	"https://onedrive.live.com/download?resid=31C8109163997654!1980&authkey=!AAO9s-kLs1yPfYQ&e=TroJce", // Alone
   	"https://onedrive.live.com/redir?resid=31C8109163997654!1981&authkey=!ANRIE2GMbRA8ZoE&e=7ZTrr2", // Make Me Wanna
   	"https://onedrive.live.com/download?resid=31C8109163997654!1764&authkey=!AKs_UtHaLdN4uvQ&e=d3U9Rv" // Live in The Moment
};

// Tela de login
static g_LoginPassword[MAX_PLAYERS][20];
static g_LoginDiscordID[MAX_PLAYERS][30];
static g_LoginSex[MAX_PLAYERS] = {-1, ...};

static g_LoginAge[MAX_PLAYERS];
static g_LoginCity[MAX_PLAYERS];

// Player
static g_PlayerPassword[MAX_PLAYERS][BCRYPT_HASH_LENGTH];
static g_SecurityKey[MAX_PLAYERS];

static bool:p_Register[MAX_PLAYERS] = {false, ...};
static bool:p_Logged[MAX_PLAYERS] = {false, ...};

static Timer:g_LoginTimer[MAX_PLAYERS] = {Timer:0, ...};

// Timer
timer OnLoginTimeout[60 * 1000](playerid) {
    Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, ""FIREBRICK1"Servidor", "{FFFFFF}Você foi kickado por demorar para logar/registrar sua conta.", "Fechar");
    
	Kick(playerid);
}

// Passou da checagem
hook OnPlayerPassedBanCheck(playerid) {
	// Carregar dados
    inline const OnDataLoad() {
		if(cache_num_rows()) {
			new playerID, playerHash[BCRYPT_HASH_LENGTH];

           	cache_get_value_name_int(0, "user_id", playerID);
            cache_get_value_name(0, "senha", playerHash, sizeof(playerHash));

			// Setar o ID da conta
			SetPlayerAccountID(playerid, playerID);

			// Pegar senha para o login
			StrCpy(g_PlayerPassword[playerid], playerHash);
		}
		else {
			// Colocar para registro
			p_Register[playerid] = true;
		}
    }

    new playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, MAX_PLAYER_NAME);

	MySQL_TQueryInline(MySQL_Database(), using inline OnDataLoad, "SELECT user_id, senha FROM playerdata WHERE username = '%e'", playerName);

	// Preparar tela de login
    ClearChat(playerid, 30);

    // Paisagens
	inline const ShowScenes() {
        new idScene = random(6);

        switch(idScene) {
            case 0: {
                // Los Santos
                InterpolateCameraPos(playerid, 1694.385009, -138.035720, 80.092514, 1685.825073, -752.941772, 158.841125, 10000);
                InterpolateCameraLookAt(playerid, 1693.869506, -143.001937, 79.826232, 1684.775268, -757.826171, 158.640396, 10000);			
            }
            case 1: {
                // San Fierro
                InterpolateCameraPos(playerid, 48.842388, 2305.175048, 228.534332, -897.027832, 1553.355712, 208.681304, 10000);
                InterpolateCameraLookAt(playerid, 44.265930, 2304.596679, 226.605239, -901.192810, 1550.655029, 208.081619, 10000);
            }
            case 2: {
                //Las Venturas
                InterpolateCameraPos(playerid, 2009.298461, 550.470336, 83.938240, 2061.659667, 1105.632080, 51.940624, 10000);
                InterpolateCameraLookAt(playerid, 2004.343994, 550.172180, 83.334251, 2059.051513, 1101.798461, 50.069347, 10000);
            }
            case 3: {
                //Palomino Creek
                InterpolateCameraPos(playerid, 1695.689331, 201.997711, 77.365585, 2241.472656, -184.676818, 62.694328, 10000);
                InterpolateCameraLookAt(playerid, 1700.644653, 202.472167, 76.897521, 2245.691162, -181.998001, 62.526390, 10000);
            }
            case 4: {
                //Montgomery
                InterpolateCameraPos(playerid, 1225.485229, 542.256958, 79.074844, 1113.297485, 138.919555, 71.657424, 10000);
                InterpolateCameraLookAt(playerid, 1230.477172, 542.433227, 78.852264, 1113.425537, 133.922302, 71.762886, 10000);
            }
            case 5: {
                //Fort Carson
                InterpolateCameraPos(playerid, 151.323852, 853.945617, 60.021907, 444.651367, 1082.788696, 60.617492, 10000);
                InterpolateCameraLookAt(playerid, 150.416595, 849.032165, 60.209362, 448.010070, 1086.482788, 60.886894, 10000);
            }
        }
	}

	Timer_CreateCallback(using inline ShowScenes, 500, 1);
    
    // Música
    new playMusic = random(sizeof(g_MusicLinks)); 
    PlayAudioStreamForPlayer(playerid, g_MusicLinks[playMusic]);

    ClearChat(playerid, 10);

    // Login
    g_LoginTimer[playerid] = defer OnLoginTimeout(playerid);

    ShowLoginText(playerid);

	// Mensagem
	SendClientMessage(playerid, 0xFF0055FF, "conectado");
	return 1;
}

// Funções dos textdraws
static PasswordLogin(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused listitem

		if (!response) return 1;

		if (strfind(inputtext, "%", true) != -1)
			return PasswordLogin(playerid);

		if (!(4 <= strlen(inputtext) <= 20)) {
			SendErrorMsg(playerid, "Senha muito curta.");
			return PasswordLogin(playerid);
		}

		if (GetPVarInt(playerid, "spammarlogin") > gettime())
			return 0;

		if (!(4 <= strlen(inputtext[playerid]) <= 20))
			return SendErrorMsg(playerid, "Digite sua senha válida.");

		if (p_Register[playerid]) {
			StopLoginTimer(playerid);

			HideLoginMenu(playerid);

			ShowRegisterMenu(playerid);
		}
		else {
			inline const CheckPassword(bool:success) {
				if(success) {
					// Cancelar mouse
					CancelSelectTextDraw(playerid);

					// Carregar itens
					CallLocalFunction("OnLoadPlayerData", "i", playerid);

					SetupLogin(playerid);
				}
				else {
					SetPVarInt(playerid, "TentativasLogin", GetPVarInt(playerid, "TentativasLogin") + 1);

					if (GetPVarInt(playerid, "TentativasLogin") == 5) {
						SendClientMessage(playerid, X11_ORANGERED2, "** Você falhou ao fazer login, por isso foi kickado.");
						
						Logger_Log("player kickado por tentativas de login", Logger_P(playerid), Logger_I("tentativas", GetPVarInt(playerid, "TentativasLogin")));
						
						// Kickar
						Kick(playerid);
					} 
					else  {
						new string[50];

						format(string, sizeof(string), "Senha_incorreta_tentativas_restantes:_~r~%d", (5-GetPVarInt(playerid, "TentativasLogin")));
						ShowErrorTextdraw(playerid, string);
					}
				}
			}

			BCrypt_CheckInline(inputtext, g_PlayerPassword[playerid], using inline CheckPassword);

			// Evitar spamm
			SetPVarInt(playerid, "spammarlogin", gettime() + 5);
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_PASSWORD, ""ORANGERED"Senha", "{FFFFFF}Insira sua senha.", "Continuar", "Sair");
	return 1;
}

// Restantes das callbacks
public OnPlayerClickLogTextdraw(playerid, type) {
	switch (type) {
		case 1: {
			PasswordLogin(playerid);
		}
		case 2: {
			if (p_Register[playerid])
				return SendErrorMsg(playerid, "Sua conta não existe.");
			
			RecoveryPassword(playerid);
		}
	}

	return 1;
}

hook OnPlayerClickRegTextdraw(playerid, type) {
	switch(type) {
		case 1: ShowPlayerGender(playerid);
		case 2: InsertDiscordID(playerid);
		case 3: ShowPlayerCity(playerid);
		case 4: ShowPlayerAge(playerid);

		case 5: {
			if (!(4 <= strlen(g_LoginDiscordID[playerid]) <= 60))
				return SendErrorMsg(playerid, "Digite seu email.");

			if (g_LoginSex[playerid] == -1)
				return SendErrorMsg(playerid, "Selecione seu sexo.");

			// Fazer o hash da senha
			inline const PasswordHash(string:senha[]) {
				// Registrar jogador
				inline OnPlayerRegister() {
					SetPlayerAccountID(playerid, cache_insert_id());

					// Registrar
					new serial[MAX_GPCI_LEN];
					gpci(playerid, serial, MAX_GPCI_LEN);

					Logger_Log("player registrado", Logger_I("id", cache_insert_id()), Logger_P(playerid), Logger_S("gpci", serial), Logger_S("sex", (g_LoginSex[playerid] == SEX_MAN ? "masculino" : "feminino")));

					ClearChat(playerid, 30);

					SendMsg(playerid, X11_DODGER_BLUE, "LSA: {FFFFFF}Seja %s "LIMEGREEN"%p {FFFFFF}fique a vontade para curtir nosso servidor", (g_LoginSex[playerid] == SEX_MAN ? "bem vindo" : "bem vinda"), playerid);
					SendMsg(playerid, X11_DODGER_BLUE, "LSA: {FFFFFF}Siga o tutorial em sua tela para obter recompensas.");
					SendMsg(playerid, X11_DODGER_BLUE, "LSA: {FFFFFF}Obrigado por jogar, é um prazer tê-lo conosco.");

					GameTextForPlayerEx(playerid, "~w~%s", 5000, 4, (g_LoginSex[playerid] == SEX_MAN ? "bem vindo" : "bem vinda"));

					// Setar as variaveis
					CallLocalFunction("OnPlayerRegister", "i", playerid);

					// Retomar
					StopAudioStreamForPlayer(playerid);
					
					HideRegisterMenu(playerid);

					p_Register[playerid] = false;

					// Dar VIP gratuito
					GiveFreeVIP(playerid);

					// Spawnar
					p_Logged[playerid] = true;

					Player_SetStatus(playerid);
					Player_SetAFK(playerid);
					
					Player_ShowHud(playerid);
					Player_ShowBars(playerid);

					Dialog_Hide(playerid);

					// Spawn
					SpawnPlayer(playerid);
				}

				new username[MAX_PLAYER_NAME];
				GetPlayerName(playerid, username, sizeof(username));

				MySQL_TQueryInline(MySQL_Database(), using inline OnPlayerRegister, "INSERT INTO playerdata (username, senha) VALUES ('%e', '%e')", username, senha);
			}
			
			BCrypt_HashInline(g_LoginPassword[playerid], BCRYPT_COST, using inline PasswordHash);
		}
	}

	return 1;
}

static RecoveryPassword(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused listitem

		if (!response) return 1;

		new inputEmail[50];

		if(sscanf(inputtext, "s[50]", inputEmail)) {
			SendErrorMsg(playerid, "Digite um email válido.");
			return RecoveryPassword(playerid);
		}

		if(!IsValidEmail(inputEmail)) {
			SendErrorMsg(playerid, "Email inválido.");
			return RecoveryPassword(playerid);
		}

		new playerMail[31];

		GetPlayerEmail(playerid, playerMail, sizeof(playerMail));

		if(!strcmp(inputEmail, playerMail)) {
			// Gerar pin
			g_SecurityKey[playerid] = gerarPIN();

			new infoEmail[128];

			format(infoEmail, sizeof(infoEmail), "Olá %p você esqueceu a senha de sua conta. Use este código para login: %d", playerid, g_SecurityKey[playerid]);
			SendMail(playerMail, "contato.lsarpg@gmail.com", "Life in San Andreas", "Recuperar Conta", infoEmail);
		
			ConfirmSecurityCode(playerid);

			StopLoginTimer(playerid);
		}
		else {
			SendErrorMsg(playerid, "O email inserido não condiz com o de sua conta.");
			RecoveryPassword(playerid);
		}
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, ""ORANGERED"Esqueci minha senha", "{FFFFFF}Insira o endereço de e-mail que está registrado em sua conta.", "Continuar", "Sair");
	return 1;
}

static ConfirmSecurityCode(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused listitem

		if(response) {
			if (g_SecurityKey[playerid] == strval(inputtext)) {
				CallLocalFunction("OnLoadPlayerData", "i", playerid);

				SetupLogin(playerid);
			}
			else {
				SendErrorMsg(playerid, "Código inválido.");

				ConfirmSecurityCode(playerid);
			}
		}
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, ""ORANGERED"Esqueci minha senha", "{FFFFFF}Insira o endereço de e-mail que está registrado em sua conta.", "Continuar", "Sair");
	return 1;
}

static ShowPlayerCity(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused inputtext

		if (!response) return 1;

		switch(listitem) {
			case 0: g_LoginCity[playerid] = LOS_SANTOS;
			case 1: g_LoginSex[playerid] = LAS_VENTURAS;
			case 2: g_LoginSex[playerid] = SAN_FIERRO;
		}

		// Atualizar textdraw
		SyncPlayerTextdraw(playerid, 4);
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_LIST, ""ORANGERED"Pronome", "{FFFFFF}Ele\nEla", "Continuar", "Sair");
	return 1;
}

static ShowPlayerGender(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused inputtext

		if (!response) return 1;

		switch(listitem) {
			case 0: {
				g_LoginSex[playerid] = SEX_MAN;
			}
			case 1: {
				g_LoginSex[playerid] = SEX_WOMAN;
			}
		}

		// Atualizar textdraw
		SyncPlayerTextdraw(playerid, 1);
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_LIST, ""ORANGERED"Pronome", "{FFFFFF}Ele\nEla", "Continuar", "Sair");
	return 1;
}

static InsertDiscordID(playerid) {
	inline _response(response, listitem, string:inputtext[]) {
		#pragma unused listitem

		if (!response) return 1;

		new inputDiscord[34];

		if(!strlen(inputtext) || strlen(inputtext) > 32) {
			SendErrorMsg(playerid, "Quantia de carácteres inválidos.");
			return InsertDiscordID(playerid);
		}

		if(sscanf(inputtext, "s[34]", inputDiscord)) {
			SendErrorMsg(playerid, "Digite um email válido.");
			return InsertDiscordID(playerid);
		}

		// Verificar se ja existe
		inline const OnPlayerCheckDiscordID() {
			new rows;

			cache_get_row_count(rows);

			if(rows) {
				SendErrorMsg(playerid, "O ID já está em uso.");

				InsertDiscordID(playerid);
			}
			else {
				Register_EmailUpdate(playerid, inputDiscord);

				// update
				StrCpy(g_LoginDiscordID[playerid], inputDiscord);
			
				SyncPlayerTextdraw(playerid, 2);
			}
		}

		MySQL_TQueryInline(MySQL_Database(), using inline OnPlayerCheckDiscordID, "SELECT * FROM `playerdata` WHERE `discord_id` = '%e'", inputDiscord);
	}

	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, ""ORANGERED"Discord ID", "{FFFFFF}Digite um ID discord válido:", "Continuar", "Fechar");
	return 1;
}

hook OnPlayerConnect(playerid, reason) {
	p_Register[playerid] = false;
	p_Logged[playerid] = false;

	g_LoginPassword[playerid][0] = EOS;
	g_LoginDiscordID[playerid][0] = EOS;
	g_LoginSex[playerid] = -1;

	g_LoginAge[playerid] = 0;
	g_LoginCity[playerid] = 0;

	g_PlayerPassword[playerid][0] = EOS;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
	p_Logged[playerid] = false;

    if (!p_Logged[playerid]) {
        StopLoginTimer(playerid);
    }

	return 1;
}

SetupLogin(playerid) {
	// Serial
	new serial[MAX_GPCI_LEN];
	gpci(playerid, serial, MAX_GPCI_LEN);

	Logger_Log("player logado", Logger_P(playerid), Logger_S("gpci", serial));

	StopLoginTimer(playerid);

	ClearChat(playerid, 30);

	StopAudioStreamForPlayer(playerid);

	HideLoginMenu(playerid);

	// Último login
	SetPlayerLastLogin(playerid);

	// Mensagens
	SendMsg(playerid, X11_CORNFLOWERBLUE, "~> {FFFFFF}Login efetuado com sucesso, bem vindo(a) "CHARTREUSE"%p", playerid);

	p_Logged[playerid] = true;

	// Dar VIP gratuito
	GiveFreeVIP(playerid);

	Player_SetStatus(playerid);
	Player_SetAFK(playerid);

	Player_ShowHud(playerid);

	Dialog_Hide(playerid);

	SpawnPlayer(playerid);
}

stock Player_IsRegister(playerid)
	return p_Register[playerid];

stock IsPlayerLogged(playerid)
	return p_Logged[playerid];

stock GetPlayerLoginSex(playerid)
	return g_LoginSex[playerid];

stock GetPlayerLoginDiscordID(playerid)
	return g_LoginDiscordID[playerid];

stock GetPlayerLoginAge(playerid)
	return g_LoginAge[playerid];

stock GetPlayerLoginCity(playerid)
	return g_LoginCity[playerid];

stock StopLoginTimer(playerid) {
    stop g_LoginTimer[playerid];

    g_LoginTimer[playerid] = Timer:0;
}
