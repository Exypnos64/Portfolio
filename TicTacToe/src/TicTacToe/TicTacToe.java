package TicTacToe;
import java.util.Scanner;

public class TicTacToe {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Player p1 = new Player();
        Player p2 = new Player();
        char[][] board = new char[3][3];
        for (int i=0; i<3; i++){
            for (int j=0; j<3; j++) {
                board[i][j] = ' ';
            }
        }
        
        
        System.out.println("Welcome to Tic Tac Toe!\n\n");
        
        /* Initialize Player 1 */
        System.out.print("Please input player 1's name: ");
        p1.setName(input.nextLine());
        System.out.print("Please input your chosen symbol: ");
        p1.setSymbol(input.nextLine().charAt(0));
        
        System.out.println();
        
        /* Initialize Player 2 */
        System.out.print("Please input player 2's name: ");
        p2.setName(input.nextLine());
        boolean same = true;
        while (same) {
            System.out.print("Please input your chosen symbol: ");
            p2.setSymbol(input.nextLine().charAt(0));
            if (p1.getSymbol() == p2.getSymbol()) {
                System.out.printf("That's %s's symbol!\n\n", p1.getName());
                same = true;
            }
            else
                same = false;
        }
        Mechanics.game(p1, p2, board);
    }
}
