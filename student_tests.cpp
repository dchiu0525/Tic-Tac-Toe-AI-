#include <cstdlib>
#include <ctime>
#include "catch.hpp"
#include <memory>
#include "XO.hpp"

//X = -1
//O = 1


TEST_CASE("Presetting constructor")
{
	INFO("presetting constructor");
	int8_t a[3] = { -1,1,-1 };
	uint8_t b[3] = { 1,4,5 };
	XO g(a,b,3 );

	g.show();
	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 3);
}

TEST_CASE("Testing makemove and show")
{
	INFO("makemove and show");
	XO g;
	g.makeMove(-1, 2);
	g.makeMove(1, 0);
	g.makeMove(-1, 3);
	g.makeMove(1, 7);
	g.makeMove(-1, 6);
	g.makeMove(1, 8);
	g.show();
	int8_t a[3] = { -1,1,-1 };
	uint8_t b[3] = { 1,4,5 };
	g.makeMoves(a, b, 3);
	g.show();
	REQUIRE(g.winner() == 1);
	REQUIRE(g.getBoard().numMoves == 9);
}



TEST_CASE("check invalid order")
{
	INFO("check invalid order");
	XO g;
	g.makeMove(-1, 2);
	g.makeMove(-1, 1);
	REQUIRE(g.makeMove(-1, 1) == false);
}

TEST_CASE("Player sequence incorrect")
{
	INFO("Player sequence incorrect");
	XO g;
	g.makeMove(-1, 2);
	g.makeMove(1, 0);
	g.makeMove(-1, 3);
	g.makeMove(1, 7);
	g.makeMove(-1, 6);
	g.makeMove(1, 8);

	g.show();


	REQUIRE(g.makeMove(1, 1)==false);
	int8_t a[3] = { 1,1,-1 };
	uint8_t b[3] = { 1,4,5 };
	g.makeMoves(a, b, 3);
	REQUIRE(g.makeMoves(a, b, 3)== false);


}

TEST_CASE( "Player X immediate win" )
{
	INFO( "Player X eventual win" );
	XO g;
	g.makeMove(-1,2);	
	g.makeMove(1,0);
	g.makeMove(-1,3);
	g.makeMove(1,7);
	g.makeMove(-1,6);
	g.makeMove(1,8);

	g.show();
	
	while(!g.gameOver())
	  g.makeOptimalMove();
	
	g.show();
	
	REQUIRE(g.winner() == -1);
	REQUIRE(g.getBoard().numMoves == 7);
}

TEST_CASE( "Optimal block w/certain loss for O" )
{
	INFO( "Optimal block w/certain loss for O" );
	XO g;
	g.makeMove(-1,1);
	g.makeMove(1,6);
	g.makeMove(-1,5);
	g.makeMove(1,7);
	g.makeMove(-1,8);

	g.makeOptimalMove();
	
	g.show();	

	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 6);
}
//
TEST_CASE( "Player X eventual win" )
{
	INFO( "Player X eventual win" );
	XO g;
	g.makeMove(-1,1);
	g.makeMove(1,6);
	g.makeMove(-1,5);
	g.makeMove(1,7);
	g.makeMove(-1,8);
	std::cout << "start\n";
	g.show();
	while (!g.gameOver()) {
		g.makeOptimalMove();
		g.show();
	}
	std::cout << "end\n";
	g.show();
	
	REQUIRE(g.winner() == -1);
	REQUIRE(g.getBoard().numMoves == 9);
}

TEST_CASE( "Optimal block w/certain loss for X" )
{
	INFO( "Optimal block w/certain loss for X" );
	XO g;
	g.makeMove(1,1);
	g.makeMove(-1,6);
	g.makeMove(1,5);
	g.makeMove(-1,7);
	g.makeMove(1,8);

	//while (!g.gameOver()) 
	//	g.makeOptimalMove();
	
	
	 

	g.makeOptimalMove();
	g.show();
	
	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 6);
}

TEST_CASE( "Player O eventual win" )
{
	INFO( "Player O eventual win" );
	XO g;
	g.makeMove(1,1);
	g.makeMove(-1,6);
	g.makeMove(1,5);
	g.makeMove(-1,7);
	g.makeMove(1,8);
	std::cout << "start1\n";
	g.show();
	while(!g.gameOver())
	  g.makeOptimalMove();
	

	std::cout << "end1\n";
	g.show();
	
	REQUIRE(g.winner() == 1);
	REQUIRE(g.getBoard().numMoves == 9);
}

TEST_CASE("test1")
{
	INFO("test1");
	XO g;
	g.makeMove(1, 0);
	g.makeMove(-1, 3);
	g.makeMove(1, 6);

	while (!g.gameOver()) {
		g.makeOptimalMove();

	}
//	std::cout << std::endl;
	g.show();


	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 9);
}

TEST_CASE("Player X corner")
{
	INFO("Player X corner");
	XO g;
	g.makeMove(-1, 0);

	std::cout << "start\n";
	g.show();
	while (!g.gameOver()) {
		g.makeOptimalMove();
		g.show();
	}
//	std::cout << std::endl;
	g.show();


	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 9);
}


TEST_CASE("Player X corner,O middle")
{
	INFO("Player X corner");
	XO g;
	g.makeMove(-1, 0);
	g.makeMove(1, 4);

	while (!g.gameOver()) {
		g.makeOptimalMove();		
	}

//	std::cout << std::endl;

	g.show();



	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 9);
}

TEST_CASE("Player O middle")
{
	INFO("Player O middle");
	XO g;
	g.makeMove(1, 4);
	g.show();
	while (!g.gameOver()) {
		g.makeOptimalMove();
		g.show();
	}
	//std::cout << std::endl;
	g.show();

	

	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 9);
}