package edu.temple.datastructures.dyee.oop.assignment.episode1;

/**
 * Executes a number of "person hunts", in which a monster moves around a field
 * containing bushes, looking for a person, and prints out the percentage
 * of times that the person escapes.
 */
public class Grader {

    static final int NUMBER_OF_TRIALS = 300;
    
    // class variables
    private static Object[][] field;
    private static Model model;
    private static View view;
    private static Controller controller;
    private static int numberOfRows;
    private static int numberOfColumns;

    /**
     * Main class for starting person hunts and counting games.
     */
    public static void main(String args[]) {
        numberOfRows = numberOfColumns = 20;
        field = new Object[numberOfRows][numberOfColumns];
        model = new Model(field);
        countGames();
    }
    
    /**
     * Runs NUMBER_OF_TRIALS person hunts, and prints out the
     * results as a percentage of times the person escapes.
     */
    private static void countGames() {
    
        // compute base score as percent of person escapes
        int numberOfEscapes = 0;        
        for (int i = 0; i < NUMBER_OF_TRIALS; i++) {
            model.reset();
            while (!model.gameIsOver) {
                model.allowSingleMove();
            }
            if (model.personIsAlive) {
                numberOfEscapes++;
            }
        }
        double percent = (100 * numberOfEscapes) / NUMBER_OF_TRIALS;
        int roundedPercent = (int)(percent + 0.5);
        System.out.println("Person escapes: " + numberOfEscapes +
                           " times out of " + NUMBER_OF_TRIALS +
                           ", or " + roundedPercent + "%");
        System.out.println("Grade:" + Math.sqrt(roundedPercent)*10);
        
        // check for problems with assumptions about named constants
        Model.NUMBER_OF_ROWS = Model.NUMBER_OF_COLUMNS = 15;
//         Model.STAY = -1;
//         Model.N  = 10;
//         Model.NE = 11;
//         Model.E  = 12;
//         Model.SE = 13;
//         Model.S  = 14;
//         Model.SW = 15;
//         Model.W  = 16;
//         Model.NW = 17;
//         Model.MIN_DIRECTION = 10;
//         Model.MAX_DIRECTION = 17;
        try {
            for (int i = 0; i < 10; i++) {
                model.reset();
                while (!model.gameIsOver) {
                    model.allowSingleMove();
                }
            }
        }
        catch (Throwable e) {
            System.out.println("Error detected in use of constants.");
            e.printStackTrace();
        }        
    }
}
