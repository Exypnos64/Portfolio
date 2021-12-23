package TicTacToe;

public class Player {
    private String name;
    private char symbol;
    private int wins;
    private int loses;
    private int moveToken;
    
    Player() {
        this.moveToken = 0;
    }
    
    Player(String name, char symbol) {
        this.name = name;
        this.symbol = symbol;
        this.moveToken = 0;
    }
    
    public String getName() {
        return this.name;
    }
    
    public char getSymbol() {
        return this.symbol;
    }
    
    public int getMove() {
        return this.moveToken;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public void setSymbol(char symbol) {
        this.symbol = symbol;
    }
    
    public void setMove(int moveToken) {
        this.moveToken = moveToken;
    }
    
    public void win() {
        wins++;
    }
    
    public void loses() {
        loses++;
    }
}
