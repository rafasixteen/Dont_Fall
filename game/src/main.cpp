#include "Game.hpp"

int main(void)
{
	Dont_Fall::Game game{};

	try
	{
		game.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}