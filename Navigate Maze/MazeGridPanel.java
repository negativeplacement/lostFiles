import javax.swing.*;
import java.awt.*;
import java.util.Stack;
import java.util.Queue;

public class MazeGridPanel extends JPanel {
	private int rows;
	private int cols;
	private Cell[][] maze;

	// Extra credit
	public void generateMazeByDFS() {
		boolean[][] visited;
		Stack<Cell> stack = new Stack<Cell>();
		Cell start = maze[0][0];
		stack.push(start);
	}

	public void solveMaze() {
		Stack<Cell> stack  = new Stack<>();
		Cell start = maze[0][cols - 1];
		start.setBackground(Color.GREEN);
		Cell finish = maze[rows - 1][0];
		finish.setBackground(Color.RED);
		stack.push(start);

		// Implement your algorithm here

		while(!stack.empty()) {
			Cell thisCell = stack.peek(); // Gives your cell position
			if (thisCell.getBackground() == Color.RED) {
				break; // Stop loop you've reached the exit 
			} else if (!thisCell.northWall && !visited(thisCell.row - 1, thisCell.col)) { // Checks if we can go north given haven't visited there yet
				stack.push(maze[thisCell.row - 1][thisCell.col]); // Move to position
				thisCell.setBackground(Color.BLUE); // Mark the position as visited
			} else if (!thisCell.eastWall && !visited(thisCell.row, thisCell.col + 1))  { // Checks if we can go east given we haven't visited there yet
				stack.push(maze[thisCell.row][thisCell.col + 1]); // Move to position
				thisCell.setBackground(Color.BLUE); // Mark the position as visited
			} else if (!thisCell.southWall && !visited(thisCell.row + 1, thisCell.col)) { // Checks if we can go south given we haven't visited there yet
				stack.push(maze[thisCell.row + 1][thisCell.col]); // Move to position
				thisCell.setBackground(Color.BLUE); // Mark the position as visited
			} else if (!thisCell.westWall && !visited(thisCell.row, thisCell.col - 1))  { // Checks if we can go west given we haven't visited there yet
				stack.push(maze[thisCell.row][thisCell.col - 1]); // Move to position
				thisCell.setBackground(Color.BLUE); // Mark the position as visited
			} else {// Dead-End?
				thisCell.setBackground(Color.LIGHT_GRAY); // Mark color for dead-end
				stack.pop();
			}
		}
		start.setBackground(Color.GREEN); // Show where you started
		finish.setBackground(Color.RED); // Show where you ended
	}

	public boolean visited(int row, int col) {
		Cell c = maze[row][col];
		Color status = c.getBackground();
		if (status.equals(Color.WHITE) || status.equals(Color.RED)) {
			return false;
		}
		return true;
	}

	public void generateMaze() {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {

				if (row == 0 && col == 0) {
					continue;
				} else if (row == 0) {
					maze[row][col].westWall = false;
					maze[row][col - 1].eastWall = false;
				} else if (col == 0) {
					maze[row][col].northWall = false;
					maze[row - 1][col].southWall = false;
				} else {
					boolean north = Math.random() < 0.5;
					if (north) {
						maze[row][col].northWall = false;
						maze[row - 1][col].southWall = false;
					} else {
						maze[row][col].westWall = false;
						maze[row][col - 1].eastWall = false;
					}
					maze[row][col].repaint();
				}
			}
		}
		this.repaint();
	}

	public MazeGridPanel(int rows, int cols) {
		this.setPreferredSize(new Dimension(800, 800));
		this.rows = rows;
		this.cols = cols;
		this.setLayout(new GridLayout(rows, cols));
		this.maze = new Cell[rows][cols];
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				maze[row][col] = new Cell(row, col);
				this.add(maze[row][col]);
			}
		}
		this.generateMaze();
		this.solveMaze();
	}
}
