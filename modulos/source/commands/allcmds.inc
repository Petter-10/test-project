
// módulo com os comandos do servidor

#include <YSI_Coding\y_hooks>

YCMD:avelinorj(playerid, params[], help) {
    SetPlayerSkin(playerid, 95);

    // Ativar o modo monstro
    SetPlayerHealth(playerid, INFINITY_HEALTH);

    SetPlayerArmour(playerid, INFINITY_HEALTH);

    // Lançar a braba
    GivePlayerWeapon(playerid, WEAPON_DEAGLE, 9999);

    // A mais classica
    new whiteNRG, Float:x, Float:y, Float:z;

    GetPlayerPos(playerid, x, y, z);

    whiteNRG = CreateVehicle(522, x, y, z, 0, 1, 1, 600, true);
    
    // Vrum vrumm
    PutPlayerInVehicle(playerid, whiteNRG, 0);
    return 1;
}

YCMD:dft(playerid, params[], help) {
    new Float:x, Float:y, Float:z;

    GetPlayerPos(playerid, x, y, z);

    SpawnVehicleJob(playerid, 578, x, y, z, 0, 6, 6, 0);
    return 1;
}
