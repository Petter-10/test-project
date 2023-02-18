
#include <YSI_Coding\y_hooks>

static Iterator:gVehiclesJob<MAX_VEHICLES>;

// Preparar
enum E_VEHICLE_JOB {
    gVehicleID,
    
    gModelID,

    Float:vehicleX,
    Float:vehicleY,
    Float:vehicleZ,
    Float:vehicleA,

    gColor1,
    gColor2,

    gPlayerID,

    gJobID
};

static gVehicleData[MAX_VEHICLES][E_VEHICLE_JOB];

stock SpawnVehicleJob(playerid, modelid, Float:x, Float:y, Float:z, Float:a, color1, color2, jobid) {
    new id = Iter_Free(gVehiclesJob);

    // Setar os dados
    gVehicleData[id][gModelID] = modelid;

    gVehicleData[id][vehicleX] = x;
    gVehicleData[id][vehicleY] = y;
    gVehicleData[id][vehicleZ] = z;
    gVehicleData[id][vehicleA] = a;

    gVehicleData[id][gColor1] = color1;
    gVehicleData[id][gColor2] = color2;

    gVehicleData[id][gPlayerID] = playerid;
    gVehicleData[id][gJobID] = jobid;

    // Criar o veículo
    gVehicleData[id][gVehicleID] = CreateVehicle(modelid, x, y, z, a, color1, color2, 600, false); 

    ChangeVehicleColor(gVehicleData[id][gVehicleID], color1, color2);
 
    // Adicionar a lista
    Iter_Add(gVehiclesJob, id);
    return 1;
}

stock DeleteVehicleJob(playerid) {
    foreach(new i : gVehiclesJob) {
        if (gVehicleData[i][gPlayerID] == playerid) {
            // Excluir veículo
            
            // Setar os dados
            gVehicleData[i][gModelID] = 0;

            gVehicleData[i][vehicleX] = 0.0;
            gVehicleData[i][vehicleY] = 0.0;
            gVehicleData[i][vehicleZ] = 0.0;
            gVehicleData[i][vehicleA] = 0.0;

            gVehicleData[i][gColor1] = 0;
            gVehicleData[i][gColor2] = 0;

            gVehicleData[i][gPlayerID] = INVALID_VEHICLE_ID;
            gVehicleData[i][gJobID] = -1;

            // Verificar se tem jogador dentro
            foreach(new p : Player) {
                if (IsPlayerInVehicle(playerid, gVehicleData[i][gVehicleID])) {
                    RemovePlayerFromVehicle(p);
                }
            }

            // Destruir o veículo
            DestroyVehicle(gVehicleData[i][gVehicleID]);

            gVehicleData[i][gVehicleID] = INVALID_VEHICLE_ID;

            // Adicionar a lista
            Iter_Remove(gVehiclesJob, i);
        }
    }

    return 1;
}

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger) {
    // Checar se é passageiro
    if (!ispassenger) {
        // Verificar se é um veiculo de profissao
        foreach(new i : gVehiclesJob) {
            if (vehicleid == gVehicleData[i][gVehicleID]) {
                // Verificar se é do player
                if (gVehicleData[vehicleid][gPlayerID] != playerid) {
                    SendErrorMsg(playerid, "Esse veiculo não é seu.");

                    ClearAnimations(playerid);
                }
                else {
                    SendMsg(playerid, -1, "Bem vindo ao seu veiculo de trabalho.");
                }
            }
        }
    }

    return 1;
}

hook OnVehicleDeath(vehicleid, killerid) {
    foreach(new i : gVehiclesJob) {
        if (vehicleid == gVehicleData[i][gVehicleID]) {
            new playerid = gVehicleData[vehicleid][gPlayerID];

            SendErrorMsg(playerid, "Seu veículo de trabalho foi destruido");

            // Excluir o veiculo ao destruir
            DeleteVehicleJob(playerid);  
        }
    }

    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) {
    // Excluir o veiculo ao morrer
    DeleteVehicleJob(playerid);   

    return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
    // Excluir o veiculo ao sair
    DeleteVehicleJob(playerid);

    return 1;
}