#!/usr/bin/env python3

import sys

if len(sys.argv) != 2:
    print("Usage: 01-football-match.py <number in hex>")
    sys.exit(1)

data = int(sys.argv[1], 16)

# ِِIndex is 5-bit team's id
teams = ["Abha", "Ahli", "Ittihad", "Ettifaq", "Albatin", "Altaawoun", "Alraed", "Al-Shabab", "Al-Ain", "Al Fateh", "Alfaisaly", "Qadissiyah", "Nasser", "Alhilal", "Alwehda", "Damac"]
leagues = ["Super", "Roution", "Crown Prince", "Custodian"]

team_1_id = data & 0b11111
team_2_id = (data & (0b11111 << 5)) >> 5
game_status = (data & (0b11 << 10)) >> 10
whose_field = (data & (0b1 << 12)) >> 12
league = (data & (0b11 << 13)) >> 13
referee_nationality = (data & (0b1 << 14)) >> 14

team_1_name = teams[team_1_id % len(teams)]
team_2_name = teams[team_2_id % len(teams)]

if whose_field == 0:
    field_name = team_1_name
else:
    field_name = team_2_name

print(f"As part of {leagues[league]}, {team_1_name} was scheduled to play against {team_2_name} on {field_name}'s home.")

if referee_nationality == 0:
    print("The appointed referee is local.")
else:
    print("The appointed referee is foreign.")

match game_status:
    case 0b00:
        print("The game tied.")
    case 0b01:
        print(team_1_name + " won!")
    case 0b10:
        print(team_2_name + " won!")
    case 0b11:
        print("The game was cancelled.")
