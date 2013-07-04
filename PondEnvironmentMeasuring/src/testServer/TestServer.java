package testServer;

import java.io.*;
import java.net.*;

// A TCP Server providing a simple csv-File to test the application against

class TestServer
{
   public static void main(String argv[]) throws Exception
      {
	   
	     String cvsContent = "00,00,02,02,07,2013,17.13,1\n" //2 o'clock
	    		 		   + "00,00,05,02,07,2013,17.12,100\n" //5 o'clock
	    		 		   + "00,00,08,02,07,2013,16.17,1000\n" //8 o'clock
	    		 		   + "00,00,11,02,07,2013,17.22,700000\n" //11 o'clock
	    		 		   + "00,00,14,02,07,2013,17.25,50000\n" //14 o'clock
	    		 		   + "00,00,17,02,07,2013,18.26,20000\n" //17 o'clock
	    		 		   + "00,00,20,02,07,2013,18.21,20000\n" //20 o'clock
	    		 		   + "00,00,23,02,07,2013,18.17,1000\n" //23 o'clock
	    		 			;

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