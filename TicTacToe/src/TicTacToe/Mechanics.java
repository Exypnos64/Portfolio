package TicTacToe;
import java.util.Scanner;

public class Mechanics {
    
    public static void game(Player player1, Player player2, char[][] board) {
        Scanner input = new Scanner(System.in);
        player1.setMove(1);
        while (!winLose(player1, player2, board)) {
            
            /* Player 1's Turn */
            if (player1.getMove() == 1) {
                printBoard(board);
                takeTurn(player1, player2, board);
            }
            
            /* Player 2's Turn */
            else {
                printBoard(board);
                takeTurn(player2, player1, board);
            }
        }
    }
    
    public static void takeTurn(Player pTurn, Player pNot, char[][] board) {
        Scanner input = new Scanner(System.in);
        
        String coord = "";
        char[] move = new char[2];
        System.out.printf("It's %s's turn!\n", pTurn.getName());
        System.out.print("Where do you want to place a mark? ex. 0A: ");
        coord = input.nextLine().toUpperCase();
        move[0] = coord.charAt(0);
        move[1] = coord.charAt(1);

        if (validMove(move, board)) {
            int x = Character.getNumericValue(move[0]);
            int y = 0;
            switch (move[1]) {
                case 'A': y = 0; break;
                case 'B': y = 1; break;
                case 'C': y = 2; break;
            }
            board[x][y] = pTurn.getSymbol();
            nextTurn(pTurn, pNot);
        }
        else{
            System.out.println("\nThat is not a valid move, please try again.\n");
        }
    }
    
    public static void nextTurn(Player player1, Player player2) {
        if (player1.getMove() == 1) {
            player1.setMove(0);
            player2.setMove(1);
        }
        else {
            player1.setMove(1);
            player2.setMove(0);
        }
    }
    
    public static boolean validMove(char[] move, char[][] board) {
        int x = Character.getNumericValue(move[0]);
        int y = 0;
        switch (move[1]) {
            case 'A': y = 0; break;
            case 'B': y = 1; break;
            case 'C': y = 2; break;
        }
        
        if ((move[0] == '0') || (move[0] == '1') || (move[0] == '2')) {
            if ((move[1] == 'A') || (move[1] == 'B') || (move[1] == 'C')) 
                if (board[x][y] == ' ')
                    return true;
                else
                    return false;
            else
                return false;
        }
        else
            return false;
    }
    
    public static boolean winLose(Player player1, Player player2, char[][] board) {
        /* Check for full board */
        int full = 0;
        for (int i=0; i<3; i++)  {
            for (int j=0; j<3; j++) {
                if (board[i][j] != ' ') {
                    full++;
                }
            }
        }
        /* Check Columns for win */
        for (int i=0; i < board.length; i++) {
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
                if (board[i][0] == player1.getSymbol()) {
                    printBoard(board);
                    System.out.printf("%s wins!\n", player1.getName());
                    return true;
                }
                else if (board[i][0] == player2.getSymbol()){
                    printBoard(board);
                    System.out.printf("%s wins!\n", player2.getName());
                    return true;
                }
            }
        }
        
        /* Check Rows for win */
        for (int i=0; i < board[0].length; i++) {
            if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
                if (board[0][i] == player1.getSymbol()) {
                    printBoard(board);
                    System.out.printf("%s wins!\n", player1.getName());
                    return true;
                }
                else if (board[0][i] == player2.getSymbol()){
                    printBoard(board);
                    System.out.printf("%s wins!\n", player2.getName());
                    return true;
                }
            }
        }
        
        /* Check diagonals for win */
        if (board[0][0] ==  board[1][1] && board[0][0] == board[2][2]) {
            if (board[0][0] == player1.getSymbol()) {
                    printBoard(board);
                System.out.printf("%s wins!\n", player1.getName());
                return true;
            }
            else if (board[0][0] == player2.getSymbol()){
                    printBoard(board);
                System.out.printf("%s wins!\n", player2.getName());
                return true;
            }
        }
        else if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
            if (board[0][2] == player1.getSymbol()) {
                printBoard(board);
                System.out.printf("%s wins!\n", player1.getName());
                return true;
            }
            else if (board[0][2] == player2.getSymbol()){
                printBoard(board);
                System.out.printf("%s wins!\n", player2.getName());
                return true;
            }
        }
        
        if (full == 9) {
            printBoard(board);
            System.out.printf("%s and %s tied!\n", player1.getName(), player2.getName());
            return true;
        }
        return false;
    }
    
    public static void printBoard(char[][] board) {
        System.out.println("   A B C\n");
        
        System.out.printf("0  %c|%c|%c\n", board[0][0], board[0][1], board[0][2]);
        System.out.println("   -----");
        System.out.printf("1  %c|%c|%c\n", board[1][0], board[1][1], board[1][2]);
        System.out.println("   -----");
        System.out.printf("2  %c|%c|%c\n\n", board[2][0], board[2][1], board[2][2]);
    }
}
