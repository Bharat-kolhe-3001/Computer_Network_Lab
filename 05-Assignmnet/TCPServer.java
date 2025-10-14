import java.io.*;
import java.net.*;
import javax.script.*;   

public class TCPServer {
    public static void main(String[] args) throws Exception {
        ServerSocket serverSocket;
        Socket socket;
        BufferedReader in;
        PrintWriter out;

        System.out.println("===== TCP Server Menu =====");
        System.out.println("1. Say Hello");
        System.out.println("2. File Transfer");
        System.out.println("3. Calculator");
        System.out.print("Enter your choice: ");

        BufferedReader console = new BufferedReader(new InputStreamReader(System.in));
        int choice = Integer.parseInt(console.readLine());

        switch (choice) {
            case 1:  
                serverSocket = new ServerSocket(5000);
                System.out.println("Server waiting for Hello client...");
                socket = serverSocket.accept();
                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                out = new PrintWriter(socket.getOutputStream(), true);

                String msg = in.readLine();
                System.out.println("Client says: " + msg);
                out.println("Hello from Server!");

                socket.close();
                serverSocket.close();
                break;

            case 2: 
                serverSocket = new ServerSocket(6000);
                System.out.println("Server ready to receive file...");
                socket = serverSocket.accept();

                FileOutputStream fos = new FileOutputStream("received.txt");
                BufferedInputStream bis = new BufferedInputStream(socket.getInputStream());
                byte[] buffer = new byte[1024];
                int bytesRead;
                while ((bytesRead = bis.read(buffer)) != -1) {
                    fos.write(buffer, 0, bytesRead);
                }

                System.out.println("File received successfully as 'received.txt'");
                fos.close();
                socket.close();
                serverSocket.close();
                break;

            case 3:  
                serverSocket = new ServerSocket(7000);
                System.out.println("Calculator Server running...");
                socket = serverSocket.accept();
                in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                out = new PrintWriter(socket.getOutputStream(), true);

                String expr = in.readLine();
                System.out.println("Received expression: " + expr);

                try {
                    ScriptEngine engine = new ScriptEngineManager().getEngineByName("JavaScript");
                    String result = engine.eval(expr).toString();
                    out.println(result);
                } catch (Exception e) {
                    out.println("Error in expression");
                }

                socket.close();
                serverSocket.close();
                break;

            default:
                System.out.println("Invalid choice!");
        }

        System.out.println("Server Task Completed.");
    }
}
