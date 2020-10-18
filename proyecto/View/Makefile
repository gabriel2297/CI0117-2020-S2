compile:	interface.c
	         gcc `pkg-config --cflags gtk+-3.0` -o pthreadmon interface.c ../Model/mapper.c ../Controller/GameController/GameController.c ../Controller/PlayerController/PlayerController.c ../Controller/BattleController/BattleController.c ../Controller/PokemonController/PokemonController.c -pthread `pkg-config --libs gtk+-3.0`
