package edu.temple.datastructures.dyee.oop.assignment.episode1;

public class Person extends Creature 
{

  boolean canSeeMonster = false;
  boolean canSeeBush = false;
  int personDirection = Model.STAY;

    public Person(Model model, int row, int column) 
    {
        super(model, row, column);
    }

    int decideMove() 
    {
        personDirection = seeMonster();
        return personDirection;
    }
    
    int seeMonster() {
      for (int i = Model.MIN_DIRECTION; i <= Model.MAX_DIRECTION; i++) {
        if (look(i) == Model.MONSTER) 
        {
          // We can see the monster
            canSeeMonster = true;
          // We can only change our cardinal direction by three or two in either direction to get out of the monsters line of view
            if (canMove(Model.turn(i, -3)))
            {
                 return Model.turn(i, -3);
            }
            if (canMove(Model.turn(i, 3)))
            {
                 return Model.turn(i, 3);
            }
            if (canMove(Model.turn(i, -2))) 
            {
                 return Model.turn(i, -2);
            }
            if (canMove(Model.turn(i, 2))) 
            { 
                return Model.turn(i, 2);
            }
            //If movement in disired direction is denied continue in direction
            return i;
        }
      }
      if (canSeeMonster) 
      {
        // We declare it as false because we are about to move out of sight
        canSeeMonster = false;
        if (canMove(personDirection + 3)) 
        { 
            return personDirection + 3;
        }
        if (canMove(personDirection - 3)) 
        {
            return personDirection - 3;
        }
        if (canMove(personDirection + 2)) 
        { 
            return personDirection + 2;
        }
        if (canMove(personDirection - 2)) 
        {
            return personDirection - 2;
        }
        return random(Model.MIN_DIRECTION, Model.MAX_DIRECTION);
      }
      return Model.STAY;
    }

    int seeBush() {
        for (int i = Model.MIN_DIRECTION; i <= Model.MAX_DIRECTION; i++) {
          if (look(i) == Model.BUSH  && distance(i) == 2) 
          {
             canSeeBush = true;
              if (canMove(Model.turn(i, -1)))
              {
                   return Model.turn(i, -1);
              }
              if (canMove(Model.turn(i, 1)))
              {
                   return Model.turn(i, 1);
              }
              if (canMove(Model.turn(i, -2))) 
              {
                   return Model.turn(i, -2);
              }
              if (canMove(Model.turn(i, 2))) 
              { 
                  return Model.turn(i, 2);
              }
              return i;
          }
        }
        if (canSeeBush) 
        {
          canSeeBush = false;
          if (canMove(personDirection + 1)) 
          { 
              return personDirection + 1;
          }
          if (canMove(personDirection - 1)) 
          {
              return personDirection - 1;
          }
          if (canMove(personDirection + 2)) 
          { 
              return personDirection + 2;
          }
          if (canMove(personDirection - 2)) 
          {
              return personDirection - 2;
          }
          return random(Model.MIN_DIRECTION, Model.MAX_DIRECTION);
        }
        return Model.STAY;
      }

    public int turnWall() {
      int atWall = Model.EDGE;
      for (int i = Model.MIN_DIRECTION; i <= Model.MAX_DIRECTION; i++) 
      {
        if (look(i) == Model.EDGE && distance(i) > 2) 
        {
          atWall++;
        }
      }
      return personDirection + atWall;
    }
}
