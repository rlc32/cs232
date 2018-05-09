/*
* server.java is the server for the ceaser cipher project.
*Author: Russ Clousing rlc32
* 05/9/18
*
*/

import java.util.Scanner;
import java.net.Socket;
import java.net.ServerSocket;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.Date;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
//main driving server class
public class server{
	public static void main(String[] args) throws Exception {
		//confirm receiving port number on start
		if(args.length != 1){
			System.err.println("needs port number: java server <portnumber>");
			System.exit(1);
		}
		//starts server running on given port number
		int portNumber = Integer.parseInt(args[0]);
		System.out.println("Server started on port " + portNumber);
		Boolean waiting = true;
		//listining for new connections to the port
		try(ServerSocket serverSocket = new ServerSocket(portNumber)){
			while(waiting){
				new CaeserMultThread(serverSocket.accept()).start();
			}
		} catch(IOException e){
			System.err.println("Could not listen on port " + portNumber);
			System.exit(-1);
		}
	}
}
//creates new thread when a client connects.
class CaeserMultThread extends Thread{
	private Socket clientSocket = null;
	private String ip;
	//assign connection to a thread
	public CaeserMultThread(Socket socket){
		this.clientSocket = socket;
		//prints out useful information about client to the terminal.
		DateFormat dateFormat = new SimpleDateFormat("yyyy/mm/dd HH:mm:ss");
		Date date = new Date();
		ip = this.clientSocket.getRemoteSocketAddress().toString();
		System.out.println("New conection from "+ip+" at "+ dateFormat.format(date));
	}
	//runs the loop that prompts user for input to encrypt.
	public void run(){
		try(
			PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
			BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			){
			//confirms that offset has been recieved
			Boolean integer = true;
			Integer offSet = 0;
			String inputValue;
			// while the server can read input
			while((inputValue = in.readLine())!=null){
				//if user just connected get the offset value
				if(integer){
					offSet = Integer.parseInt(inputValue);
					out.append(offSet.toString());
					out.append("\n");
					out.flush();
					integer = false;
					continue;
				}
				//encrypt the user input and print it.
				out.append(encrypt(offSet, inputValue));
				out.append("\n");
				out.flush();
			}
			//terminate the connections
			System.out.println("terminating connection to " + ip);
			out.close();
			in.close();
			clientSocket.close();
		}catch(IOException e){
			e.printStackTrace();
		}
	}
	//This function handles encrypitng the user input
	private static String encrypt(Integer offset, String plaintext){
		String temp = "";
		Integer length = plaintext.length();
		//for ever char in the plaintext change it by the given offset
		for(Integer x = 0; x < length; x++){
			char c = (char)(plaintext.charAt(x)+offset);
			//if the offset changes it to be past z have it loop back the other way to start at begining of alphabet
			if(c > 'z'){
				temp += (char)(plaintext.charAt(x)-(26-offset));
			}else{
				temp+= (char)(plaintext.charAt(x)+offset);
			}
		}
		return temp;
	}
}