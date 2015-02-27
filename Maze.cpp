#include "Maze.h"
#include "Color.h"
#include "Rect.h"

#include <windows.h>  //for the sleep function

#include <iostream>
using namespace std;

Maze::Maze(Matrix* mz)
{
   maze = mz;
   height = maze->getNumRows();
   width = maze->getNumCols();

   WALL = 0;
   SPACE = 1;
   TRIED = 2;
   BACKTRACK = 3;
   PATH = 4;
}

Maze::~Maze()
{
   delete maze;
}

void Maze::addListener(Update* g)
{
   gui = g;
}

bool Maze::solve()
{
   bool done = traverse();
   return done;
}

//backing through the maze, setting the color to BACKTRACK
Cell* Maze::processBackTrack(StackLinked<Cell>* stack)
{
   //DO THIS
   //you may need to back through several cells

   Cell* top_cell = stack->peek();  
   //top_cell is NULL if the stack is empty
   //top_cell's direction is DEAD_END if you need to keep backtracking

   Cell* popped_cell;
   Cell* next_cell;
   Dir direction;
   
   int top_row = top_cell->getRow(); //get the row of the cell on top of the stack
   int top_col = top_cell->getCol(); //get the column of the cell on top of the stack
   
   int next_row;
   int next_col;

	//this is probably not the best way to do this, but it works
   bool loop = true;
   while (loop)  //need to back track
   {
		popped_cell = new cell;

		//remove the cell and set the maze location to BACKTRACK (the maze is a Matrix)
		
		mz->setElement(top->row(), top->col(), static_cast<double>(BACKTRACK)); //update the maze location to BACKTRACK
		
		popped_cell = stack->pop(); //if the program crashes here, we know that we didn't need to manually delete the item we popped from the stack

		delete popped_cell;
		
      //look at the next cell
		top_cell = stack->peek();
		
		direction = top_cell->getDir();
		
		next_row = top_cell->getRow();
		next_col = top_cell->getCol();
	
	//the following section checks each of the neighboring cells (in respective order. This is not necessary, but is more efficient) to the cell on top of the stack to see weather or not if any of the adjacent cells are spaces.
	//If there are no neighboring cells containing spaces, then we continue to backtrack. Otherwise, we check the cell in the direction after the direction after we first backtracked
	//to see if it is a space. If not, we check the adjacent cell in the next direction and so on . If there are no neighboring cells containing spaces, then we continue to backtrack. 
	
		//went down initially
		if (direction == RIGHT)
		{
		
			if (mz->getElement(nextRow, nextCol + 1) == SPACE) 
			{
				loop = false;
			}
			if (mz->getElement(nextRow - 1, nextCol) == SPACE)
			{
				loop = false;
			}
			if (mz->getElement(nextRow, nextCol - 1))
			{
				loop = false
			}
		}

		//went right initially
		if (direction == UP)
		{
			if (mz->getElement(nextRow - 1, nextCol) == SPACE) 
			{
				loop = false;
			}
			if (mz->getElement(nextRow, nextCol - 1) == SPACE)
			{
				loop = false;
			}
			/*
			Down can't be a space. We would've already went there
			if (mz->getElement(nextRow - 1, nextCol))
			{
				loop = false
			}
			*/
		}
		
		//went up initailly
		if (direction == LEFT)
		{
			if (mz->getElement(nextRow, nextCol - 1) == SPACE) 
			{
				loop = false;
			}
			
			/*
			Down can't be a space. We would've already went there
			if (mz->getElement(nextRow - 1, nextCol) == SPACE)
			{
				loop = false;
			}
			*/
			
			/*
			Left can't be a space. We would've already went there.
			if (mz->getElement(nextRow, nextCol - 1) == SPACE)
			{
				loop = false;
			}
			*/
		}
      Sleep(75);      //slow down the maze traversal
      gui->update();  //update whenever the color of a cell has been changed
   }

   return top_cell;
}

bool Maze::isSolved(Cell* curr_cell, StackLinked<Cell>* stack)
{
   //DO THIS
   //get row and col from curr_cell

   int row = curr_cell->getRow();
   int col = curr_cell->getCol();

   int final_row = mz->getNumRows();
   int final_col = mz->getNumCols();

   //have you solved the maze? (check that we are at the bottom right maze location and that it is a SPACE
   if (mz->getElement(final_row, final_col) == mz->getElement(row, col) && mz->getElement(final_row, final_col))  
   {


      //set the maze location to TRIED
	  mz->setElement(row,col, static_cast<double>(TRIED));

      //push curr_cell

	  stack->push(curr_cell());

      gui->update();
      //return the appropriate boolean
	  
	  return true;

   }

   return false;

   //return the appropriate boolean
}

//backing through the maze, setting the solution color to PATH
void Maze::processSolution(StackLinked<Cell>* stack)
{
   //DO THIS
   //the stack has the solution path stored
   
   Cell* top_cell;
   
   int row;
   int col;
   while(!stack->isEmpty())
   {
      //get the next cell from the stack
		top_cell = stack->pop();

		row = top_cell->getRow();
		col = top_cell->getCol();
		
		mz->setElement(row, col, static_cast<double>(PATH));//update the maze location to PATH


      gui->update();
   }
}

bool Maze::traverse()
{
   //DO THIS
   //complete several sections in this method

   bool done = false; //assume we are not done unless proven otherwise
   StackLinked<Cell> stack;

   maze->setElement(1, 1, TRIED);
   gui->update();

   Cell* start_cell = new Cell(1, 1);
   stack.push(start_cell);  //start from the top left corner

   while(!stack.isEmpty())
   {
      Cell* top_cell = processBackTrack(&stack);
      if (top_cell == NULL) break;  //no solution (back tracked all the way to the beginning)

      //call a method in the Cell class to give you a new Cell in a new direction relative to top_cell (initially, DOWN)
      //DO THIS
      Cell* curr_cell = top_cell->nextCell();





      //does this new Cell solve the maze?
      done = isSolved(curr_cell, &stack);
      if (done) break;

      //DO THIS
      //get the row and col from curr_cell
      int row = curr_cell->getRow();
      int col = curr_cell->getCol();

      //check that the current maze location corresponds to SPACE, otherwise delete it
      if (mz->getElement(row, col) == SPACE)
      {
         //update the maze location to TRIED
         //put the cell on the stack (move forward through the maze)
		
		mz->setElement(row,col, static_cast<double>(TRIED));
		stack->push(curr_cell);

		




         Sleep(75);  //slow down the maze traversal
         gui->update();
      }
      else //look for a different route 
      {
         //DO THIS
         //delete the cell

		 delete curr_cell;

      }
   }

   //did we make it to the bottom right?
   if (done)
   {
      processSolution(&stack);
   }
   else
   {
      cout << "No solution." << endl;
   }

   return done;
}

void Maze::mouseClicked(int x, int y)
{}

void Maze::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   int rows = maze->getNumRows();
   int cols = maze->getNumCols();
   int cell_width = (int) (((double) width)/cols + 0.5);
   int cell_height = (int) (((double) height)/rows + 0.5);

   Color red(1.0, 0.0, 0.0);
   Rect redRect(&red, cell_width, cell_height);

   Color green(0.0, 1.0, 0.0);
   Rect greenRect(&green, cell_width, cell_height);

   Color blue(0.0, 0.0, 1.0);
   Rect blueRect(&blue, cell_width, cell_height);

   Color white(1.0, 1.0, 1.0);
   Rect whiteRect(&white, cell_width, cell_height);

   Color black(0.0, 0.0, 0.0);
   Rect blackRect(&black, cell_width, cell_height);
 
   for (int i = 1; i <= rows; i++)
   {
      for (int j = 1; j <= cols; j++)
      {
         int val = (int) maze->getElement(i, j);
         int x_pixel = (j - 1) * cell_width + cell_width/2;
         int y_pixel = (i - 1) * cell_height + cell_height/2;

         if (val == WALL)
         {
            blackRect.draw(cr, x_pixel, y_pixel);
         }
         else if (val == SPACE)
         {
            whiteRect.draw(cr, x_pixel, y_pixel);
         }
         else if (val == TRIED)
         {
            blueRect.draw(cr, x_pixel, y_pixel);
         }
         else if (val == BACKTRACK)
         {
            redRect.draw(cr, x_pixel, y_pixel);
         }
         else if (val == PATH)
         {
            greenRect.draw(cr, x_pixel, y_pixel);
         }
      }
   }
}
