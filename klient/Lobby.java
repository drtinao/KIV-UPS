import javax.swing.*;
import java.awt.*;
import java.text.Normalizer;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.regex.Pattern;

import static javax.swing.JOptionPane.showMessageDialog;

public class Lobby {
    private static JTextField createNewTf = null; /* user submitted name of room */
    private static JList existingGameList = null; /* JList which contains names of already created rooms */

    private static Lobby lobby = null; /* instance of this singleton class */
    private static JFrame lobbyFrame = null; /* JFrame representing lobby (where user chooses game room) */

    /**
     * Sets visibility of Lobby part.
     * @param visibility true -> lobby visible, false -> lobby invisible
     */
    public static void setVisibility(boolean visibility){
        if(visibility){
            resetComponent();
        }

        if(lobby == null){
            lobby = new Lobby();
        }

        if(lobbyFrame == null){
            lobbyFrame = lobby.prepLobbyFrame();
        }

        lobbyFrame.setVisible(visibility);
    }

    /**
     * Resets all static variables to default state.
     */
    public static void resetComponent(){
       lobby = null;
       lobbyFrame = null;
    }

    /**
     * Prepares object of type JFrame which contains all GUI items of main lobby window.
     * @return JFrame object with GUI items
     */
    private static JFrame prepLobbyFrame(){
        JFrame lobbyFrame = new JFrame("Lobby");
        lobbyFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        lobbyFrame.setLayout(new FlowLayout());
        /* prepare GUI items - START */
        JLabel connectToL = new JLabel("Connect to existing room");
        JLabel createNewL = new JLabel("Create new room");

        existingGameList = new JList();
        existingGameList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        JScrollPane sPaneGameList = new JScrollPane(existingGameList);
        Dimension d = existingGameList.getPreferredSize();
        d.width = 160;
        d.height = 130;
        sPaneGameList.setPreferredSize(d);

        createNewTf = new JTextField("", 20);
        createNewTf.setToolTipText("Enter name of room (10 char max)");
        JButton connectToBtn = new JButton("Connect");
        JButton refreshBtn = new JButton("Refresh");
        refreshBtn.addActionListener(e -> refreshGameList());

        JPanel outerCardP = new JPanel();
        outerCardP.setAlignmentX(Component.CENTER_ALIGNMENT);
        outerCardP.add(connectToBtn);
        outerCardP.add(refreshBtn);
        connectToBtn.addActionListener(e -> connectToGame());
        JButton createNewBtn = new JButton("Create new");
        createNewBtn.addActionListener(e -> createNewGame());
        /* prepare GUI items - END */

        lobbyFrame.add(connectToL);
        lobbyFrame.add(sPaneGameList);
        lobbyFrame.add(outerCardP);
        lobbyFrame.add(createNewL);
        lobbyFrame.add(createNewTf);
        lobbyFrame.add(createNewBtn);
        lobbyFrame.setSize(250,325);
        lobbyFrame.setResizable(false);

        lobbyFrame.setLocationRelativeTo(null);
        return lobbyFrame;
    }

    /**
     * Is executed after clicking on button for connecting to existing game.
     * Gets name of chosen room and sends it to the server.
     */
    private static void connectToGame(){
        if(existingGameList.getSelectedValue() == null){
            showMessageDialog(null,"Select game from list please.","Warning",JOptionPane.WARNING_MESSAGE);
            return;
        }

        String roomName = existingGameList.getSelectedValue().toString();

        int roomNameLength = roomName.length();
        if(roomNameLength < 10){ /* add "%" to comply with 10 characters requirement */
            int toAdd = 10 - roomNameLength;

            for(int i = 0; i < toAdd; i++){
                roomName = roomName.concat("%");
            }
        }

        roomName += "0"; /* means that user wants to join existing room */
        ClientConnection connection = ClientConnection.getClientConnection();

        /* wait for server response - another thread */
        String finalRoomName = roomName;
        new Thread(() -> {
            String result = connection.sendToServer(finalRoomName, 2, false, false, false);

            if(result.equals("#99?")){ /* ok, received, connected */
                /* go to game screen */
                Lobby.setVisibility(false);
                displayOptionStartGame();
            }else if(result.equals("#98?")){
                showMessageDialog(null,"Server received invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(result.equals("#96?")) { /* room to which user wants to go does not exist anymore */
                showMessageDialog(null, "Room with name " + existingGameList.getSelectedValue() + " does not exist anymore!", "Error", JOptionPane.WARNING_MESSAGE);
            }else if(result.equals("#95?")){
                showMessageDialog(null,"Room with name " + existingGameList.getSelectedValue() + " has a game running or is full!","Error",JOptionPane.WARNING_MESSAGE);
            }else{ /* server returned invalid confirmation.. */
                showMessageDialog(null,"Server returned invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }
        }).start();
    }

    /**
     * Is executed after clicking on button for new game creation.
     * Method checks validity of user input and sends name of the
     * new room to server (10char is name + 1char '1' -> user wants
     * to create a new room)
     */
    private static void createNewGame(){
        if(checkValuesCreateNew() != 0){
            return;
        }

        /* input values are ok */
        /* send nickname to server - START */
        String newRoom = createNewTf.getText();
        int newRoomLength = newRoom.length();
        if(newRoomLength < 10){ /* add "%" to comply with 10 characters requirement */
            int toAdd = 10 - newRoomLength;

            for(int i = 0; i < toAdd; i++){
                newRoom = newRoom.concat("%");
            }
        }

        newRoom += "1"; /* means that user wants to create a new room */
        ClientConnection connection = ClientConnection.getClientConnection();
        String finalNewRoom = newRoom;
        new Thread(() -> {
            String result = connection.sendToServer(finalNewRoom,2, false, false, false);

            if(result.equals("#99?")){ /* ok, received, room created */
                /* go to game screen */
                Lobby.setVisibility(false);
                displayOptionStartGame();
            }else if(result.equals("#98?")){ /* server received invalid message */
                showMessageDialog(null,"Server received invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }else if(result.equals("#97?")) { /* room which user wants to create already exists */
                showMessageDialog(null,"Room with name " + createNewTf.getText() + " already exists, you cannot create a new one!","Error",JOptionPane.WARNING_MESSAGE);
            }else{ /* server returned invalid confirmation.. */
                showMessageDialog(null,"Server returned invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }
        }).start();
        /* send nickname to server - END */
    }

    /**
     * Checks validity of user entered name of game room.
     * @return 0 if game room name is ok, else 1
     */
    private static int checkValuesCreateNew(){
        /* check room name - START */
        if(createNewTf == null || createNewTf.getText().length() > 10 || createNewTf.getText().length() == 0 || createNewTf.getText().contains("%")){
            showMessageDialog(new JFrame(), "Room name length can be 10 characters only and cannot contain \"%\"!", "Check room name", JOptionPane.ERROR_MESSAGE);
            if(createNewTf != null){
                createNewTf.setText("");
            }
            return 1;
        }

        String convertedString = Normalizer.normalize(createNewTf.getText(), Normalizer.Form.NFD).replaceAll("[^\\p{ASCII}]", "");
        if(!convertedString.equals(createNewTf.getText())){
            showMessageDialog(new JFrame(), "Room of the name cannot contain diacritics!", "Check name", JOptionPane.ERROR_MESSAGE);
            return 1;
        }

        if(!Pattern.matches("[a-zA-Z0-9]+", createNewTf.getText())){
            showMessageDialog(new JFrame(), "Room name can contain just normal alphabet characters (a-z) and numbers (0-9)!", "Check name", JOptionPane.ERROR_MESSAGE);
            return 1;
        }
        /* check room name - END */

        return 0;
    }

    /**
     * Send request message to server ('1'), which means -> get game room list.
     * Expected response is 50char (5game rooms, each 10char);
     */
    private static void refreshGameList(){
        ClientConnection con = ClientConnection.getClientConnection();

        /* wait for server response - another thread */
        new Thread(() -> {
            String result = con.sendToServer("1", 2, true, false, false);
            if(result.charAt(0) == '#' && result.charAt(51) == '?'){ /* ok received */
                result = result.substring(1, 51);

                String[] game_rooms = new String[5];
                int free_index = 0;
                String one_room = "";

                int counter = 0;
                for(int i = 0; i < result.length(); i++){
                    if(result.charAt(i) != '%')
                        one_room += result.charAt(i);
                    counter++;

                    if(counter == 10){
                        counter = 0;
                        game_rooms[free_index] = one_room;
                        one_room = "";
                        free_index++;
                    }
                }

                DefaultListModel model = new DefaultListModel();
                model.clear();

                for(int i = 0; i < game_rooms.length; i++){
                    model.add(i, game_rooms[i]);
                }
                existingGameList.setModel(model);
            }else{
                showMessageDialog(null,"Server returned invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
            }
        }).start();
    }

    /**
     * Displays an option dialog from which can user start the game.
     */
    private static void displayOptionStartGame(){
        AtomicBoolean left = new AtomicBoolean(false); /* true if user left the room, then exit thread */
        ClientConnection connection = ClientConnection.getClientConnection();

        /* waiting window creation - START */
        JFrame waitFrame = new JFrame("Waiting");
        waitFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        waitFrame.setLayout(new FlowLayout());
        JLabel waitingL = new JLabel("Waiting for other players");
        JButton startGameBtn = new JButton("Start game");
        JButton leaveRoomBtn = new JButton("Leave room");

        waitFrame.add(waitingL);
        waitFrame.add(startGameBtn);
        waitFrame.add(leaveRoomBtn);
        waitFrame.setSize(200,135);
        waitFrame.setResizable(false);
        waitFrame.setLocationRelativeTo(null);
        /* waiting window creation - END */

        /* new thread for checking if game has been started */
        new Thread(() -> {
            String result = "";

            long startTime = System.currentTimeMillis();
            long endTime = System.currentTimeMillis();
            long timeElapsed = endTime - startTime;
            while(!result.equals("#10?") && !left.get()){
                endTime = System.currentTimeMillis();
                timeElapsed = endTime - startTime;
                if(timeElapsed < 1000){ /* every 1 sec check game state */
                    continue;
                }else{
                    startTime = System.currentTimeMillis();
                }

                result = connection.sendToServer("7", 3, false, false, false);

                if(result.equals("#10?")){ /* game started successfully */
                    left.set(true);
                    waitFrame.setVisible(false);
                    Game.setVisibility(true);
                }else if(result.equals("#99?")){ /* not started yet */
                    /* code if the game has not started */
                }
            }
        }).start();

        waitFrame.setVisible(true);
        startGameBtn.addActionListener(arg0 -> {
            new Thread(() -> {
                String result = connection.sendToServer("5", 3, false, false, false);
                if(result.equals("#99?")){ /* ok - game started could be started */
                    /* another thread (upper defined) will start the game */
                }else if(result.equals("#11?")){ /* cannot start game, room is empty */
                    JOptionPane.showMessageDialog(null,"Room is empty, cannot start yet!\n","Error",JOptionPane.WARNING_MESSAGE);
                }else if(result.equals("#98?")){ /* server received invalid data */
                    showMessageDialog(null,"Server received invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
                }else{/* server returned invalid confirmation.. */
                    showMessageDialog(null,"Server returned invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
                }
            }).start();
        });

        leaveRoomBtn.addActionListener(arg0 -> {
            new Thread(() -> {
                String result = connection.sendToServer("6", 3, false, false, false);
                if(result.equals("#99?")){ /* ok - response */
                    left.set(true);;
                    Lobby.setVisibility(true);
                    waitFrame.setVisible(false);
                }else if(result.equals("#98?")){ /* server received invalid data */
                    showMessageDialog(null,"Server received invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
                }else{/* server returned invalid confirmation.. */
                    showMessageDialog(null,"Server returned invalid data, try it one more time please.","Warning",JOptionPane.WARNING_MESSAGE);
                }
            }).start();
        });
    }
}
