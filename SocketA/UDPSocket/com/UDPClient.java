
// package socketa;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Scanner;

public class UDPClient {
	
    private DatagramSocket clientSocket;
    private InetAddress serverAddress;
    private int port;
    private Scanner msgScanner;
	
	public UDPClient() throws SocketException, IOException {
        this.serverAddress = InetAddress.getByName("localhost");
        this.port = 5000;
		clientSocket = new DatagramSocket();
		
    }
	
    public void clientCommunication() throws Exception {
		System.out.println("-- Running UDP Client at " + InetAddress.getLocalHost() + " --");
		msgScanner = new Scanner(System.in);
		String msg;
		DatagramPacket clientSend = null;
		byte[] buff = new byte[1024];

        while (true) {
			
			System.out.print("\nSent message: ");
			msg = msgScanner.nextLine();
            buff = msg.getBytes();
            
			clientSend = new DatagramPacket(buff, buff.length, serverAddress, port);
			this.clientSocket.send(clientSend);
			
			System.out.println(
				"sent " + buff.length + " bytes to (" +
				clientSend.getAddress().getHostAddress() +
				", " + clientSend.getPort() + ")");

			buff = new byte[1024];
			DatagramPacket clientReceive =
				new DatagramPacket(buff, buff.length);
			this.clientSocket.receive(clientReceive);
			msg = new String(clientReceive.getData()).trim();
			
			System.out.println("\nRecieved message: " + msg);
			System.out.println(
				"received " + msg.getBytes().length + " bytes from (" +
				clientReceive.getAddress().getHostAddress() + ", "
				+ clientReceive.getPort() + ")");

			if (msg.equals("bye")) {
				System.out.println("Server sent bye.....EXITING");
				break;
			}
		}
		clientSocket.close();
	}
	
	public static void main(String args[]) throws Exception {        
        UDPClient serverSocket = new UDPClient();
        serverSocket.clientCommunication();
    }
}
