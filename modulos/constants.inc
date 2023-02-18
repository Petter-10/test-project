
#undef MAX_PLAYERS
	#define MAX_PLAYERS (33)

#undef MAX_VEHICLES
	#define MAX_VEHICLES (500)

#define MAX_NPCS	(3)

// Server
#define SERVER_NAME         "Unknow Project"
#define SERVER_VERSION      "1.0.0"
#define SERVER_DISCORD      "discord.gg/"
#define SERVER_PASS			"0"

#define INFINITY_HEALTH     (Float:0x7F800000)

// Configurações do YSI
#define YSI_NO_HEAP_MALLOC

// Logger
#define SERVER_DEBUG_HANDLER    "server"
#define MYSQL_DEBUG_HANDLER		"mysql"
#define PLAYER_DEBUG_HANDLER	"player"

// Arquivos
#define DIRECTORY_MAIN				"config/"

// Sexo
#define SEX_MAN			1 
#define SEX_WOMAN		2

// Spawns
#define LOS_SANTOS		1
#define	LAS_VENTURAS	2
#define SAN_FIERRO		3

// GPCI
#define MAX_GPCI_LEN            (41)

// Callbacks
forward SetupLoginScreen(playerid);
forward OnCustomNPCConnect(npcid);
forward OnCustomNPCDisconnect(npcid, reason);
forward OnPlayerPassedBanCheck(playerid);
forward OnPlayerAutoSave(playerid);

forward OnPlayerClickLogTextdraw(playerid, type);
forward OnPlayerClickRegTextdraw(playerid, type);