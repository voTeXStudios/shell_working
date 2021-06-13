#include <stdio.h>
#include <stdlib.h>
#include "tic_tac_toe.h"
#include <unistd.h>

void win();
void board();
void win(int player, int winner, int pos[])
{
	board(pos);
	if (winner){
		printf("===> Player %d is the winner\n", player);
	}
}

void board(int pos[])
{
	const char* screen_clear = " \e[1;1H\e[2J";
  	if (write(STDOUT_FILENO, screen_clear, 12) == -1){
      		fprintf(stderr, "Error while clearing the screen");
      		return;
  	}
	printf("\n\n\tTic Tac Toe\n\n");

	printf("Player 1 (X)  -  Player 2 (O)\n\n\n");


	printf("     |     |     \n");
	printf("  %c  |  %c  |  %c \n", pos[0], pos[1], pos[2]);

	printf("_____|_____|_____\n");
	printf("     |     |     \n");

	printf("  %c  |  %c  |  %c \n", pos[3], pos[4], pos[5]);

	printf("_____|_____|_____\n");
	printf("     |     |     \n");

	printf("  %c  |  %c  |  %c \n", pos[6], pos[7], pos[8]);

	printf("     |     |     \n\n");
}

void play()
{
	int winner = 0, count = 0;
	int pos[9], index, sign, player, flag, i, k;
	

	for(i=0; i<9; i++)
		pos[i] = ' ';
	board(pos);
	while (count < 9 && winner != 1){
		flag = 0;
		//print board
		if (count % 2 == 0){
			sign = 'X';
			player = 1;
		}
		else{
			sign = 'O';
			player = 2;
		}

		printf("Move for player %d[1-9] (0 for exit): ", player);

		int check = scanf("%d", &index);

		while((getchar() != '\n'));

		if (check != 1)
		{
			printf("ERROR: Invalid arg\n");
			continue;

		}
			
		if (index == 0)
			return;

		if (index < 1 || index > 9){
			printf("ERROR: Invalid position\n");
			continue;			
		}
		

		if (pos[index - 1] == 'X' || pos[index - 1] == 'O'){
			printf("NOTE: Position is occupied\n");
			continue;
		}
		
		pos[index - 1] = sign;
		board(pos);
		count++;

		for(i=0;i<9;i++)
		{
			if (i % 3 == 0)
				flag = 0;
			if (pos[i] == sign)
				flag++;
			if (flag == 3){
				winner = 1;
				win(player, winner, pos);
			}
		}
		flag = 0;

		for (i = 0; i < 3; i++)
		{
			for (k = 0; k <= i + 6; k+=3)
			{
				if (pos[k] == sign)
					flag++;
			}
			if (flag == 3){
				winner = 1;
				win(player, winner, pos);
			}
			flag = 0;
		}


		if ((pos[0] == sign && pos[4] == sign && pos[8] == sign)||(pos[2] == sign && pos[4] == sign && pos[6] == sign)){
				winner = 1;
				win(player, winner, pos);
		}
		

	}
	if (count == 9 && winner != 1){
		board(pos);
		printf("===> Match Draw!!\n");
	}

}
