package edu.temple.datastructures.dyee.oop.assignment.episode1;

import java.util.Random;

/**
 * Represents a creature.
 */
public class Creature {

    // instance variables -- every creature has a location
    private Model model;
    /** The row of the field containing this creature (do not modify!) */
    int row;
    /** The column of the field containing this creature (do not modify!) */
    int column;
    static Random randomNumberGenerator = new Random();
    
    /**
     * Constructor for objects of class Creature.
     *
     * @param model  the model (needed to use Model.look and Model.move methods
     * @param row  the row of the field in which to place this creature
     * @param column  the column of the field in which to place this creature
     */
    public Creature(Model model, int row, int column) {
        this.model = model;
        this.row = row;
        this.column = column;
    }
    
    /**
     * Utility method to choose a random integer from min
     * to max, inclusive.
     *
     * @param min  the minimum value to be returned
     * @param max  the maximum value to be returned
     * @return a random integer N, where min &lt;= N &lt;= max
     */
    static int random(int min, int max) {
        return Model.random(min, max);
    }

    /**
     * Finds the first visible thing in the given direction, starting
     * from this creature's current position.
     *
     * @param direction the direction in which to look
     * @return the object seen
     */
    int look(int direction) {
        return model.look(row, column, direction);
    }
    
    /**
     * Finds the distance to the first visible thing in the given
     * direction, starting from this creature's current position.
     *
     * @param direction the direction in which to look
     * @return the distance to the object seen
     */
    int distance(int direction) {
        return model.distance(row, column, direction);
    }
    
    /**
     * Determines whether this creature can move one step in the
     * given direction. A creature cannot move off the edge of
     * the array or onto a bush, but it <i>can</i> move onto
     * another creature.<p>
     * If we extend this program to allow multiple persons or
     * multiple monsters, we should disallow a creature moving onto
     * another creature of the same type.
     *
     * @param direction the direction in which to consider moving
     * @return true if the move is possible
     */
    boolean canMove(int direction) {
        if (direction == Model.STAY) return true;
        if (distance(direction) > 1) return true;
        int object = look(direction);
        if (object == Model.EDGE || object == Model.BUSH) return false;
        return true;
    }
    
    /**
     * Decides what direction to move next.
     *
     * @return the desired direction
     */
    int decideMove() {
        return Model.STAY;
    }
}
