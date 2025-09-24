import java.io.*;
import java.net.*;

public class clinet {
    public static void main(String[] args) {
        try {
          
            Socket socket = new Socket("localhost", 12345);
            System.out.println("Connected to server.");

            
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            
            out.println("Hello Server");

          
            String msg = in.readLine();
            System.out.println("Server says: " + msg);

            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
