
#include <YSI_Coding\y_hooks>

// Definicoes
static Text:gLoginTextdraws[22];
static Text:g_LoginError[3];

static PlayerText:gLoginPlayerTextdraws[MAX_PLAYERS][11];
static PlayerText:gRegisterButton[MAX_PLAYERS];
static PlayerText:gErrorTextdraw[MAX_PLAYERS];

static bool:gLoginShow[MAX_PLAYERS] = {false, ...};
static bool:gRegisterShow[MAX_PLAYERS] = {false, ...};

hook OnGameModeInit() {
    gLoginTextdraws[0] = TextDrawCreate(44.000000, 131.000000, "_");
    TextDrawFont(gLoginTextdraws[0], 1);
    TextDrawLetterSize(gLoginTextdraws[0], -1.124999, 21.049999);
    TextDrawTextSize(gLoginTextdraws[0], 235.500000, 15.000000);
    TextDrawSetOutline(gLoginTextdraws[0], 1);
    TextDrawSetShadow(gLoginTextdraws[0], 0);
    TextDrawAlignment(gLoginTextdraws[0], 1);
    TextDrawColor(gLoginTextdraws[0], -1);
    TextDrawBackgroundColor(gLoginTextdraws[0], 255);
    TextDrawBoxColor(gLoginTextdraws[0], 200);
    TextDrawUseBox(gLoginTextdraws[0], 1);
    TextDrawSetProportional(gLoginTextdraws[0], 1);
    TextDrawSetSelectable(gLoginTextdraws[0], 0);

    gLoginTextdraws[1] = TextDrawCreate(452.000000, 130.000000, "_");
    TextDrawFont(gLoginTextdraws[1], 1);
    TextDrawLetterSize(gLoginTextdraws[1], -1.124999, 9.099998);
    TextDrawTextSize(gLoginTextdraws[1], 262.000000, 8.500000);
    TextDrawSetOutline(gLoginTextdraws[1], 1);
    TextDrawSetShadow(gLoginTextdraws[1], 0);
    TextDrawAlignment(gLoginTextdraws[1], 1);
    TextDrawColor(gLoginTextdraws[1], -1);
    TextDrawBackgroundColor(gLoginTextdraws[1], 255);
    TextDrawBoxColor(gLoginTextdraws[1], 200);
    TextDrawUseBox(gLoginTextdraws[1], 1);
    TextDrawSetProportional(gLoginTextdraws[1], 1);
    TextDrawSetSelectable(gLoginTextdraws[1], 0);

    gLoginTextdraws[2] = TextDrawCreate(143.000000, 158.000000, "A_Nossa_equipe_agradece_sua_presenca. Obrigado_por_jogar_consco,_ter_voce_aqui_e_um_privilegio!");
    TextDrawFont(gLoginTextdraws[2], 2);
    TextDrawLetterSize(gLoginTextdraws[2], 0.112498, 1.050001);
    TextDrawTextSize(gLoginTextdraws[2], 400.000000, 17.000000);
    TextDrawSetOutline(gLoginTextdraws[2], 1);
    TextDrawSetShadow(gLoginTextdraws[2], 0);
    TextDrawAlignment(gLoginTextdraws[2], 2);
    TextDrawColor(gLoginTextdraws[2], -1);
    TextDrawBackgroundColor(gLoginTextdraws[2], 255);
    TextDrawBoxColor(gLoginTextdraws[2], 50);
    TextDrawUseBox(gLoginTextdraws[2], 0);
    TextDrawSetProportional(gLoginTextdraws[2], 1);
    TextDrawSetSelectable(gLoginTextdraws[2], 0);

    gLoginTextdraws[3] = TextDrawCreate(143.000000, 180.000000, "Caso_necessite_de_ajuda_procure_nossa_equipe_de_staff. Entre_em_nosso_Discord,_sua_participacao_e_feedback_sao_essenciais!");
    TextDrawFont(gLoginTextdraws[3], 2);
    TextDrawLetterSize(gLoginTextdraws[3], 0.112498, 1.050001);
    TextDrawTextSize(gLoginTextdraws[3], 400.000000, 17.000000);
    TextDrawSetOutline(gLoginTextdraws[3], 1);
    TextDrawSetShadow(gLoginTextdraws[3], 0);
    TextDrawAlignment(gLoginTextdraws[3], 2);
    TextDrawColor(gLoginTextdraws[3], -1);
    TextDrawBackgroundColor(gLoginTextdraws[3], 255);
    TextDrawBoxColor(gLoginTextdraws[3], 50);
    TextDrawUseBox(gLoginTextdraws[3], 0);
    TextDrawSetProportional(gLoginTextdraws[3], 1);
    TextDrawSetSelectable(gLoginTextdraws[3], 0);

    gLoginTextdraws[4] = TextDrawCreate(44.000000, 131.000000, "_");
    TextDrawFont(gLoginTextdraws[4], 1);
    TextDrawLetterSize(gLoginTextdraws[4], -1.124999, 21.049999);
    TextDrawTextSize(gLoginTextdraws[4], 40.000000, 9.000000);
    TextDrawSetOutline(gLoginTextdraws[4], 1);
    TextDrawSetShadow(gLoginTextdraws[4], 0);
    TextDrawAlignment(gLoginTextdraws[4], 1);
    TextDrawColor(gLoginTextdraws[4], -1);
    TextDrawBackgroundColor(gLoginTextdraws[4], 255);
    TextDrawBoxColor(gLoginTextdraws[4], 16711880);
    TextDrawUseBox(gLoginTextdraws[4], 1);
    TextDrawSetProportional(gLoginTextdraws[4], 1);
    TextDrawSetSelectable(gLoginTextdraws[4], 0);

    gLoginTextdraws[5] = TextDrawCreate(448.000000, 131.000000, "_");
    TextDrawFont(gLoginTextdraws[5], 1);
    TextDrawLetterSize(gLoginTextdraws[5], -1.124999, 9.000005);
    TextDrawTextSize(gLoginTextdraws[5], 445.500000, 7.000000);
    TextDrawSetOutline(gLoginTextdraws[5], 1);
    TextDrawSetShadow(gLoginTextdraws[5], 0);
    TextDrawAlignment(gLoginTextdraws[5], 1);
    TextDrawColor(gLoginTextdraws[5], -1);
    TextDrawBackgroundColor(gLoginTextdraws[5], 255);
    TextDrawBoxColor(gLoginTextdraws[5], 16711880);
    TextDrawUseBox(gLoginTextdraws[5], 1);
    TextDrawSetProportional(gLoginTextdraws[5], 1);
    TextDrawSetSelectable(gLoginTextdraws[5], 0);

    gLoginTextdraws[6] = TextDrawCreate(240.000000, 131.000000, "_");
    TextDrawFont(gLoginTextdraws[6], 1);
    TextDrawLetterSize(gLoginTextdraws[6], -1.124999, 21.049999);
    TextDrawTextSize(gLoginTextdraws[6], 236.000000, 9.000000);
    TextDrawSetOutline(gLoginTextdraws[6], 1);
    TextDrawSetShadow(gLoginTextdraws[6], 0);
    TextDrawAlignment(gLoginTextdraws[6], 1);
    TextDrawColor(gLoginTextdraws[6], -1);
    TextDrawBackgroundColor(gLoginTextdraws[6], 255);
    TextDrawBoxColor(gLoginTextdraws[6], 16711880);
    TextDrawUseBox(gLoginTextdraws[6], 1);
    TextDrawSetProportional(gLoginTextdraws[6], 1);
    TextDrawSetSelectable(gLoginTextdraws[6], 0);

    gLoginTextdraws[7] = TextDrawCreate(142.000000, 116.000000, "Projeto_sem_nome");
    TextDrawFont(gLoginTextdraws[7], 0);
    TextDrawLetterSize(gLoginTextdraws[7], 0.383332, 1.549998);
    TextDrawTextSize(gLoginTextdraws[7], 400.000000, 17.000000);
    TextDrawSetOutline(gLoginTextdraws[7], 1);
    TextDrawSetShadow(gLoginTextdraws[7], 0);
    TextDrawAlignment(gLoginTextdraws[7], 2);
    TextDrawColor(gLoginTextdraws[7], -1);
    TextDrawBackgroundColor(gLoginTextdraws[7], 255);
    TextDrawBoxColor(gLoginTextdraws[7], 50);
    TextDrawUseBox(gLoginTextdraws[7], 0);
    TextDrawSetProportional(gLoginTextdraws[7], 1);
    TextDrawSetSelectable(gLoginTextdraws[7], 0);

    gLoginTextdraws[8] = TextDrawCreate(100.000000, 300.000000, "Sua_diversao_e_nossa_alegria");
    TextDrawFont(gLoginTextdraws[8], 3);
    TextDrawLetterSize(gLoginTextdraws[8], 0.166666, 0.899999);
    TextDrawTextSize(gLoginTextdraws[8], 400.000000, 17.000000);
    TextDrawSetOutline(gLoginTextdraws[8], 1);
    TextDrawSetShadow(gLoginTextdraws[8], 0);
    TextDrawAlignment(gLoginTextdraws[8], 1);
    TextDrawColor(gLoginTextdraws[8], -1);
    TextDrawBackgroundColor(gLoginTextdraws[8], 255);
    TextDrawBoxColor(gLoginTextdraws[8], 50);
    TextDrawUseBox(gLoginTextdraws[8], 0);
    TextDrawSetProportional(gLoginTextdraws[8], 1);
    TextDrawSetSelectable(gLoginTextdraws[8], 0);

    gLoginTextdraws[9] = TextDrawCreate(302.000000, 139.000000, "Meus_dados");
    TextDrawFont(gLoginTextdraws[9], 0);
    TextDrawLetterSize(gLoginTextdraws[9], 0.316666, 1.450000);
    TextDrawTextSize(gLoginTextdraws[9], 400.000000, 17.000000);
    TextDrawSetOutline(gLoginTextdraws[9], 1);
    TextDrawSetShadow(gLoginTextdraws[9], 0);
    TextDrawAlignment(gLoginTextdraws[9], 2);
    TextDrawColor(gLoginTextdraws[9], -1);
    TextDrawBackgroundColor(gLoginTextdraws[9], 255);
    TextDrawBoxColor(gLoginTextdraws[9], 50);
    TextDrawUseBox(gLoginTextdraws[9], 0);
    TextDrawSetProportional(gLoginTextdraws[9], 1);
    TextDrawSetSelectable(gLoginTextdraws[9], 0);

    gLoginTextdraws[10] = TextDrawCreate(371.000000, 161.000000, "_");
    TextDrawFont(gLoginTextdraws[10], 1);
    TextDrawLetterSize(gLoginTextdraws[10], -1.124999, -0.500000);
    TextDrawTextSize(gLoginTextdraws[10], 275.500000, -11.000000);
    TextDrawSetOutline(gLoginTextdraws[10], 1);
    TextDrawSetShadow(gLoginTextdraws[10], 0);
    TextDrawAlignment(gLoginTextdraws[10], 1);
    TextDrawColor(gLoginTextdraws[10], -1);
    TextDrawBackgroundColor(gLoginTextdraws[10], 255);
    TextDrawBoxColor(gLoginTextdraws[10], 16711880);
    TextDrawUseBox(gLoginTextdraws[10], 1);
    TextDrawSetProportional(gLoginTextdraws[10], 1);
    TextDrawSetSelectable(gLoginTextdraws[10], 0);

    gLoginTextdraws[11] = TextDrawCreate(371.000000, 195.000000, "_");
    TextDrawFont(gLoginTextdraws[11], 1);
    TextDrawLetterSize(gLoginTextdraws[11], -1.124999, 0.599999);
    TextDrawTextSize(gLoginTextdraws[11], 275.500000, -11.000000);
    TextDrawSetOutline(gLoginTextdraws[11], 1);
    TextDrawSetShadow(gLoginTextdraws[11], 0);
    TextDrawAlignment(gLoginTextdraws[11], 1);
    TextDrawColor(gLoginTextdraws[11], -1);
    TextDrawBackgroundColor(gLoginTextdraws[11], 255);
    TextDrawBoxColor(gLoginTextdraws[11], -56);
    TextDrawUseBox(gLoginTextdraws[11], 1);
    TextDrawSetProportional(gLoginTextdraws[11], 1);
    TextDrawSetSelectable(gLoginTextdraws[11], 0);

    gLoginTextdraws[12] = TextDrawCreate(621.000000, 232.000000, "_");
    TextDrawFont(gLoginTextdraws[12], 1);
    TextDrawLetterSize(gLoginTextdraws[12], -0.404165, 14.600028);
    TextDrawTextSize(gLoginTextdraws[12], 612.500000, 9.000000);
    TextDrawSetOutline(gLoginTextdraws[12], 1);
    TextDrawSetShadow(gLoginTextdraws[12], 0);
    TextDrawAlignment(gLoginTextdraws[12], 1);
    TextDrawColor(gLoginTextdraws[12], -1);
    TextDrawBackgroundColor(gLoginTextdraws[12], 255);
    TextDrawBoxColor(gLoginTextdraws[12], 16711880);
    TextDrawUseBox(gLoginTextdraws[12], 1);
    TextDrawSetProportional(gLoginTextdraws[12], 1);
    TextDrawSetSelectable(gLoginTextdraws[12], 0);

    gLoginTextdraws[13] = TextDrawCreate(619.000000, 372.000000, "_");
    TextDrawFont(gLoginTextdraws[13], 1);
    TextDrawLetterSize(gLoginTextdraws[13], -1.124999, -16.550010);
    TextDrawTextSize(gLoginTextdraws[13], 261.500000, 76.000000);
    TextDrawSetOutline(gLoginTextdraws[13], 1);
    TextDrawSetShadow(gLoginTextdraws[13], 0);
    TextDrawAlignment(gLoginTextdraws[13], 1);
    TextDrawColor(gLoginTextdraws[13], -1);
    TextDrawBackgroundColor(gLoginTextdraws[13], 255);
    TextDrawBoxColor(gLoginTextdraws[13], 200);
    TextDrawUseBox(gLoginTextdraws[13], 1);
    TextDrawSetProportional(gLoginTextdraws[13], 1);
    TextDrawSetSelectable(gLoginTextdraws[13], 0);

    gLoginTextdraws[14] = TextDrawCreate(299.000000, 235.000000, "Discord-id");
    TextDrawFont(gLoginTextdraws[14], 0);
    TextDrawLetterSize(gLoginTextdraws[14], 0.316666, 1.450000);
    TextDrawTextSize(gLoginTextdraws[14], 400.000000, 17.000000);
    TextDrawSetOutline(gLoginTextdraws[14], 1);
    TextDrawSetShadow(gLoginTextdraws[14], 0);
    TextDrawAlignment(gLoginTextdraws[14], 2);
    TextDrawColor(gLoginTextdraws[14], -1);
    TextDrawBackgroundColor(gLoginTextdraws[14], 255);
    TextDrawBoxColor(gLoginTextdraws[14], 50);
    TextDrawUseBox(gLoginTextdraws[14], 0);
    TextDrawSetProportional(gLoginTextdraws[14], 1);
    TextDrawSetSelectable(gLoginTextdraws[14], 0);

    gLoginTextdraws[15] = TextDrawCreate(412.000000, 269.000000, "_");
    TextDrawFont(gLoginTextdraws[15], 1);
    TextDrawLetterSize(gLoginTextdraws[15], -1.124999, 0.599999);
    TextDrawTextSize(gLoginTextdraws[15], 277.000000, -11.000000);
    TextDrawSetOutline(gLoginTextdraws[15], 1);
    TextDrawSetShadow(gLoginTextdraws[15], 0);
    TextDrawAlignment(gLoginTextdraws[15], 1);
    TextDrawColor(gLoginTextdraws[15], -1);
    TextDrawBackgroundColor(gLoginTextdraws[15], 255);
    TextDrawBoxColor(gLoginTextdraws[15], -56);
    TextDrawUseBox(gLoginTextdraws[15], 1);
    TextDrawSetProportional(gLoginTextdraws[15], 1);
    TextDrawSetSelectable(gLoginTextdraws[15], 0);

    gLoginTextdraws[16] = TextDrawCreate(297.000000, 287.000000, "Pronome");
    TextDrawFont(gLoginTextdraws[16], 0);
    TextDrawLetterSize(gLoginTextdraws[16], 0.316666, 1.450000);
    TextDrawTextSize(gLoginTextdraws[16], 400.000000, 17.000000);
    TextDrawSetOutline(gLoginTextdraws[16], 1);
    TextDrawSetShadow(gLoginTextdraws[16], 0);
    TextDrawAlignment(gLoginTextdraws[16], 2);
    TextDrawColor(gLoginTextdraws[16], -1);
    TextDrawBackgroundColor(gLoginTextdraws[16], 255);
    TextDrawBoxColor(gLoginTextdraws[16], 50);
    TextDrawUseBox(gLoginTextdraws[16], 0);
    TextDrawSetProportional(gLoginTextdraws[16], 1);
    TextDrawSetSelectable(gLoginTextdraws[16], 0);

    gLoginTextdraws[17] = TextDrawCreate(411.000000, 323.000000, "_");
    TextDrawFont(gLoginTextdraws[17], 1);
    TextDrawLetterSize(gLoginTextdraws[17], -1.124999, 0.599999);
    TextDrawTextSize(gLoginTextdraws[17], 277.000000, -11.000000);
    TextDrawSetOutline(gLoginTextdraws[17], 1);
    TextDrawSetShadow(gLoginTextdraws[17], 0);
    TextDrawAlignment(gLoginTextdraws[17], 1);
    TextDrawColor(gLoginTextdraws[17], -1);
    TextDrawBackgroundColor(gLoginTextdraws[17], 255);
    TextDrawBoxColor(gLoginTextdraws[17], -56);
    TextDrawUseBox(gLoginTextdraws[17], 1);
    TextDrawSetProportional(gLoginTextdraws[17], 1);
    TextDrawSetSelectable(gLoginTextdraws[17], 0);

    gLoginTextdraws[18] = TextDrawCreate(460.000000, 235.000000, "Cidade");
    TextDrawFont(gLoginTextdraws[18], 0);
    TextDrawLetterSize(gLoginTextdraws[18], 0.316666, 1.450000);
    TextDrawTextSize(gLoginTextdraws[18], 400.000000, 17.000000);
    TextDrawSetOutline(gLoginTextdraws[18], 1);
    TextDrawSetShadow(gLoginTextdraws[18], 0);
    TextDrawAlignment(gLoginTextdraws[18], 2);
    TextDrawColor(gLoginTextdraws[18], -1);
    TextDrawBackgroundColor(gLoginTextdraws[18], 255);
    TextDrawBoxColor(gLoginTextdraws[18], 50);
    TextDrawUseBox(gLoginTextdraws[18], 0);
    TextDrawSetProportional(gLoginTextdraws[18], 1);
    TextDrawSetSelectable(gLoginTextdraws[18], 0);

    gLoginTextdraws[19] = TextDrawCreate(613.000000, 269.000000, "_");
    TextDrawFont(gLoginTextdraws[19], 1);
    TextDrawLetterSize(gLoginTextdraws[19], -1.124999, 0.599999);
    TextDrawTextSize(gLoginTextdraws[19], 445.000000, -11.000000);
    TextDrawSetOutline(gLoginTextdraws[19], 1);
    TextDrawSetShadow(gLoginTextdraws[19], 0);
    TextDrawAlignment(gLoginTextdraws[19], 1);
    TextDrawColor(gLoginTextdraws[19], -1);
    TextDrawBackgroundColor(gLoginTextdraws[19], 255);
    TextDrawBoxColor(gLoginTextdraws[19], -56);
    TextDrawUseBox(gLoginTextdraws[19], 1);
    TextDrawSetProportional(gLoginTextdraws[19], 1);
    TextDrawSetSelectable(gLoginTextdraws[19], 0);

    gLoginTextdraws[20] = TextDrawCreate(457.000000, 291.000000, "Idade");
    TextDrawFont(gLoginTextdraws[20], 0);
    TextDrawLetterSize(gLoginTextdraws[20], 0.316666, 1.450000);
    TextDrawTextSize(gLoginTextdraws[20], 400.000000, 17.000000);
    TextDrawSetOutline(gLoginTextdraws[20], 1);
    TextDrawSetShadow(gLoginTextdraws[20], 0);
    TextDrawAlignment(gLoginTextdraws[20], 2);
    TextDrawColor(gLoginTextdraws[20], -1);
    TextDrawBackgroundColor(gLoginTextdraws[20], 255);
    TextDrawBoxColor(gLoginTextdraws[20], 50);
    TextDrawUseBox(gLoginTextdraws[20], 0);
    TextDrawSetProportional(gLoginTextdraws[20], 1);
    TextDrawSetSelectable(gLoginTextdraws[20], 0);

    gLoginTextdraws[21] = TextDrawCreate(612.000000, 323.000000, "_");
    TextDrawFont(gLoginTextdraws[21], 1);
    TextDrawLetterSize(gLoginTextdraws[21], -1.124999, 0.599999);
    TextDrawTextSize(gLoginTextdraws[21], 445.000000, -11.000000);
    TextDrawSetOutline(gLoginTextdraws[21], 1);
    TextDrawSetShadow(gLoginTextdraws[21], 0);
    TextDrawAlignment(gLoginTextdraws[21], 1);
    TextDrawColor(gLoginTextdraws[21], -1);
    TextDrawBackgroundColor(gLoginTextdraws[21], 255);
    TextDrawBoxColor(gLoginTextdraws[21], -56);
    TextDrawUseBox(gLoginTextdraws[21], 1);
    TextDrawSetProportional(gLoginTextdraws[21], 1);
    TextDrawSetSelectable(gLoginTextdraws[21], 0);

    g_LoginError[0] = TextDrawCreate(621.000000, 130.000000, "_");
    TextDrawFont(g_LoginError[0], 1);
    TextDrawLetterSize(g_LoginError[0], -1.124999, 9.099998);
    TextDrawTextSize(g_LoginError[0], 458.500000, 8.500000);
    TextDrawSetOutline(g_LoginError[0], 1);
    TextDrawSetShadow(g_LoginError[0], 0);
    TextDrawAlignment(g_LoginError[0], 1);
    TextDrawColor(g_LoginError[0], -1);
    TextDrawBackgroundColor(g_LoginError[0], 255);
    TextDrawBoxColor(g_LoginError[0], 200);
    TextDrawUseBox(g_LoginError[0], 1);
    TextDrawSetProportional(g_LoginError[0], 1);
    TextDrawSetSelectable(g_LoginError[0], 0);

    g_LoginError[1] = TextDrawCreate(621.000000, 130.000000, "_");
    TextDrawFont(g_LoginError[1], 1);
    TextDrawLetterSize(g_LoginError[1], -0.404164, 9.100033);
    TextDrawTextSize(g_LoginError[1], 612.500000, 9.000000);
    TextDrawSetOutline(g_LoginError[1], 1);
    TextDrawSetShadow(g_LoginError[1], 0);
    TextDrawAlignment(g_LoginError[1], 1);
    TextDrawColor(g_LoginError[1], -1);
    TextDrawBackgroundColor(g_LoginError[1], 255);
    TextDrawBoxColor(g_LoginError[1], -16777016);
    TextDrawUseBox(g_LoginError[1], 1);
    TextDrawSetProportional(g_LoginError[1], 1);
    TextDrawSetSelectable(g_LoginError[1], 0);

    g_LoginError[2] = TextDrawCreate(479.000000, 135.000000, "Erro!");
    TextDrawFont(g_LoginError[2], 0);
    TextDrawLetterSize(g_LoginError[2], 0.316666, 1.450000);
    TextDrawTextSize(g_LoginError[2], 400.000000, 17.000000);
    TextDrawSetOutline(g_LoginError[2], 1);
    TextDrawSetShadow(g_LoginError[2], 0);
    TextDrawAlignment(g_LoginError[2], 2);
    TextDrawColor(g_LoginError[2], -1);
    TextDrawBackgroundColor(g_LoginError[2], 255);
    TextDrawBoxColor(g_LoginError[2], 50);
    TextDrawUseBox(g_LoginError[2], 0);
    TextDrawSetProportional(g_LoginError[2], 1);
    TextDrawSetSelectable(g_LoginError[2], 0);

    return 1;
}

hook OnPlayerConnect(playerid) {
    gLoginShow[playerid] = false;
    gRegisterShow[playerid] = false;

    gLoginPlayerTextdraws[playerid][0] = CreatePlayerTextDraw(playerid, 112.000000, 141.000000, "Bem_vindo,_Petter!");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][0], 0);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][0], 0.250000, 1.299998);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][0], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][0], 1);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][0], 0);

    gLoginPlayerTextdraws[playerid][1] = CreatePlayerTextDraw(playerid, 332.000000, 163.000000, "Digite_sua_senha_abaixo_para_efetuar_registro");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][1], 0.133331, 1.200000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][1], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][1], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][1], 0);

    gLoginPlayerTextdraws[playerid][2] = CreatePlayerTextDraw(playerid, 323.000000, 193.000000, "Clique_aqui");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][2], 3);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][2], 0.204164, 1.000000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][2], 20.000000, 43.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][2], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][2], 1);

    gLoginPlayerTextdraws[playerid][3] = CreatePlayerTextDraw(playerid, 340.000000, 267.000000, "Clique_aqui");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][3], 3);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][3], 0.204164, 1.000000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][3], 20.000000, 43.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][3], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][3], 1);

    gLoginPlayerTextdraws[playerid][4] = CreatePlayerTextDraw(playerid, 322.000000, 251.000000, "Certifique-se_de_inserir_o_ID_correto");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][4], 0.133331, 1.200000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][4], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][4], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][4], 0);

    gLoginPlayerTextdraws[playerid][5] = CreatePlayerTextDraw(playerid, 328.000000, 303.000000, "Selecione_como_gostaria_de_ser_chamado");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][5], 0.133331, 1.200000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][5], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][5], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][5], 0);

    gLoginPlayerTextdraws[playerid][6] = CreatePlayerTextDraw(playerid, 341.000000, 321.000000, "Clique_aqui");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][6], 3);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][6], 0.204164, 1.000000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][6], 20.000000, 43.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][6], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][6], 1);

    gLoginPlayerTextdraws[playerid][7] = CreatePlayerTextDraw(playerid, 484.000000, 251.000000, "Selecione_sua_cidade_de_origem");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][7], 0.133331, 1.200000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][7], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][7], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][7], 0);

    gLoginPlayerTextdraws[playerid][8] = CreatePlayerTextDraw(playerid, 523.000000, 267.000000, "Clique_aqui");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][8], 3);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][8], 0.204164, 1.000000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][8], 20.000000, 43.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][8], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][8], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][8], 1);

    gLoginPlayerTextdraws[playerid][9] = CreatePlayerTextDraw(playerid, 490.000000, 304.000000, "Selecione_a_idade_de_seu_personagem");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][9], 0.133331, 1.200000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][9], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][9], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][9], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][9], 0);

    gLoginPlayerTextdraws[playerid][10] = CreatePlayerTextDraw(playerid, 523.000000, 321.000000, "Clique_aqui");
    PlayerTextDrawFont(playerid, gLoginPlayerTextdraws[playerid][10], 3);
    PlayerTextDrawLetterSize(playerid, gLoginPlayerTextdraws[playerid][10], 0.204164, 1.000000);
    PlayerTextDrawTextSize(playerid, gLoginPlayerTextdraws[playerid][10], 20.000000, 43.000000);
    PlayerTextDrawSetOutline(playerid, gLoginPlayerTextdraws[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, gLoginPlayerTextdraws[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, gLoginPlayerTextdraws[playerid][10], 2);
    PlayerTextDrawColor(playerid, gLoginPlayerTextdraws[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, gLoginPlayerTextdraws[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, gLoginPlayerTextdraws[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, gLoginPlayerTextdraws[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, gLoginPlayerTextdraws[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, gLoginPlayerTextdraws[playerid][10], 1);

    gRegisterButton[playerid] = CreatePlayerTextDraw(playerid, 433.000000, 348.000000, "Continuar");
    PlayerTextDrawFont(playerid, gRegisterButton[playerid], 3);
    PlayerTextDrawLetterSize(playerid, gRegisterButton[playerid], 0.204163, 1.000000);
    PlayerTextDrawTextSize(playerid, gRegisterButton[playerid], 20.000000, 43.000000);
    PlayerTextDrawSetOutline(playerid, gRegisterButton[playerid], 1);
    PlayerTextDrawSetShadow(playerid, gRegisterButton[playerid], 0);
    PlayerTextDrawAlignment(playerid, gRegisterButton[playerid], 2);
    PlayerTextDrawColor(playerid, gRegisterButton[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, gRegisterButton[playerid], 255);
    PlayerTextDrawBoxColor(playerid, gRegisterButton[playerid], 50);
    PlayerTextDrawUseBox(playerid, gRegisterButton[playerid], 0);
    PlayerTextDrawSetProportional(playerid, gRegisterButton[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, gRegisterButton[playerid], 1);

    gErrorTextdraw[playerid] = CreatePlayerTextDraw(playerid, 469.000000, 157.000000, "Senha_invalida!");
    PlayerTextDrawFont(playerid, gErrorTextdraw[playerid], 1);
    PlayerTextDrawLetterSize(playerid, gErrorTextdraw[playerid], 0.133331, 1.200000);
    PlayerTextDrawTextSize(playerid, gErrorTextdraw[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, gErrorTextdraw[playerid], 1);
    PlayerTextDrawSetShadow(playerid, gErrorTextdraw[playerid], 0);
    PlayerTextDrawAlignment(playerid, gErrorTextdraw[playerid], 1);
    PlayerTextDrawColor(playerid, gErrorTextdraw[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, gErrorTextdraw[playerid], 255);
    PlayerTextDrawBoxColor(playerid, gErrorTextdraw[playerid], 50);
    PlayerTextDrawUseBox(playerid, gErrorTextdraw[playerid], 0);
    PlayerTextDrawSetProportional(playerid, gErrorTextdraw[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, gErrorTextdraw[playerid], 0);
    return 1;
}

ShowLoginText(playerid) {
    if (Player_IsRegister(playerid)) {

    }
    
    SelectTextDraw(playerid, 0x00FF00FF);

    // Pegar nome do player
    new playerName[MAX_PLAYER_NAME];

    GetPlayerName(playerid, playerName, sizeof(playerName));

	PlayerTextDrawUpdate(playerid, gLoginPlayerTextdraws[playerid][0], "Bem_vindo,_%s!", playerid);

    for(new i; i < sizeof gLoginTextdraws; i++)
        TextDrawShowForPlayer(playerid, gLoginTextdraws[i]);

    for(new i = 0; i < 11; i++)
        PlayerTextDrawShow(playerid, gLoginPlayerTextdraws[playerid][i]);

	gLoginShow[playerid] = true;
}

hook OnPlayerClickRegTextdraw(playerid, PlayerText:playertextid) {
    if (gLoginShow[playerid]) {
        if (playertextid == gLoginPlayerTextdraws[playerid][2]) {
            CallLocalFunction("OnPlayerClickLogTextdraw", "ii", playerid, 1);
        }
    }

    if (gRegisterShow[playerid]) {
        if (playertextid == gLoginPlayerTextdraws[playerid][6])
            CallLocalFunction("OnPlayerClickRegTextdraw", "ii", playerid, 1);

        if (playertextid == gLoginPlayerTextdraws[playerid][3])
            CallLocalFunction("OnPlayerClickRegTextdraw", "ii", playerid, 2);

        if (playertextid == gLoginPlayerTextdraws[playerid][8])
            CallLocalFunction("OnPlayerClickRegTextdraw", "ii", playerid, 3);

        if (playertextid == gLoginPlayerTextdraws[playerid][10])
            CallLocalFunction("OnPlayerClickRegTextdraw", "ii", playerid, 4);
    }
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if(_:clickedid == _:INVALID_TEXT_DRAW) {
		if (gLoginShow[playerid])
			SelectTextDraw(playerid, 0x00FF00FF);

		//if(RegisterShow[playerid])
			//ShowLoginText(playerid);
	}
    return 1;
}

stock SyncPlayerTextdraw(playerid, textdrawid) {
    switch(textdrawid) {
        case 0: {
        }
        case 1: {
            new sexid = GetPlayerLoginSex(playerid);

            switch(sexid) {
                case SEX_MAN: PlayerTextDrawSetString(playerid, gLoginPlayerTextdraws[playerid][6], "Ele");
                case SEX_WOMAN: PlayerTextDrawSetString(playerid, gLoginPlayerTextdraws[playerid][6], "Ela");
            }
        }

        case 2: PlayerTextDrawUpdate(playerid, gLoginPlayerTextdraws[playerid][3], "%s", GetPlayerLoginDiscordID(playerid));
        case 3: PlayerTextDrawUpdate(playerid, gLoginPlayerTextdraws[playerid][10], "%i", GetPlayerLoginAge(playerid));
       
        case 4: {
            new cityid = GetPlayerLoginCity(playerid);

            switch(cityid) {
                case LOS_SANTOS: PlayerTextDrawSetString(playerid, gLoginPlayerTextdraws[playerid][8], "Los_Santos");
                case LAS_VENTURAS: PlayerTextDrawSetString(playerid, gLoginPlayerTextdraws[playerid][8], "Las_Venturas");
                case SAN_FIERRO: PlayerTextDrawSetString(playerid, gLoginPlayerTextdraws[playerid][8], "San_Fierro");
            }          
        }
    }

    return 1;
}

stock ShowRegisterButton(playerid) {
    PlayerTextDrawShow(playerid, gRegisterButton[playerid]);

    return 1;
}

stock ShowErrorTextdraw(playerid, const string[]) {
    PlayerTextDrawUpdate(playerid, gErrorTextdraw[playerid], "%s", string);

    for(new i; i < sizeof g_LoginError; i++)
        TextDrawShowForPlayer(playerid, g_LoginError[i]);

    return 1;
}
