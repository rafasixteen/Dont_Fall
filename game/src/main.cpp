#include "Game.hpp"

#include "core/Defines.hpp"

int main(void)
{
	Dont_Fall::Game game{};
	//Dont_Fall::RGUI::GUI gui{ {game.GetScreenCenter().x,game.GetScreenCenter().y} };

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