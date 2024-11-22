package IgniV;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

public class IgniV
{
    public static void main(String[] args) throws FileNotFoundException {
        InputStream testin = new FileInputStream(args[0]);
       
        IgniVParser parser = new IgniVParser(new IgniVLexer(testin));
        // IgniVParser parser = new IgniVParser(new IgniVLexer(System.in));
        parser.parse().eval();
    }
}