import java.io.*;
import java.net.*;
import java.util.Scanner;

public class UDPClient {
    public static void main(String[] args) throws Exception {
        DatagramSocket client = new DatagramSocket();
        InetAddress serverAddr = InetAddress.getByName("localhost");
        byte[] buffer = new byte[1024];
        Scanner sc = new Scanner(System.in);

        // Step 1: Send hello
        String msg = "Hello Server";
        client.send(new DatagramPacket(msg.getBytes(), msg.length(), serverAddr, 5000));

        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        client.receive(packet);
        System.out.println("Server says: " + new String(packet.getData(), 0, packet.getLength()));

      
        System.out.print("Enter file name to request: ");
        String fileName = sc.nextLine();
        client.send(new DatagramPacket(fileName.getBytes(), fileName.length(), serverAddr, 5000));

        FileOutputStream fos = new FileOutputStream("received_" + fileName);
        while (true) {
            packet = new DatagramPacket(buffer, buffer.length);
            client.receive(packet);
            String data = new String(packet.getData(), 0, packet.getLength());
            if (data.equals("EOF")) break;
            if (data.equals("NOTFOUND")) {
                System.out.println("File not found on server.");
                fos.close();
                client.close();
                return;
            }
            fos.write(packet.getData(), 0, packet.getLength());
        }
        fos.close();
        System.out.println("File received  successfully!");

        System.out.print("Enter arithmetic expression (e.g. 5 + 3): ");
        String expr = sc.nextLine();
        client.send(new DatagramPacket(expr.getBytes(), expr.length(), serverAddr, 5000));

        packet = new DatagramPacket(buffer, buffer.length);
        client.receive(packet);
        System.out.println("Server reply: " + new String(packet.getData(), 0, packet.getLength()));

        client.close();
        System.out.println("Client Task Completed.");
    }
}
