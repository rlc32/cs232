/*
* client.java is the client for the ceaser cipher project.
*Author: Russ Clousing rlc32
* 05/9/18
*
*/



import java.util.Scanner;
import java.net.Socket;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStream;
//main client class
public class client{
	public static void main(String[] args) throws IOException{
		//check user input has two arguments
		if(args.length != 2){
			System.err.println("Two arguments needed.");
			System.exit(1);
		}
		Integer portNumber;
		String serverName = args[0];
		//confirm that second argument is integer.
		try{
			portNumber = Integer.parseInt(args[1]);
		}catch(NumberFormatException ex ){
			System.err.println("Second argument must be an integer");
			return;
		}
		System.out.println("Welcome to the caeser cipher");
		//prompt for user input of offest
		System.out.print("Please enter the rotation offset (1-25): ");
		//read in user input
		Scanner getInput = new Scanner(System.in);
		Integer offset = getInput.nextInt();
		//create connection to server
		try(
			Socket serverSocket = new Socket(serverName, portNumber);
			OutputStream os = serverSocket.getOutputStream();
			PrintWriter out = new PrintWriter(os, true);
			BufferedReader input = new BufferedReader(new InputStreamReader(serverSocket.getInputStream()));
			){
			//send offset to the server
			out.append(offset.toString());
			out.append("\n");
			out.flush();
			//read in returned offset value
			String outputline = input.readLine();
			System.out.println("The Server has returned an offset value of: " + outputline + "\n");
			//prompt for user to enter text to be sent to server
			String returnVal;
			while(true){
				System.out.print("Please enter text to be encrypted: ");
				String text = getInput.nextLine();
				if(text.equals("quit")){
					System.out.println("\n Closing Connection");
					break;
				}
				out.append(text);
				out.append("\n");
				out.flush();
				returnVal = input.readLine();
				//prevents writing blank output to terminal as encryped text. 
				//this happens on first time run for some reason. so this if block catches it.
				if(returnVal.equals("")){
					System.out.println("");
					continue;
				}
				//print out the encrypted text
				System.out.println("encrypted text: " + returnVal);
			}
		}catch(IOException e){
			System.err.println("Could not connect to "+ serverName);
			System.exit(-1);
		}

	}
}