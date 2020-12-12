/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanity_check)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, test_all_initially_blank)
{
    Piezas p;
    bool all_blank = true;
    for(int i = 0; i < BOARD_ROWS; i++) {
      for(int j = 0; j < BOARD_COLS; j++) {
        if(p.pieceAt(i, j) != Blank) {
          all_blank = false;
          break;
        }
      }
    }
	ASSERT_TRUE(all_blank);
}

TEST(PiezasTest, test_not_blank_after_drop)
{
    Piezas p;
    p.dropPiece(1);
    bool all_blank = true;
    for(int i = 0; i < BOARD_ROWS; i++) {
      for(int j = 0; j < BOARD_COLS; j++) {
        if(p.pieceAt(i, j) != Blank) {
          all_blank = false;
          break;
        }
      }
    }
	ASSERT_FALSE(all_blank);
}

TEST(PiezasTest, test_one_drop)
{
    Piezas p;
    p.dropPiece(0);
	ASSERT_TRUE(p.pieceAt(0, 0) == X);
}

TEST(PiezasTest, test_two_drops)
{
    Piezas p;
    p.dropPiece(0);
    p.dropPiece(0);
	ASSERT_TRUE((p.pieceAt(0, 0) == X) && (p.pieceAt(1, 0) == O));
}

TEST(PiezasTest, test_x_win_vert)
{
    /*  XOOX
        XXOO
        XOXO   */
    Piezas p;
    p.dropPiece(0); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(3); // O
    p.dropPiece(0); // X
    p.dropPiece(2); // O
    p.dropPiece(1); // X
    p.dropPiece(3); // O
    p.dropPiece(0); // X
    p.dropPiece(1); // O
    p.dropPiece(3); // X
    p.dropPiece(2); // O
	ASSERT_TRUE(p.gameState() == X);
}

TEST(PiezasTest, test_o_win_vert)
{
    /*  OXXO
        OOXX
        OXOX   */
    Piezas p;
    p.dropPiece(1); // X
    p.dropPiece(0); // O
    p.dropPiece(3); // X
    p.dropPiece(2); // O
    p.dropPiece(2); // X
    p.dropPiece(0); // O
    p.dropPiece(3); // X
    p.dropPiece(1); // O
    p.dropPiece(1); // X
    p.dropPiece(0); // O
    p.dropPiece(2); // X
    p.dropPiece(3); // O
	ASSERT_TRUE(p.gameState() == O);
}

TEST(PiezasTest, test_x_win_horiz)
{
    /*  OOOX
        OOOX
        XXXX   */
    Piezas p;
    p.dropPiece(0); // X
    p.dropPiece(0); // O
    p.dropPiece(1); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(2); // O
    p.dropPiece(3); // X
    p.dropPiece(0); // O
    p.dropPiece(3); // X
    p.dropPiece(1); // O
    p.dropPiece(3); // X
    p.dropPiece(2); // O
	ASSERT_TRUE(p.gameState() == X);
}

TEST(PiezasTest, test_o_win_horiz)
{
    /*  XXXO
        XXXO
        OOOO   */
    Piezas p;
    p.dropPiece(0); // X
    p.dropPiece(0); // O
    p.dropPiece(1); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(2); // O
    p.dropPiece(0); // X
    p.dropPiece(3); // O
    p.dropPiece(1); // X
    p.dropPiece(3); // O
    p.dropPiece(2); // X
    p.dropPiece(3); // O
	ASSERT_TRUE(p.gameState() == O);
}
