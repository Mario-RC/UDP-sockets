
// package socketa;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class UDPServer {

	private DatagramSocket serverSocket;
	private int port;
	private boolean running;
	
    public UDPServer() throws SocketException, IOException {
        this.port = 5000;
		this.serverSocket = new DatagramSocket(this.port);
		running = true;
	}
	
    private void serverCommunication() throws Exception {
        System.out.println("-- Running Server at " + InetAddress.getLocalHost() + "--");
		
		String msg;
		DatagramPacket serverReceive = null;
		byte[] buff = new byte[1024];
        
        while (running) {
            
            buff = new byte[1024];
            serverReceive = new DatagramPacket(buff, buff.length);
            serverSocket.receive(serverReceive);
			msg = new String(serverReceive.getData()).trim();
			
			// System.out.println("Client: " + data(buff).toString());
            System.out.println("\nRecieved message: " + msg);
			System.out.println(
				"received " + msg.getBytes().length + " bytes from (" +
				serverReceive.getAddress().getHostAddress() + ", "
				+ serverReceive.getPort() + ")");

			if (msg.equals("bye")) {
				System.out.println("Client sent bye.....EXITING");
				running = false;
				continue;
			}

			InetAddress clientAddress = serverReceive.getAddress();
			port = serverReceive.getPort();
			msg = "Received";
			buff = msg.getBytes();
			DatagramPacket serverSend =
				new DatagramPacket(buff, buff.length, clientAddress, port);
			serverSocket.send(serverSend);

			System.out.println("\nSent message: " + msg);
			System.out.println(
				"sent " + buff.length + " bytes back to (" +
				serverSend.getAddress().getHostAddress() +
				", " + serverSend.getPort() + ")");
		}
		serverSocket.close();
	}

	public static void main(String args[]) throws Exception {
		UDPServer clientSocket = new UDPServer();
		clientSocket.serverCommunication();
	}
}
