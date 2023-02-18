
#include <YSI_Coding\y_hooks>

static bool:gJobStarted[MAX_PLAYERS] = {false, ...};

static gJobVehicle[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...};
static gJobTrailer[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...};

hook OnPlayerConnect(playerid) {
    gJobStarted[playerid] = false;

    gJobVehicle[playerid] = INVALID_VEHICLE_ID;
    gJobTrailer[playerid] = INVALID_VEHICLE_ID;
}

stock SetPlayerJob(playerid, bool:status) {
    gJobStarted[playerid] = status;

    // Pegar o id do veículo
    switch (status) {
        case true: {
            new vehicleid = GetPlayerVehicleID(playerid);

            if (vehicleid != INVALID_VEHICLE_ID) {
                gJobVehicle[playerid] = vehicleid;

                // Pegar o trailer do veículo
                if (GetVehicleTrailer(vehicleid) != INVALID_VEHICLE_ID) {
                    new trailerid = GetVehicleTrailer(vehicleid);

                    gJobTrailer[playerid] = trailerid;
                }
            }
        }
        case false: {
            gJobVehicle[playerid] = INVALID_VEHICLE_ID;
        }
    }
    return 1;
}

stock IsPlayerWorking(playerid)
    return gJobStarted[playerid];

// Extras dos veiculos
#include <vehicles-job>

// Trabalhos honestos
#include <trucker>