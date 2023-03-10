
// M?dulo principal do servidor
#include <constants> // defines e configura??es
#include <utils> // fun??es ?teis

#include <database> // SQL e dados
#include <stream> // objetos e mapa
#include <commands> // comandos
#include <timers> // timers
#include <interface> // hud
#include <admin> // administra??o
#include <account> // player
#include <player> // definicoes do player
#include <system> // sistemas do servidor
#include <jobs> //  trabalhos

#include <YSI_Coding\y_hooks>

hook OnScriptInit() {
	printf("\n----------------------------------");
	printf("\n\n");
	printf("%s by PetteR_", SERVER_NAME);
	printf("Versao: %s", SERVER_VERSION);
	printf("%s", SERVER_DISCORD);
	printf("\n\n");
	printf("----------------------------------\n");

	return 1;
}

public OnGameModeInit() {
	// Configurar o servidor
	SendRconCommand("hostname ? "SERVER_NAME"");
	SendRconCommand("gamemodetext "SERVER_VERSION"");
	SendRconCommand("weburl "SERVER_DISCORD"");
    SendRconCommand("password "SERVER_PASS"");

	SendRconCommand("language Portugu?s - Brasil");

    // Iniciar os dados
    //Database_Init();

	EnableStuntBonusForAll(false); // Desativar o b?nus por stunt
	UsePlayerPedAnims(); // Colocar os player caminhando igual CJ
	DisableInteriorEnterExits(); // Desativar interiores
    return 1;
}

public OnGameModeExit() {
    // Fechar os dados
    //Database_Close();
    return 1;
}