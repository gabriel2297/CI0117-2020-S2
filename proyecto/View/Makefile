compile:	interface.c
	         gcc `pkg-config --cflags gtk+-3.0` -O0 -g -o pthreadmon interface.c ../Model/mapper.c ../Controller/GameController/GameController.c ../Controller/PlayerController/PlayerController.c ../Controller/BattleController/BattleController.c ../Controller/PokemonController/PokemonController.c -pthread -lm `pkg-config --libs gtk+-3.0`
