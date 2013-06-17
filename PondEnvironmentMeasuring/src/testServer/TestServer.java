package testServer;

import java.io.*;
import java.net.*;

// A TCP Server providing a simple csv-File to test the application against

class TestServer
{
   public static void main(String argv[]) throws Exception
      {
	   
	     String cvsContent = "00,30,15,13,05,2013,11.5,9.7,\n"
	 			+ "01,00,16,13,05,2013,11.0,7.8,3.0\n"
	 			+ "01,30,14,13,05,2013,,7.5, 3.5\n";

	     // Socket on which the Server is running
		 ServerSocket myServerSocket = new ServerSocket(6789);
		 
		 System.out.println("Server active");
	     
		 // connection socket, being initialized when a client connects
	     Socket mySocket = myServerSocket.accept();
	     
	     System.out.println("Client connecting from ["+mySocket.getInetAddress()+", "+mySocket.getPort()+"]\n");
	       
	     DataOutputStream out = new DataOutputStream(mySocket.getOutputStream());
	       
	     // write CSV to TCP Stream
	     out.writeBytes(cvsContent);
	
	     // close connection
	     mySocket.close();
	     myServerSocket.close();
	     
	     System.out.println("Transfer finished");
      }
}