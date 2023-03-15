import javax.swing.*;
import java.io.*;
import java.net.InetSocketAddress;
import java.net.Socket;

import static javax.swing.JOptionPane.showMessageDialog;

public class ClientConnection{
    private static ClientConnection connection = null; /* instance of class ClientConnection */

    private static String serverIP; /* IP address of server */
    private static int portNumber; /* port number */
    private static Socket connectSock; /* socket used for communication with the server */
    private static boolean sendOff; /* if true, sending to message cannot be performed */

    private static boolean connectSuccess; /* true is connection was successful, else false */
    private static OutputStream outputStr; /* for socket write */
    private static PrintWriter outputPw; /* for socket write */
    private static InputStream inputStr; /* for socket read */
    private static BufferedReader inputBr; /* for socket read */

    /**
     * Singleton class, which is used for handling connection to server.
     * @return instance of ClientConnection
     */
    public static ClientConnection getClientConnection(){
        if(connection == null){
            connection = new ClientConnection();
        }
        return connection;
    }

    /**
     * Just takes server IP address + port number and assigns them to respective variables.
     * @param serverIP IP address of server
     * @param portNumber port number
     */
    public void initConnection(String serverIP, int portNumber){
        this.serverIP = serverIP;
        this.portNumber = portNumber;

        connectSuccess = false;
        sendOff = false;
    }

    /**
     * Function tries to establish connection with the game server.
     * @return 0 if connection went ok, else -1
     */
    public static int tryConnect(){
        try{
            connectSock = new Socket();
            connectSock.connect(new InetSocketAddress(serverIP, portNumber), 2000); /* 2s timeout for connect */
            connectSock.setSoTimeout(1000);
            connectSuccess = true;

            inputStr = connectSock.getInputStream();
            inputBr = new BufferedReader(new InputStreamReader(inputStr));
            outputStr = connectSock.getOutputStream();
            outputPw = new PrintWriter(outputStr);
            showMessageDialog(null,"Connection to server was successful!\n" + "IP: " + serverIP + "\nPort: " + portNumber,"Welcome",JOptionPane.INFORMATION_MESSAGE);
            return 0;
        }catch(IOException exception){
            showMessageDialog(null,"Connection to server cannot be established!\n" + "IP: " + serverIP + "\nPort: " + portNumber,"Warning",JOptionPane.WARNING_MESSAGE);
            connectSuccess = false;
            return -1;
        }
    }

    /**
     * Getter for connectSuccess. Equals to true when connection to server was successful, else false.
     * @return value of connectSuccess
     */
    public static boolean getConnectSuccess(){
        return connectSuccess;
    }

    /**
     * Method tries to send given message to game server. If an error occurs, warning is displayed. Also returns answer from game server when returned. Expected message depends on stage in which user currently is.
     * @param stringToSend String object with message to send
     * @param userStage stage of player
     * @param nameWanted if name is expected (in some stages - name of rooms, name of people in room etc.)
     * @param cardsWanted if user expects cards in hand (34char - 0 if card not present, 1 if present)
     * @param gameStateWanted if state of game is expected(message in form "#xyyz?", where x = player´s num, yy = number of card placed (0-44) OR 00 if waiting for player OR 45 if player takes card
     *        OR 46 if player disconnected)
     * @return message received
     */
    public static synchronized String sendToServer(String stringToSend, int userStage, boolean nameWanted, boolean cardsWanted, boolean gameStateWanted){
        if(sendOff){
            while(true){
              /* neverending loop, wait for app to close */
            }
        }

        char beginCharacter = '#'; /* message start */
        char endCharacter = '?'; /* message end */

        System.out.println("SEND to server: " + beginCharacter + stringToSend + endCharacter + "\n");

        try{
            outputPw.print(beginCharacter + stringToSend + endCharacter);
            outputPw.flush();
        }catch(Exception exception){
            showMessageDialog(null,"Error while sending data!\n" + "IP: " + serverIP + "\nPort: " + portNumber,"Warning",JOptionPane.WARNING_MESSAGE);
        }

        int expectedCharNum = 0;

        String message = "";

        switch(userStage){
            case 1: /* connected, get name confirmation (99 = ok, received), (98 = fail) */
                expectedCharNum = 4;
                break;

            case 2: /* picking game room (99 = ok, received; 98 = game running, error; 97 = room with name already exists), error; 50char -> room names */
                if(nameWanted){
                    expectedCharNum = 52; /* user send request to get game rooms */
                }else{
                    expectedCharNum = 4; /* confirm game pick */
                }
                break;

            case 3: /* waiting for game to start (10 - game started by some user), (11 - game cannot be started, room is empty), (99 - received request. but game has not been started yet) */
                expectedCharNum = 4;
                break;

            case 4: /* playing game */
                if(cardsWanted){
                    expectedCharNum = 34; /* card length */
                }else if(nameWanted){
                    expectedCharNum = 47; /* names of people in room 3*15char */
                }else if(gameStateWanted){
                    expectedCharNum = 6; /* code for game change */
                }else{
                    expectedCharNum = 4; /* new card expected */;
                }
                break;
        }

        try{
            for(int i = 0; i < expectedCharNum; i++){
                char c = (char) inputBr.read();
                message += c;
            }

            if(message.charAt(0) != '#' || message.charAt(message.length() - 1) != '?'){
                sendOff = true;
                showMessageDialog(null,"Connection to server was lost, client will be closed!","Warning",JOptionPane.WARNING_MESSAGE);
                System.exit(0);
            }

        }catch (IOException e){
            if(!sendOff){
                sendOff = true;
                showMessageDialog(null,"Connection to server was lost, client will be closed!","Warning",JOptionPane.WARNING_MESSAGE);
                System.exit(0);
            }
        }

        System.out.println("RECEIVE from server: " + message + "\n");
        return message;
    }

    /**
     * Closes connection with the server.
     */
    public static void closeConnection(){
        try{
            inputBr.close();
            outputStr.close();
            connectSock.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
}
