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
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(1); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(2); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(3); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(0); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(2); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(1); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(3); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(0); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(1); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(3); // X
	ASSERT_TRUE(p.gameState() == Invalid);
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

TEST(PiezasTest, test_placement_greater_than_bounds)
{
    /*  XXOX
        OOOO
        XXXOX  */
    Piezas p;
    p.dropPiece(0); // X
    p.dropPiece(0); // O
    p.dropPiece(1); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(2); // O
    p.dropPiece(4); // X!
    p.dropPiece(3); // O
    p.dropPiece(1); // X
    p.dropPiece(3); // O
    p.dropPiece(3); // X
    p.dropPiece(2); // O
    p.dropPiece(0); // X
	ASSERT_TRUE(p.gameState() == O);
}

TEST(PiezasTest, test_placement_less_than_bounds)
{
    /*  XXOX
        OOOO
       XXXXO  */
    Piezas p;
    p.dropPiece(0); // X
    p.dropPiece(0); // O
    p.dropPiece(1); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(2); // O
    p.dropPiece(-1); // X!
    p.dropPiece(3); // O
    p.dropPiece(1); // X
    p.dropPiece(3); // O
    p.dropPiece(3); // X
    p.dropPiece(2); // O
    p.dropPiece(0); // X
	ASSERT_TRUE(p.gameState() == O);
}

TEST(PiezasTest, test_too_many_pieces_for_column)
{
    /*   O
        XXOX
        OOXX
        OXOX   */
    Piezas p;
    p.dropPiece(1); // X
    p.dropPiece(0); // O
    p.dropPiece(3); // X
    ASSERT_TRUE(p.dropPiece(2) == O); // O
    p.dropPiece(2); // X
    p.dropPiece(0); // O
    ASSERT_TRUE(p.dropPiece(3) == X); // X
    p.dropPiece(1); // O
    p.dropPiece(1); // X
    ASSERT_TRUE(p.dropPiece(1) == Blank); // 0!
    p.dropPiece(0); // X
    p.dropPiece(2); // O
    p.dropPiece(3); // X
	ASSERT_TRUE(p.gameState() == X);
}

TEST(PiezasTest, test_o_win_horiz)
{
    /*  XXXO
        XXXO
        OOOO   */
    Piezas p;
    p.dropPiece(0); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(0); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(1); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(1); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(2); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(2); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(0); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(3); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(1); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(3); // O
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(2); // X
	ASSERT_TRUE(p.gameState() == Invalid);
    p.dropPiece(3); // O
	ASSERT_TRUE(p.gameState() == O);
}

TEST(PiezasTest, test_tie_game)
{
    /*  XOXO
        XOXO
        XOXO   */
    Piezas p;
    p.dropPiece(0); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(3); // O
    ASSERT_TRUE(p.dropPiece(0) == X); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(3); // O
    p.dropPiece(0); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(3); // O
	ASSERT_TRUE(p.gameState() == Blank);
}

TEST(PiezasTest, test_invalid_win)
{
    /*  ----
        ----
        XOXO   */
    Piezas p;
    p.dropPiece(0); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(3); // O
	ASSERT_TRUE(p.gameState() == Invalid);
}

TEST(PiezasTest, test_invalid_win_blank)
{
    /*  ----
        ----
        ----   */
    Piezas p;
	ASSERT_TRUE(p.gameState() == Invalid);
}

TEST(PiezasTest, test_pieceAt)
{
    /*  ----
        ----
        XOXO   */
    Piezas p;
    p.dropPiece(0); // X
    p.dropPiece(1); // O
    p.dropPiece(2); // X
    p.dropPiece(3); // O
	ASSERT_TRUE(p.pieceAt(2, 2) == Blank);
	ASSERT_TRUE(p.pieceAt(1, 2) == Blank);
	ASSERT_TRUE(p.pieceAt(1, 3) == Blank);
	ASSERT_TRUE(p.pieceAt(0, 0) == X);
	ASSERT_TRUE(p.pieceAt(0, 1) == O);
	ASSERT_TRUE(p.pieceAt(0, 2) == X);
	ASSERT_TRUE(p.pieceAt(0, 3) == O);
	ASSERT_TRUE(p.pieceAt(2, 5) == Invalid);
	ASSERT_TRUE(p.pieceAt(-1, 2) == Invalid);
	ASSERT_TRUE(p.pieceAt(-1, 8) == Invalid);
}

TEST(PiezasTest, test_pieceAt_works_as_expected)
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
	ASSERT_TRUE(p.pieceAt(0, 0) == X);
	ASSERT_TRUE(p.pieceAt(0, 1) == O);
	ASSERT_TRUE(p.pieceAt(0, 2) == X);
	ASSERT_TRUE(p.pieceAt(0, 3) == O);
	ASSERT_TRUE(p.pieceAt(1, 0) == X);
	ASSERT_TRUE(p.pieceAt(1, 1) == X);
	ASSERT_TRUE(p.pieceAt(1, 2) == O);
	ASSERT_TRUE(p.pieceAt(1, 3) == O);
	ASSERT_TRUE(p.pieceAt(2, 0) == X);
	ASSERT_TRUE(p.pieceAt(2, 1) == O);
	ASSERT_TRUE(p.pieceAt(2, 2) == O);
	ASSERT_TRUE(p.pieceAt(2, 3) == X);
}

TEST(PiezasTest, test_o_win_reset_x_win)
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

    ASSERT_TRUE(p.dropPiece(3) == Blank); // X!
	ASSERT_TRUE(p.gameState() == O);

    p.reset();
    /*  OOOX
        OOOX
        XXXX   */
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

