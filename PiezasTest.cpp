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
