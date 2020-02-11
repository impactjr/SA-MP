/*

	-> Include: Vehicle Control
	-> Author: YumikoJR & Impact
	-> Date: 11th February
	-> Copyright (C) 2020

*/

#if defined _inc_vehicle_control
	#undef _inc_vehicle_control
#endif

#if defined _vehicle_control_included
	#endinput
#endif
#define _vehicle_control_included

#tryinclude <a_samp>
#tryinclude <YSI_Coding\y_hooks>

#if !defined PRESSED
#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#endif

static
	Menu:vc_Menu,
	bool:openedMenu[MAX_PLAYERS char],
	bool:SelectedMenu[MAX_PLAYERS char][4],
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

hook OnGameModeInit() {
	vc_Menu = CreateMenu("Veh Control", 4, 200.0, 100.0, 150.0, 150.0);
	AddMenuItem(vc_Menu, 0, "Bonnet");
	AddMenuItem(vc_Menu, 0, "Boot");
	AddMenuItem(vc_Menu, 0, "Lights");
	AddMenuItem(vc_Menu, 0, "Engine");
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if (PRESSED(KEY_YES)) {
		if (!openedMenu[playerid]) {
			ShowMenuForPlayer(vc_Menu, playerid);
			openedMenu[playerid] = true;
		} else if (openedMenu[playerid]) {
			HideMenuForPlayer(vc_Menu, playerid);
			openedMenu[playerid] = false;
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerSelectedMenuRow(playerid, row) {
	if (GetPlayerMenu(playerid) == (vc_Menu)) {
		new vehicleID = GetPlayerVehicleID(playerid);

		switch (row) {
			case 0: {
				if (!SelectedMenu[playerid][0]) {
					GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, 1, boot, objective);
					SendClientMessage(playerid, -1, "Bonnet opened!");

					SelectedMenu[playerid][0] = true;
				} else if (SelectedMenu[playerid][0]) {
					GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, 0, boot, objective);
					SendClientMessage(playerid, -1, "Bonnet closed!");

					SelectedMenu[playerid][0] = false;
				}
			}
			case 1: {
				if (!SelectedMenu[playerid][1]) {
					GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, 1, objective);
					SendClientMessage(playerid, -1, "Boot opened!");

					SelectedMenu[playerid][1] = true;
				} else if (SelectedMenu[playerid][1]) {
					GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, 0, objective);
					SendClientMessage(playerid, -1, "Boot closed!");

					SelectedMenu[playerid][1] = false;
				}
			}
			case 2: {
				if (!SelectedMenu[playerid][2]) {
					GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vehicleID, engine, 1, alarm, doors, bonnet, boot, objective);
					SendClientMessage(playerid, -1, "Lights turned on!");

					SelectedMenu[playerid][2] = true;
				} else if (SelectedMenu[playerid][2]) {
					GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vehicleID, engine, 0, alarm, doors, bonnet, boot, objective);
					SendClientMessage(playerid, -1, "Lights turned off!");

					SelectedMenu[playerid][2] = false;
				}
			}
			case 3: {
				if (!SelectedMenu[playerid][3]) {
					GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vehicleID, 1, lights, alarm, doors, bonnet, boot, objective);
					SendClientMessage(playerid, -1, "Engine started!");

					SelectedMenu[playerid][3] = true;
				} else if (SelectedMenu[playerid][3]) {
					GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(vehicleID, 0, lights, alarm, doors, bonnet, boot, objective);
					SendClientMessage(playerid, -1, "Engine switched off!");

					SelectedMenu[playerid][3] = false;
				}
			}
		}
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate) {
	if (newstate == PLAYER_STATE_DRIVER) {
		new vehicleID = GetPlayerVehicleID(playerid);
		GetVehicleParamsEx(vehicleID, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(vehicleID, 0, lights, alarm, doors, bonnet, boot, objective);
		SendClientMessage(playerid, -1, "You entered the vehicle, to start the engine, press Y!");
	}
	return Y_HOOKS_CONTINUE_RETURN_1;
}
