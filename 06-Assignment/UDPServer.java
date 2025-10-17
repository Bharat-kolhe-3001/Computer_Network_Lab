import java.io.*;
import java.net.*;

public class UDPServer {
    public static void main(String[] args) throws Exception {
        DatagramSocket server = new DatagramSocket(5000);
        byte[] buffer = new byte[1024];
        System.out.println("UDP Server started...");
 
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        server.receive(packet);
        String clientMsg = new String(packet.getData(), 0, packet.getLength());
        System.out.println("Client says: " + clientMsg);

        InetAddress clientAddr = packet.getAddress();
        int clientPort = packet.getPort();
        String reply = "Hello from Server!";
        server.send(new DatagramPacket(reply.getBytes(), reply.length(), clientAddr, clientPort));

       
        packet = new DatagramPacket(buffer, buffer.length);
        server.receive(packet);
        String fileName = new String(packet.getData(), 0, packet.getLength());
        System.out.println("Requested file: " + fileName);

        File file = new File(fileName);
        if (file.exists()) {
            server.send(new DatagramPacket("FOUND".getBytes(), 5, clientAddr, clientPort));

            FileInputStream fis = new FileInputStream(file);
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                server.send(new DatagramPacket(buffer, bytesRead, clientAddr, clientPort));
                Thread.sleep(10);
            }
            fis.close();

            server.send(new DatagramPacket("EOF".getBytes(), 3, clientAddr, clientPort));
            System.out.println("File sent successfully!");
        } else {
            server.send(new DatagramPacket("NOTFOUND".getBytes(), 8, clientAddr, clientPort));
            System.out.println("File not found.");
        }

     
        packet = new DatagramPacket(buffer, buffer.length);
        server.receive(packet);
        String expr = new String(packet.getData(), 0, packet.getLength());
        System.out.println("Received expression: " + expr);

        String result;
        try {
            String[] parts = expr.trim().split(" ");
            double a = Double.parseDouble(parts[0]);
            String op = parts[1];
            double b = Double.parseDouble(parts[2]);
            double res = 0;
            switch (op) {
                case "+": res = a + b; break;
                case "-": res = a - b; break;
                case "*": res = a * b; break;
                case "/": res = a / b; break;
                default: result = "Invalid operator"; break;
            }
            result = "Result: " + res;
        } catch (Exception e) {
            result = "Error in calculation.";
        }

        server.send(new DatagramPacket(result.getBytes(), result.length(), clientAddr, clientPort));
        System.out.println("Result sent to client.");

        server.close();
    }
}
