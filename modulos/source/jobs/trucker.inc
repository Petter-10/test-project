
// Profissão de caminhoneiro
#include <YSI_Coding\y_hooks>

// Definições
static gTruckerCP[MAX_PLAYERS] = {INVALID_STREAMER_ID, ...};
static gTruckerObject[MAX_VEHICLES] = {INVALID_STREAMER_ID, ...};

static gTruckerProcess[MAX_PLAYERS];
static Timer:gTruckerTimer[MAX_PLAYERS] = {Timer:0, ...};

// Deposito
static gDepositLS;
static gDepositLV;
static gDepositSF;

hook OnPlayerConnect(playerid) {
    gTruckerCP[playerid] = INVALID_STREAMER_ID;
    gTruckerProcess[playerid] = 0;

    return 1;
}

hook OnVehicleDeath(vehicleid, killerid) {
    // Destruir o objeto
    if (IsValidDynamicObject(gTruckerObject[vehicleid])) {
        DestroyDynamicObject(gTruckerObject[vehicleid]);

        gTruckerObject[vehicleid] = INVALID_OBJECT_ID;
    }

    return 1;
}

YCMD:carregar(playerid, params[], help) {
    new vehicleid = GetPlayerVehicleID(playerid);

    if (IsPlayerWorking(playerid))
        return SendErrorMsg(playerid, "Você já está trabalhando.");

    if (vehicleid == INVALID_VEHICLE_ID)
        return SendErrorMsg(playerid, "Você não está em um veículo.");

    if (GetVehicleModel(vehicleid) != 578)
        return SendErrorMsg(playerid, "Você não está em um DFT-30 para iniciar o trabalho");

    Trucker_Init(playerid);
    return 1;
}

stock Trucker_Init(playerid) {
    // Iniciar o trabalho
    SetPlayerJob(playerid, true);

    // Informar 
    SendMsg(playerid, -1, "Carregue mercadoria no porto de Los Santos e aguarde sua nota fiscal.");

    gTruckerCP[playerid] =  CreateDynamicRaceCP(2, 2260.22, -2436.00, 13.10, 0.0, 0.0, 0.0, 5, -1, -1, .playerid = playerid, .streamdistance = 5000);

    gTruckerProcess[playerid] = 1;
    return 1;
}

stock Trucker_Finish(playerid) {
    // Cancelar o trabalho
    SetPlayerJob(playerid, false);

    gTruckerProcess[playerid] = 0;

    if (IsValidDynamicRaceCP(gTruckerCP[playerid])) {
        DestroyDynamicRaceCP(gTruckerCP[playerid]);

        gTruckerCP[playerid] = INVALID_STREAMER_ID;
    }

    if (Timer_IsRunning(gTruckerTimer[playerid])) {
        stop gTruckerTimer[playerid];

        gTruckerTimer[playerid] = Timer:0;
    }

    // Deletar objeto
    new vehicleid = GetPlayerVehicleID(playerid);

    if (IsValidDynamicObject(gTruckerObject[vehicleid])) {
        DestroyDynamicObject(gTruckerObject[vehicleid]);

        gTruckerObject[vehicleid] = INVALID_OBJECT_ID;
    }
    return 1;
}

static timer LoadUnload_Truck[5000](playerid) {
    new idProgress = gTruckerProcess[playerid];

    switch(idProgress) {
        case 1: {
            DestroyDynamicRaceCP(gTruckerCP[playerid]);

            gTruckerCP[playerid] = INVALID_STREAMER_ID;
            
            // Anexar o objeto ao veículo
            new vehicleid = GetPlayerVehicleID(playerid);
            
            gTruckerObject[vehicleid] = CreateDynamicObject(2935, 0, 0, -1000, 0, 0, 0, 100);
            AttachDynamicObjectToVehicle(gTruckerObject[vehicleid], vehicleid, 0.00, -1.65, 1.20, 0.00, 0.00, 0.00);

            // Informar localidade de entrega
            new string[120], string2[120], weightCargo, nfeNumber;
            
            weightCargo = min(20, 45);
            nfeNumber = random(10000);

            // Formatar o dialog
            format(string, sizeof(string), "O veículo foi carregado com mercadorias, pesando o total de %i ton.\n", weightCargo);
            format(string, sizeof(string), "%sLeve a mercadoria até o depósito de Los Santos.\n\n", string);
            format(string, sizeof(string), "%sSeu veículo %s sobrecarregado.", string, (weightCargo > 40 ? "está" : "não está"));

            // Formatar o cabeçalho
            format(string2, sizeof(string2), "Nota Fiscal - #%i", nfeNumber);

            Dialog_Show(playerid, DIALOG_STYLE_MSGBOX, string2, string, "Fechar");

            // Setar o próximo passo
            gTruckerProcess[playerid] = 2;

            // Criar novo checkpoint
            gTruckerCP[playerid] =  CreateDynamicRaceCP(1, 1067.89, -883.89, 43.17, 0.0, 0.0, 0.0, 5, -1, -1, .playerid = playerid, .streamdistance = 5000);
        }
        case 2: {
            SendMsg(playerid, -1, "Você entregou as mercadorias e ganhou 500");

            Trucker_Finish(playerid);
        }
    }
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid) {
    if (IsPlayerWorking(playerid) && checkpointid == gTruckerCP[playerid]) {
        // Executar o timer
        gTruckerTimer[playerid] = defer LoadUnload_Truck(playerid);

        new idProgress = gTruckerProcess[playerid];

        switch(idProgress) {
            case 1: GameTextForPlayer(playerid, "~w~Carregando ~r~~h~aguarde...", 4000, 4);
            case 2: GameTextForPlayer(playerid, "~w~Efetuando descarga ~r~~h~aguarde...", 4000, 4);
        }

        // Ocultar checkpoint
        TogglePlayerDynamicRaceCP(playerid, checkpointid, 0);
    }

    return 1;
}

// Carregar o deposito
forward ServerConfig_deposito(name[], value[]);
public ServerConfig_deposito(name[], value[]) {
    INI_Int("ls", gDepositLS);
    INI_Int("lv", gDepositLV);
    INI_Int("sf", gDepositSF);

    return 1;
}

stock ServerSave_deposito() {
    new INI:confFile = INI_Open(SETTINGS_FILE);

    // Deposito de encomendas
    INI_SetTag(confFile, "deposito");

    INI_WriteInt(confFile, "ls", gDepositLS);
    INI_WriteInt(confFile, "lv", gDepositLV);
    INI_WriteInt(confFile, "sf", gDepositSF);

    INI_Close(confFile);
    return 1;
}