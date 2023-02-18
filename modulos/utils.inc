
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_va>

// Funções úteis

stock FormatFullTime() {
    new
        date[36];

    getdate(date[2], date[1], date[0]);
    gettime(date[3], date[4], date[5]);

    format(date, sizeof(date), "%02d/%02d/%d, %02d:%02d:%02d", date[0], date[1], date[2], date[3], date[4], date[5]);
    return date;
}

stock TimestampToDate(unix_timestamp, &year, &month, &day, &hour, &minute, &second, utc_hour = -2, utc_minute = 0)  { 
    static days_of_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, next_year, ut_of_next_year; 
    static const unix_timestamp_by_year[] = 
    { 
        -315619200, -283996800, -252460800, -220924800, -189388800, -157766400, -126230400, -94694400, -63158400, -31536000, 
        0, 31536000, 63072000, 94694400, 126230400, 157766400, 189302400, 220924800, 252460800, 283996800, 
        315532800, 347155200, 378691200, 410227200, 441763200, 473385600, 504921600, 536457600, 567993600, 599616000, 
        631152000, 662688000, 694224000, 725846400, 757382400, 788918400, 820454400, 852076800, 883612800, 915148800, 
        946684800, 978307200, 1009843200, 1041379200, 1072915200, 1104537600, 1136073600, 1167609600, 1199145600, 1230768000, 
        1262304000, 1293840000, 1325376000, 1356998400, 1388534400, 1420070400, 1451606400, 1483228800, 1514764800, 1546300800, 
        1577836800, 1609459200, 1640995200, 1672531200, 1704067200, 1735689600, 1767225600, 1798761600, 1830297600, 1861920000, 
        1893456000, 1924992000, 1956528000, 1988150400, 2019686400, 2051222400, 2082758400, 2114380800, 2145916800, -2117514496 
    }; 
     
    if (!(-315619200 <= (unix_timestamp += (utc_hour * 3600) + (utc_minute * 60)) <= cellmax)) return; 

    next_year = floatround(1970 + (unix_timestamp / 86400) * 0.00273790926, floatround_floor) + 1; 
    ut_of_next_year = unix_timestamp_by_year[next_year - 1960]; 
    year = (!(next_year & 3) && ((next_year % 25) || !(next_year & 15))) && ut_of_next_year <= unix_timestamp <= ut_of_next_year + 86400 ? next_year : next_year - 1; 
    days_of_month[1] = (!(year & 3) && ((year % 25) || !(year & 15))) ? 29 : 28; 
    unix_timestamp -= unix_timestamp_by_year[year - 1960] + ((hour = (unix_timestamp / 3600) % 24) * 3600) + ((minute = (unix_timestamp / 60) % 60) * 60) + (second = unix_timestamp % 60); 
    day = (unix_timestamp / 86400) + 1; 

    for (new i; i != sizeof days_of_month; i++) 
    { 
        if ((day -= days_of_month[i]) > 0) continue; 

        day = !day ? days_of_month[i] : day + days_of_month[i]; 
        month = i + 1; 

        break; 
    } 
}

stock ClearChat(playerid, linhas) {
    for(new i = 0; i < linhas; i++)
        SendClientMessage(playerid, -1, " ");

    return 1;
}

// Restante dos utilitarios
#include <msg>
#include <fix>