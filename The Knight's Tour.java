class Main {
	//The Knight
	public static void main(String[] args) {
	   Knight();
	}
	
	public static void printBoard(int [][] yourBoard) {
	    for(int i = 0; i < yourBoard.length; i++) {
	        for(int j = 0; j < yourBoard[0].length; j++) {
	            System.out.print(yourBoard[i][j] + "\t");
	            if(j == (yourBoard[0].length - 1)) {
	                System.out.println("");
	            }
	        }
	    }
	}
	
	// Checks if the knight can move to that position
	public static boolean canMove(int xPosition, int yPosition, int[][] yourBoard) {
	    if(xPosition >= 0 && xPosition < yourBoard.length && yPosition >= 0 && yPosition < yourBoard[0].length) { // Check if the knight is in bounds of the chess board
	        if(yourBoard[xPosition][yPosition] == 1) { // If in bounds, check if the position hasn't been touched
	            return true;
	        }
	    }
	    return false;
	}
	
	// Move the knight through the board 
	public static boolean moveKnight(int yourX, int yourY, int moveCounter, int[][] yourBoard) {
	    if(moveCounter == (yourBoard.length * yourBoard[0].length)) {// Check if you've touched all positions on the board
	        printBoard(yourBoard); // if all positions were touched, print the board
	        return true;
	    }
	    int[] xPossibleMoves = {2, 1, -1, -2, -2, -1, 1, 2}; // Denotes the shift in the knight's movement that correspond with the index of the Y movement
		int[] yPossibleMoves = {1, 2, 2, 1, -1, -2, -2, -1}; // Denotes the shift in the knight's movement that correspond with the index of the X movement
	    for(int i = 0; i < yourBoard.length; i++) {
	        int newX = yourX + xPossibleMoves[i]; // Denotes new X position after a single knight move
		    int newY = yourY + yPossibleMoves[i]; // Denotes new Y position after a single knight move
	        if(canMove(newX, newY, yourBoard)) {
	            yourBoard[newX][newY] = moveCounter; // Recursive step
	            if(moveKnight(newX, newY, moveCounter + 1, yourBoard)) {
	                return true;
	            } else {
	                yourBoard[newX][newY] = 1; // Set back to default
	            }
	        }
	    }
	    return false;
	}
	
	public static void Knight() {
	    int[][] chessBoard = new int[8][8]; // The chessBoard layout
	    for(int i = 0; i < chessBoard.length; i++) {
	        for(int j = 0; j < chessBoard[0].length; j++) {
	            chessBoard[i][j] = 1; // Fill the array with 1, it denotes all untouched positions
		    }
	    }
		chessBoard[0][0] = 0;// Place your knight location [0,0]

		if(moveKnight(0, 0, 1, chessBoard)) {
		   return;
		}
	}
}
