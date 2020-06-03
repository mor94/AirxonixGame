#pragma once
#define PICSIZE 25
#define BOARD_SIZE 25
#define SHIFT 300
enum myEnum
{
	t_newGame,
	t_help,
	t_highScore,
	t_exit,
	t_timePrize,
	t_lifePrize,
	t_poisionPrize,
	t_boostPrize,
	t_coinPrize,
	t_menuBackground,
	t_helicopter,
	t_wreckingBall,
	t_regularBall,
	t_hedgehog,
	t_fullCell,
	t_emptyCell,
	t_line,
	t_background,
	t_board,
	t_heart,
	t_clock,
	t_helpScreen,
	t_levelUpScreen,
	t_highScoreBackground,
	t_gameOverBackground,
	t_youWinBackground,
	t_poisionScreen,
	t_MAX_texture
};
enum direction
{
	t_up,
	t_down,
	t_left,
	t_right,
	t_wait
};
enum sounds
{
	t_backgroundSound,
	t_welcomeSound,
	t_startSound,
	t_lineSound,
	t_lifePrizeSound,
	t_scorePrizeSound,
	t_timePrizeSound,
	t_poisionPrizeSound,
	t_frozenPrizeSound,
	t_gameOverSound,
	t_ByeByeSound,
	t_clickSound,
	t_OoSound,
	t_OhySound,
	t_closeAreaSound,
	t_runningOutTimeSound,
	t_MAX_SOUND

};
