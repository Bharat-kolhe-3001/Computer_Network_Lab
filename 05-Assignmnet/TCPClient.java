import java.io.*;
import java.net.*;

public class TCPClient {
    public static void main(String[] args) throws Exception {
        System.out.println("===== TCP Client Menu =====");
        System.out.println("1. Say Hello");
        System.out.println("2. File Transfer");
        System.out.println("3. Calculator");
        System.out.print("Enter your choice: "); 

        BufferedReader console = new BufferedReader(new InputStreamReader(System.in));
        int choice = Integer.parseInt(console.readLine());

        switch (choice) {
            case 1:  
                Socket s1 = new Socket("localhost", 5000);
                BufferedReader in1 = new BufferedReader(new InputStreamReader(s1.getInputStream()));
                PrintWriter out1 = new PrintWriter(s1.getOutputStream(), true);

                out1.println("Hello from Client!");
                System.out.println("Server says: " + in1.readLine());

                s1.close();
                break;

            case 2: 
                Socket s2 = new Socket("localhost", 6000);
                System.out.print("Enter file name to send: ");
                String filename = console.readLine();

                FileInputStream fis = new FileInputStream(filename);
                BufferedOutputStream bos = new BufferedOutputStream(s2.getOutputStream());
                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = fis.read(buffer)) != -1) {
                    bos.write(buffer, 0, bytesRead);
                }
                bos.flush();
                fis.close();
                s2.close();
                System.out.println("File sent successfully.");
                break;

            case 3: 
                Socket s3 = new Socket("localhost", 7000);
                BufferedReader in3 = new BufferedReader(new InputStreamReader(s3.getInputStream()));
                PrintWriter out3 = new PrintWriter(s3.getOutputStream(), true);

                System.out.print("Enter arithmetic expression (e.g. 5+3*2): ");
                String expr = console.readLine();
                out3.println(expr);

                System.out.println("Result from server: " + in3.readLine());
                s3.close();
                break;

            default:
                System.out.println("Invalid choice!");
        }

        System.out.println("Client Task Completed.");
    }
}

